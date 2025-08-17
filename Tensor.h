#pragma once
#include <vector>
#include <array>
#include <initializer_list>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <type_traits>
#include <cstddef>
#include <ostream>

using namespace std; // 👈 your preference

// Small helper for range slicing
struct Range {
    size_t start;
    size_t stop;   // exclusive
    size_t step;   // > 0
    Range(size_t s, size_t e, size_t p=1) : start(s), stop(e), step(p) {
        if (p == 0) throw invalid_argument("Range.step must be > 0");
    }
};

template <class T>
class Tensor {
public:
    using value_type      = T;
    using size_type       = size_t;
    using shape_type      = vector<size_type>;
    using strides_type    = vector<size_type>;
    using container_type  = vector<T>;
    using iterator        = typename container_type::iterator;
    using const_iterator  = typename container_type::const_iterator;

    // ───────────── constructors ─────────────
    Tensor() = default;

    // Construct with shape and optional initial value
    explicit Tensor(shape_type shape, const T& init = T())
        : shape_(move(shape))
    {
        validate_shape();
        compute_strides();
        data_.assign(numel(), init);
    }

    // Construct from data (flattened) and shape
    Tensor(container_type data, shape_type shape)
        : data_(move(data)), shape_(move(shape))
    {
        validate_shape();
        compute_strides();
        if (data_.size() != numel())
            throw invalid_argument("Data size does not match shape product.");
    }

    // Construct from initializer_list for 1D
    Tensor(initializer_list<T> list)
        : data_(list), shape_{list.size()}
    {
        compute_strides();
    }

    // ───────────── basic info ─────────────
    size_type ndim() const noexcept { return shape_.size(); }
    const shape_type& shape() const noexcept { return shape_; }
    const strides_type& strides() const noexcept { return strides_; }
    size_type size() const noexcept { return data_.size(); }
    size_type numel() const noexcept {
        return shape_.empty()
             ? 0
             : accumulate(shape_.begin(), shape_.end(), size_type{1}, multiplies<size_type>());
    }

    // ───────────── data access ─────────────
    // Access with vector of indices
    T& at(const shape_type& idx) { return data_.at(flat_index_checked(idx)); }
    const T& at(const shape_type& idx) const { return data_.at(flat_index_checked(idx)); }

    // Variadic operator()
    template <class... Indexes,
              class = enable_if_t<(conjunction_v<is_integral<Indexes>...>)>>
    T& operator()(Indexes... is) {
        shape_type idx{ static_cast<size_type>(is)... };
        return at(idx);
    }
    template <class... Indexes,
              class = enable_if_t<(conjunction_v<is_integral<Indexes>...>)>>
    const T& operator()(Indexes... is) const {
        shape_type idx{ static_cast<size_type>(is)... };
        return at(idx);
    }

    // Iteration
    iterator begin() noexcept { return data_.begin(); }
    iterator end() noexcept { return data_.end(); }
    const_iterator begin() const noexcept { return data_.begin(); }
    const_iterator end() const noexcept { return data_.end(); }

    // Fill
    void fill(const T& v) { std::fill(data_.begin(), data_.end(), v); }

    // Reshape (keeps elements count the same)
    void reshape(shape_type new_shape) {
        if (product(new_shape) != numel())
            throw invalid_argument("reshape: total elements must remain constant.");
        shape_ = move(new_shape);
        compute_strides();
    }

    // Squeeze: remove dimensions of size 1
    Tensor squeeze() const {
        shape_type new_shape;
        for (size_type dim : shape_) {
            if (dim != 1) {
                new_shape.push_back(dim);
            }
        }
        // If all dimensions were 1, keep at least one dimension
        if (new_shape.empty()) {
            new_shape.push_back(1);
        }
        
        Tensor result(data_, new_shape);
        return result;
    }

    // Squeeze specific dimension (only if it has size 1)
    Tensor squeeze(size_type dim) const {
        if (dim >= ndim()) {
            throw out_of_range("Dimension index out of range for squeeze.");
        }
        if (shape_[dim] != 1) {
            throw invalid_argument("Cannot squeeze dimension that is not of size 1.");
        }
        
        shape_type new_shape;
        for (size_type i = 0; i < ndim(); ++i) {
            if (i != dim) {
                new_shape.push_back(shape_[i]);
            }
        }
        // If we removed the last dimension, keep at least one dimension
        if (new_shape.empty()) {
            new_shape.push_back(1);
        }
        
        Tensor result(data_, new_shape);
        return result;
    }

    // Squeeze in-place: remove dimensions of size 1
    void squeeze_() {
        shape_type new_shape;
        for (size_type dim : shape_) {
            if (dim != 1) {
                new_shape.push_back(dim);
            }
        }
        // If all dimensions were 1, keep at least one dimension
        if (new_shape.empty()) {
            new_shape.push_back(1);
        }
        
        shape_ = move(new_shape);
        compute_strides();
    }

    // Squeeze specific dimension in-place (only if it has size 1)
    void squeeze_(size_type dim) {
        if (dim >= ndim()) {
            throw out_of_range("Dimension index out of range for squeeze.");
        }
        if (shape_[dim] != 1) {
            throw invalid_argument("Cannot squeeze dimension that is not of size 1.");
        }
        
        shape_type new_shape;
        for (size_type i = 0; i < ndim(); ++i) {
            if (i != dim) {
                new_shape.push_back(shape_[i]);
            }
        }
        // If we removed the last dimension, keep at least one dimension
        if (new_shape.empty()) {
            new_shape.push_back(1);
        }
        
        shape_ = move(new_shape);
        compute_strides();
    }

    // Unsqueeze: add a dimension of size 1 at specified position
    Tensor unsqueeze(size_type dim) const {
        if (dim > ndim()) {
            throw out_of_range("Dimension index out of range for unsqueeze.");
        }
        
        shape_type new_shape;
        for (size_type i = 0; i < ndim(); ++i) {
            if (i == dim) {
                new_shape.push_back(1);  // Insert dimension of size 1
            }
            new_shape.push_back(shape_[i]);
        }
        // If dim equals ndim(), add the dimension at the end
        if (dim == ndim()) {
            new_shape.push_back(1);
        }
        
        Tensor result(data_, new_shape);
        return result;
    }

    // Unsqueeze in-place: add a dimension of size 1 at specified position
    void unsqueeze_(size_type dim) {
        if (dim > ndim()) {
            throw out_of_range("Dimension index out of range for unsqueeze.");
        }
        
        shape_type new_shape;
        for (size_type i = 0; i < ndim(); ++i) {
            if (i == dim) {
                new_shape.push_back(1);  // Insert dimension of size 1
            }
            new_shape.push_back(shape_[i]);
        }
        // If dim equals ndim(), add the dimension at the end
        if (dim == ndim()) {
            new_shape.push_back(1);
        }
        
        shape_ = move(new_shape);
        compute_strides();
    }

    // Pretty-print
    friend ostream& operator<<(ostream& os, const Tensor& t) {
        os << "Tensor<>, shape=[";
        for (size_type i = 0; i < t.ndim(); ++i)
            os << t.shape_[i] << (i+1==t.ndim()?"] ":"x ");
        os << "size=" << t.size() << " data=[";
        for (size_type i = 0; i < t.size(); ++i) {
            os << t.data_[i];
            if (i+1 != t.size()) os << ", ";
        }
        os << "]]";
        return os;
    }

private:
    container_type data_;
    shape_type     shape_;
    strides_type   strides_;

    void validate_shape() const {
        for (auto s : shape_)
            if (s == 0) throw invalid_argument("Shape dimensions must be > 0.");
    }

    void compute_strides() {
        strides_.assign(ndim(), 1);
        if (ndim() == 0) return;
        for (size_type i = ndim()-1; i > 0; --i)
            strides_[i-1] = strides_[i] * shape_[i];
    }

    static size_type product(const shape_type& s) {
        return s.empty() ? 0 : accumulate(s.begin(), s.end(), size_type{1}, multiplies<size_type>());
    }

    size_type flat_index_checked(const shape_type& idx) const {
        if (idx.size() != ndim()) throw invalid_argument("Index rank mismatch.");
        size_type off = 0;
        for (size_type i = 0; i < idx.size(); ++i) {
            if (idx[i] >= shape_[i]) throw out_of_range("Index out of bounds.");
            off += idx[i] * strides_[i];
        }
        return off;
    }
};



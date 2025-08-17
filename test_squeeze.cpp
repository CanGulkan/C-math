#include <iostream>
#include "Tensor.h"

using namespace std;

void test_squeeze_unsqueeze() {
    cout << "=== Testing Squeeze and Unsqueeze Methods ===" << endl;
    
    // Test 1: Basic squeeze - remove all dimensions of size 1
    cout << "\n1. Basic squeeze test:" << endl;
    vector<size_t> shape1 = {2, 1, 3, 1, 4};  // Shape: [2, 1, 3, 1, 4]
    Tensor<double> t1(shape1, 5.0);
    
    cout << "Original tensor: " << t1 << endl;
    
    Tensor<double> squeezed = t1.squeeze();
    cout << "After squeeze(): " << squeezed << endl;
    
    // Test 2: Squeeze specific dimension
    cout << "\n2. Squeeze specific dimension test:" << endl;
    vector<size_t> shape2 = {2, 1, 3, 1, 4};  // Shape: [2, 1, 3, 1, 4]
    Tensor<double> t2(shape2, 7.0);
    
    cout << "Original tensor: " << t2 << endl;
    
    // Squeeze dimension 1 (which has size 1)
    Tensor<double> squeezed_dim1 = t2.squeeze(1);
    cout << "After squeeze(1): " << squeezed_dim1 << endl;
    
    // Squeeze dimension 3 (which has size 1)
    Tensor<double> squeezed_dim3 = t2.squeeze(3);
    cout << "After squeeze(3): " << squeezed_dim3 << endl;
    
    // Test 3: In-place squeeze
    cout << "\n3. In-place squeeze test:" << endl;
    vector<size_t> shape3 = {1, 2, 1, 3};  // Shape: [1, 2, 1, 3]
    Tensor<double> t3(shape3, 9.0);
    
    cout << "Before squeeze_(): " << t3 << endl;
    t3.squeeze_();
    cout << "After squeeze_(): " << t3 << endl;
    
    // Test 4: Basic unsqueeze - add dimension at different positions
    cout << "\n4. Basic unsqueeze test:" << endl;
    vector<size_t> shape4 = {2, 3, 4};  // Shape: [2, 3, 4]
    Tensor<double> t4(shape4, 11.0);
    
    cout << "Original tensor: " << t4 << endl;
    
    // Unsqueeze at position 0
    Tensor<double> unsqueezed_0 = t4.unsqueeze(0);
    cout << "After unsqueeze(0): " << unsqueezed_0 << endl;
    
    // Unsqueeze at position 1
    Tensor<double> unsqueezed_1 = t4.unsqueeze(1);
    cout << "After unsqueeze(1): " << unsqueezed_1 << endl;
    
    // Unsqueeze at position 2
    Tensor<double> unsqueezed_2 = t4.unsqueeze(2);
    cout << "After unsqueeze(2): " << unsqueezed_2 << endl;
    
    // Unsqueeze at the end
    Tensor<double> unsqueezed_end = t4.unsqueeze(3);
    cout << "After unsqueeze(3): " << unsqueezed_end << endl;
    
    // Test 5: In-place unsqueeze
    cout << "\n5. In-place unsqueeze test:" << endl;
    vector<size_t> shape5 = {2, 3};  // Shape: [2, 3]
    Tensor<double> t5(shape5, 13.0);
    
    cout << "Before unsqueeze_(1): " << t5 << endl;
    t5.unsqueeze_(1);
    cout << "After unsqueeze_(1): " << t5 << endl;
    
    // Test 6: Squeeze and unsqueeze combination
    cout << "\n6. Squeeze and unsqueeze combination:" << endl;
    vector<size_t> shape6 = {1, 3, 1, 2, 1};  // Shape: [1, 3, 1, 2, 1]
    Tensor<double> t6(shape6, 15.0);
    
    cout << "Original: " << t6 << endl;
    
    auto squeezed_all = t6.squeeze();
    cout << "After squeeze(): " << squeezed_all << endl;
    
    auto back_to_3d = squeezed_all.unsqueeze(0).unsqueeze(2);
    cout << "After unsqueeze(0).unsqueeze(2): " << back_to_3d << endl;
    
    // Test 7: Edge cases
    cout << "\n7. Edge cases:" << endl;
    
    // Tensor with all dimensions of size 1
    vector<size_t> shape7 = {1, 1, 1};  // Shape: [1, 1, 1]
    Tensor<double> t7(shape7, 17.0);
    
    cout << "All 1s tensor: " << t7 << endl;
    auto squeezed_all_ones = t7.squeeze();
    cout << "After squeeze(): " << squeezed_all_ones << endl;
    
    // 1D tensor
    vector<size_t> shape8 = {5};  // Shape: [5]
    Tensor<double> t8(shape8, 19.0);
    
    cout << "1D tensor: " << t8 << endl;
    auto unsqueezed_1d = t8.unsqueeze(0);
    cout << "After unsqueeze(0): " << unsqueezed_1d << endl;
    
    cout << "\n=== All tests completed! ===" << endl;
}

void test_error_cases() {
    cout << "\n=== Testing Error Cases ===" << endl;
    
    try {
        // Try to squeeze a dimension that's not size 1
        vector<size_t> shape1 = {2, 3, 4};
        Tensor<double> t1(shape1, 1.0);
        cout << "Trying to squeeze dimension 1 (size 3) of tensor: " << t1 << endl;
        auto result = t1.squeeze(1);  // Should throw error
    } catch (const exception& e) {
        cout << "Expected error: " << e.what() << endl;
    }
    
    try {
        // Try to squeeze with invalid dimension index
        vector<size_t> shape2 = {2, 3};
        Tensor<double> t2(shape2, 1.0);
        cout << "Trying to squeeze dimension 5 of 2D tensor: " << t2 << endl;
        auto result = t2.squeeze(5);  // Should throw error
    } catch (const exception& e) {
        cout << "Expected error: " << e.what() << endl;
    }
    
    try {
        // Try to unsqueeze with invalid dimension index
        vector<size_t> shape3 = {2, 3};
        Tensor<double> t3(shape3, 1.0);
        cout << "Trying to unsqueeze at dimension 5 of 2D tensor: " << t3 << endl;
        auto result = t3.unsqueeze(5);  // Should throw error
    } catch (const exception& e) {
        cout << "Expected error: " << e.what() << endl;
    }
}

int main() {
    try {
        test_squeeze_unsqueeze();
        test_error_cases();
    }
    catch (const exception& e) {
        cout << "Unexpected error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

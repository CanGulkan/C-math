#include <iostream>
#include "Tensor.h"

using namespace std;

int main() {
    cout << "=== Practical Examples of Squeeze and Unsqueeze ===" << endl;
    
    // Example 1: Image batch processing
    cout << "\n1. Image Batch Processing Example:" << endl;
    cout << "   Converting between different tensor shapes for neural networks" << endl;
    
    // Simulate a batch of 1 RGB image (batch_size=1, height=28, width=28, channels=3)
    vector<size_t> image_shape = {1, 28, 28, 3};
    Tensor<double> image_batch(image_shape, 0.5);
    cout << "   Image batch: " << image_batch << endl;
    
    // Remove batch dimension for single image processing
    Tensor<double> single_image = image_batch.squeeze(0);
    cout << "   Single image (squeezed): " << single_image << endl;
    
    // Add batch dimension back
    Tensor<double> back_to_batch = single_image.unsqueeze(0);
    cout << "   Back to batch (unsqueezed): " << back_to_batch << endl;
    
    // Example 2: Matrix operations with broadcasting
    cout << "\n2. Matrix Broadcasting Example:" << endl;
    cout << "   Preparing tensors for element-wise operations" << endl;
    
    // Create a 2D matrix
    vector<size_t> matrix_shape = {3, 4};
    Tensor<double> matrix(matrix_shape, 2.0);
    cout << "   Matrix: " << matrix << endl;
    
    // Create a 1D vector
    vector<size_t> vector_shape = {4};
    Tensor<double> vector_1d(vector_shape, 0.5);
    cout << "   Vector 1D: " << vector_1d << endl;
    
    // Add dimension to vector for broadcasting (make it row vector)
    Tensor<double> row_vector = vector_1d.unsqueeze(0);
    cout << "   Row vector (unsqueezed): " << row_vector << endl;
    
    // Add dimension to vector for broadcasting (make it column vector)
    Tensor<double> col_vector = vector_1d.unsqueeze(1);
    cout << "   Column vector (unsqueezed): " << col_vector << endl;
    
    // Example 3: Tensor reshaping workflow
    cout << "\n3. Tensor Reshaping Workflow:" << endl;
    cout << "   Common pattern: squeeze -> process -> unsqueeze" << endl;
    
    // Start with a tensor that has unnecessary dimensions
    vector<size_t> original_shape = {1, 5, 1, 3, 1};
    Tensor<double> original(original_shape, 1.0);
    
    // Fill with some pattern
    for (size_t i = 0; i < original.numel(); ++i) {
        *(original.begin() + i) = static_cast<double>(i + 1);
    }
    
    cout << "   Original tensor: " << original << endl;
    
    // Step 1: Remove all singleton dimensions
    Tensor<double> cleaned = original.squeeze();
    cout << "   After squeeze(): " << cleaned << endl;
    
    // Step 2: Reshape for processing (flatten to 1D for this example)
    vector<size_t> flat_shape = {cleaned.numel()};
    cleaned.reshape(flat_shape);
    cout << "   After reshape to 1D: " << cleaned << endl;
    
    // Step 3: Reshape back to 2D for further processing
    vector<size_t> matrix_2d_shape = {5, 3};
    cleaned.reshape(matrix_2d_shape);
    cout << "   Reshaped to 2D: " << cleaned << endl;
    
    // Step 4: Add dimensions back for compatibility with original format
    Tensor<double> final_result = cleaned.unsqueeze(0).unsqueeze(2).unsqueeze(4);
    cout << "   Final result (unsqueezed): " << final_result << endl;
    
    cout << "\n=== Key Benefits ===" << endl;
    cout << "• squeeze(): Removes dimensions of size 1, simplifying tensor operations" << endl;
    cout << "• squeeze(dim): Removes specific dimension of size 1" << endl;
    cout << "• unsqueeze(dim): Adds dimension of size 1 at specified position" << endl;
    cout << "• squeeze_() and unsqueeze_(): In-place versions for memory efficiency" << endl;
    cout << "• Useful for: broadcasting, neural networks, dimension compatibility" << endl;
    
    return 0;
}

#include <iostream>
#include "Tensor.h"

using namespace std;   

int main() {
    // Create a 2×3×4 tensor filled with zeros
    Tensor<float> A({2,3,4}, 0.0f);

    // Assign a value
    A(1,2,3) = 42.0f;

    cout << "ndim = " << A.ndim() << "\n";
    cout << "numel = " << A.numel() << "\n";
    cout << "A(1,2,3) = " << A(1,2,3) << "\n\n";

    // Reshape to (3,8)
    A.reshape({3,8});
    cout << "After reshape:" << endl;
    for (auto v : A) cout << v << " ";
    cout << "\n\n";

    // Print with custom operator<<
    cout << A << endl;

    return 0;
}
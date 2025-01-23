#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <vector>
#include <cmath>
#include <string> 
#include "func.h" 
#include "Matrix.h"  

using namespace std;





int main() {


    cout << "Testing Mathematical Utility Functions\n";
    cout << "--------------------------------------\n";

    // Test func
    cout << "Function Test (func):" << endl;
    cout << "func(2) = " << func(4) << " (Expected: 12)" << endl;

    // Test GCD
    cout << "\nGCD Test:" << endl;
    cout << "gcd(48, 18) = " << gcd(48, 18) << " (Expected: 6)" << endl;

    // Test doubleToFraction
    cout << "\nDouble to Fraction Test:" << endl;
    cout << "doubleToFraction(1.33333) = " << doubleToFraction(1.33333)  << endl;

    // Test False Position Method
    cout << "\nFalse Position Method Test:" << endl; 
    cout << "Root of x^2 - 4 between 1 and 3: "<<endl; 
    falsePositionMethod(1, 3);
    
    // Test Average
    cout << "\nAverage Tests:" << endl;
    cout << "avg(3, 7) = " << avg(3.0, 7.0) << " (Expected: 5)" << endl;

    vector<long double> values = {1.0, 2.0, 3.0, 4.0, 5.0};
    cout << "avg({1, 2, 3, 4, 5}) = " << avg(values) << " (Expected: 3)" << endl;

    // Test Bisection Method
    cout << "\nBisection Method Test:" << endl;
    cout << "Root of x^2 - 4 between 0 and 2: ";
    bisection(1, 3, 10);

    // Test Riemann Sum
    cout << "\nRiemann Sum Test:" << endl;
    cout << "Riemann Sum of x^4 from 0 to 2: " << Riemann_Sum(2, 4) << endl;

    // Test Simpson's Rule
    cout << "\nSimpson's Rule Test:" << endl;
    cout << "Simpson's Rule for x^4 from 0 to 2: " << integral_simson(2, 4) << endl;

    // Test Trapezoidal Rule
    cout << "\nTrapezoidal Rule Test:" << endl;
    cout << "Trapezoidal Rule for x^4 from 0 to 2: " << integral_trapezoidal(2, 4) << endl;

    // Test Derivative
    cout << "\nDerivative Test:" << endl;
    cout << "Derivative of x^2 - 4 at x=2: " << derivative(2) << " (Expected: 4)" << endl;

    // Test Lagrange Interpolation
    cout << "\nLagrange Interpolation Test:" << endl;
    vector<vector<long double>> interpolationPoints = {{1, 1}, {2, 4}, {3, 9}};
    cout << "Lagrange Interpolation at x=1.5: " 
         << lagrange_interpolation(1.5, interpolationPoints) << " (Expected: ~2.25)" << endl;




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




    try {
        cout << "Testing Matrix Class\n";
        cout << "---------------------\n";

        // Test Matrix Construction
        vector<vector<long double>> data1 = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        vector<vector<long double>> data2 = {
            {9, 8, 7},
            {6, 5, 4},
            {3, 2, 1}
        };

        Matrix A(data1);
        Matrix B(data2);

        cout << "Matrix A:\n";
        A.print();

        cout << "\nMatrix B:\n";
        B.print();

        // Test Matrix Addition
        cout << "\nA + B:\n";
        Matrix C = A + B;
        C.print();

        // Test Scalar Multiplication
        cout << "\nA * 2:\n";
        Matrix D = A * 2.0;
        D.print();

        // Test Scalar Division
        cout << "\nA / 2:\n";
        Matrix E = A / 2.0;
        E.print();

        // Test Transpose
        cout << "\nTranspose of A:\n";
        Matrix F = A.transpose();
        F.print();

        // Test Determinant
        cout << "\nDeterminant of A: " << det(A) << endl;
        cout << "Determinant of B: " << det(B) << endl;

        // Test Inverse (on a smaller matrix)
        vector<vector<long double>> invertibleData = {
            {1, 2, 1},
            {3, 1, -2},
            {2, -1, 4}
        };
        Matrix G(invertibleData);

        cout << "\nMatrix G:\n";
        G.print();

        cout << "\nDeterminant of G: " << det(G) << endl;

        if (G.isInvertible()) {
            cout << "Inverse of G:\n";
            Matrix H = G.getinverse();
            H.print();
        } else {
            cout << "Matrix G is not invertible.\n";
        }

        // Test Identity Matrix
        cout << "\nIdentity Matrix (3x3):\n";
        Matrix I(3, 3);
        I.identity();
        I.print();

        // Test Adding Rows and Columns
        vector<long double> newRow = {10, 11, 12};
        I.add_row(newRow);
        cout << "\nAfter adding a row to Identity Matrix:\n";
        I.print();

        vector<long double> newCol = {13, 14, 15, 16};
        I.add_col(newCol);
        cout << "\nAfter adding a column to Identity Matrix:\n";
        I.print();

        // Test Element Access and Update
        cout << "\nElement at (0, 0): " << I.getElementAt(0, 0) << endl;
        I.setElementAt(0, 0, 99);
        cout << "After setting (0, 0) to 99:\n";
        I.print();

        // Test Equality
        cout << "\nAre A and B equal? " << (A == B ? "Yes" : "No") << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }     

    

  


    

    return 0;
}

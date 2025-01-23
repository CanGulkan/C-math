Mathematical Utility Functions & Matrix Operations
This C++ project showcases a collection of mathematical utility functions and matrix operations. The program is designed to test and demonstrate various numerical methods, as well as the functionality of a custom Matrix class. The utilities cover common mathematical operations and numerical methods used in fields such as numerical analysis, calculus, and linear algebra.

Features
Mathematical Utility Functions
func()
A simple function for demonstration purposes. It takes an integer as input and returns a result based on a predefined formula. For example, calling func(2) returns 12.

GCD (Greatest Common Divisor)
Computes the greatest common divisor of two integers using the Euclidean algorithm. The gcd() function is a classic method for determining the largest integer that divides both numbers without leaving a remainder.

Example:

cpp
Copy
Edit
gcd(48, 18) // Expected: 6
doubleToFraction()
Converts a floating-point number to its fractional representation. This function approximates a floating-point number as a ratio of two integers (a fraction). The function uses continued fractions or a similar method for the conversion.

Example:

cpp
Copy
Edit
doubleToFraction(1.33333) // Expected: 4/3
False Position Method
A numerical method to find the root of a nonlinear equation. It is also known as the Regula Falsi method and works by iteratively refining the bounds of the root. The method is efficient for continuous functions and is tested here for the equation x^2 - 4 = 0.

Example:

cpp
Copy
Edit
falsePositionMethod(1, 3) // Finds the root of x^2 - 4 between 1 and 3
Average (avg)
Computes the arithmetic mean of a list of numbers. It can be used for both two values and a vector of values. This method is essential in many applications, such as statistical analysis.

Example:

cpp
Copy
Edit
avg(3.0, 7.0) // Expected: 5
avg({1, 2, 3, 4, 5}) // Expected: 3
Bisection Method
A root-finding algorithm that divides the interval into two halves and selects the subinterval that contains the root. This method is particularly useful for continuous functions that change sign over an interval.

Example:

cpp
Copy
Edit
bisection(1, 3, 10) // Finds the root of x^2 - 4 between 1 and 3 with 10 iterations
Riemann Sum
Approximates the integral of a function over a specified range. The method sums up areas of rectangles under a curve, where each rectangle's height is determined by the function's value at specific points.

Example:

cpp
Copy
Edit
Riemann_Sum(2, 4) // Approximates the integral of x^4 from 0 to 2
Simpson's Rule
Another method for numerical integration, Simpson's Rule approximates the area under a curve using parabolic segments. It is more accurate than the trapezoidal rule for many functions.

Example:

cpp
Copy
Edit
integral_simson(2, 4) // Uses Simpson's Rule to compute the integral of x^4 from 0 to 2
Trapezoidal Rule
A method for numerical integration that approximates the integral by summing the areas of trapezoids. It is simple to implement and works well for smooth functions.

Example:

cpp
Copy
Edit
integral_trapezoidal(2, 4) // Uses the Trapezoidal Rule to compute the integral of x^4 from 0 to 2
Derivative
Computes the derivative of a function at a given point using numerical differentiation. In this project, it calculates the derivative of the function x^2 - 4 at x = 2.

Example:

cpp
Copy
Edit
derivative(2) // Expected: 4
Lagrange Interpolation
A polynomial interpolation method that estimates the value of a function at a given point based on known values at other points. It is particularly useful when dealing with discrete data points.
Example:

cpp
Copy
Edit
lagrange_interpolation(1.5, interpolationPoints) // Expected: ~2.25 for interpolation points {1, 1}, {2, 4}, {3, 9}
Matrix Operations
This project also implements a custom Matrix class that supports a variety of matrix operations.

Matrix Construction
Matrices are created from 2D vectors, allowing users to define any matrix of arbitrary size. The class supports initialization with both square and rectangular matrices.

Example:

cpp
Copy
Edit
Matrix A({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
Matrix Addition
Allows for adding two matrices of the same dimensions. The + operator is overloaded to handle matrix addition.

Example:

cpp
Copy
Edit
Matrix C = A + B; // Adds matrices A and B
Scalar Multiplication
Supports multiplying a matrix by a scalar value. This operation scales each element of the matrix by the given scalar.

Example:

cpp
Copy
Edit
Matrix D = A * 2.0; // Multiplies matrix A by 2
Scalar Division
Allows dividing each element of the matrix by a scalar. This operation is useful when normalizing or scaling matrices.

Example:

cpp
Copy
Edit
Matrix E = A / 2.0; // Divides matrix A by 2
Transpose
Computes the transpose of a matrix, swapping rows and columns. This operation is crucial in many linear algebra applications.

Example:

cpp
Copy
Edit
Matrix F = A.transpose(); // Computes the transpose of matrix A
Determinant
Calculates the determinant of a square matrix. The determinant is an important scalar value used in linear algebra to understand matrix properties, such as invertibility.

Example:

cpp
Copy
Edit
det(A) // Computes the determinant of matrix A
Inverse
Computes the inverse of a matrix, if it is invertible. An invertible matrix has a non-zero determinant and allows for solving linear systems of equations.

Example:

cpp
Copy
Edit
Matrix H = A.getinverse(); // Computes the inverse of matrix A
Identity Matrix
Creates an identity matrix of a given size. The identity matrix is essential in many matrix operations, such as finding the inverse or performing matrix multiplication.

Example:

cpp
Copy
Edit
Matrix I(3, 3); // Creates a 3x3 identity matrix
Add Rows and Columns
Allows users to add new rows and columns to a matrix dynamically. This operation is useful for expanding matrices in real-time calculations.

Example:

cpp
Copy
Edit
I.add_row({10, 11, 12}); // Adds a new row to matrix I
I.add_col({13, 14, 15, 16}); // Adds a new column to matrix I
Element Access and Update
Provides methods to access and update specific elements within the matrix. The user can retrieve and modify individual elements as needed.

Example:

cpp
Copy
Edit
I.getElementAt(0, 0); // Retrieves the element at row 0, column 0
I.setElementAt(0, 0, 99); // Sets the element at row 0, column 0 to 99
Matrix Equality
Checks whether two matrices are equal. The == operator is overloaded to compare matrices element-wise.
Example:

cpp
Copy
Edit
A == B // Checks if matrices A and B are equal
How to Use
Compilation:
To compile the project, you will need a C++ compiler that supports C++11 or later. Example using g++:

bash
Copy
Edit
g++ -o math_util main.cpp Matrix.cpp func.cpp
Running the Program:
After compilation, run the program with the following command:

bash
Copy
Edit
./math_util
The program will perform various tests, displaying the results for each of the mathematical methods and matrix operations defined above.

Example Output
Here is an example output after running the program:

sql
Copy
Edit
Testing Mathematical Utility Functions
--------------------------------------
Function Test (func):
func(2) = 12 (Expected: 12)

GCD Test:
gcd(48, 18) = 6 (Expected: 6)

Double to Fraction Test:
doubleToFraction(1.33333) = 4/3

False Position Method Test:
Root of x^2 - 4 between 1 and 3:
...

Testing Matrix Class
---------------------
Matrix A:
1 2 3
4 5 6
7 8 9

Matrix B:
9 8 7
6 5 4
3 2 1

Matrix A + B:
10 10 10
10 10 10
10 10 10

...
Requirements
C++11 or later: The project utilizes features from the C++11 standard, such as lambda expressions and initializer lists.
C++ Compiler: A compatible C++ compiler (e.g., g++).
License
This project is licensed under the MIT License - see the LICENSE file for details
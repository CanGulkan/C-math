#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Matrix {
public:
    
    Matrix() : row(0), col(0), mtx(0, vector<long double>(0, 0)) {
        
    }

    Matrix(vector<vector<long double>> exp) {

        if (exp.empty()) {
            throw invalid_argument("Matrix is empty, cannot determine column size.");
        }
        if (exp[0].empty()) {
            throw invalid_argument("Matrix is empty, cannot determine column size.");
        }


        row = exp.size(); 
        col = exp[0].size();  
        
        mtx.resize(row, vector<long double>(col));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) { 
                mtx[i][j] = exp[i][j];  
            }
        }
        
    }
    
    Matrix(int x, int y) : row(x), col(y), mtx(x, vector<long double>(y, 0)) {
        if (x <= 0 || y <= 0) {
         throw invalid_argument("Matrix dimensions must be positive integers.");
        }
    }

    Matrix(int r, int c , vector<vector<long double>>& data) : row(r), col(c), mtx(r, vector<long double>(c)) { 
    
        if (r <= 0 || c <= 0) {
            throw invalid_argument("Matrix dimensions must be positive integers.");
        }
    
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) { 
                mtx[i][j] = data[i][j]; 
            }
        }
    
    }


    void display(){

        for (const auto& row : mtx) { 
            for (const auto& elem : row) {
               cout << elem << " ";
            }
            cout << endl;
        }

    }


    void print() {
    // Print the top border of the matrix (adjusted to be wider)
    //cout << "+-----------------------------------------+" << endl;

    cout << "+";
    for(int i=0;i<14*col-1;i++){
        cout << "-";
    }
    cout << "+" << endl;
    
    // Iterate through each row
    for (const auto& row : mtx) {
        cout << "| "; // Start of row
        // Iterate through each element in the row
        for (const auto& elem : row) {
            // Print the fraction with center alignment
            cout << setw(7) << internal << doubleToFraction(elem)<< setw(7) << " | ";
        }
        cout << endl;

        // Print a separator line after each row
        cout << "+";
        for(int i=0;i<14*col-1;i++){
           cout << "-";
        }
       
        cout << "+" << endl;

       // cout << "+-----------------------------------------+" << endl;
    }
    cout <<endl;
    }
    
    void fillMatrix() {
        cout << "Enter matrix elements: \n";
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cin >> mtx[i][j];
            }
        }
    }

    Matrix operator+(const Matrix& other) { 

	if(other.getCol() != col || other.getRow() != row){
		throw runtime_error("Matrix dimensions do not match for addition!");
	} 

	Matrix result(row, col); 

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result.mtx[i][j] = mtx[i][j] + other.mtx[i][j];
		}
	}


	return result; 
    }

    bool operator==(const Matrix& other) {
	if (other.getCol() != col || other.getRow() != row) {
		cout << "erorr";
		return 0;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (mtx[i][j] != other.mtx[i][j]) {
				return 0;
			}
		}
	}

	return 1;
    }

    void operator=(const Matrix& other) {
	if (this == &other) return; // Handle self-assignment
    if (other.getCol() != col || other.getRow() != row) {
        throw runtime_error("Matrix dimensions do not match for assignment.");
    }

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			
			mtx[i][j] = other.mtx[i][j];
				
		}
	}
    }

    Matrix operator+(const long double scalar) const { 
	Matrix result(row, col);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			result.mtx[i][j] = this->mtx[i][j] + scalar;
		}
	}
	return result;
    }


    Matrix operator*(const long double scalar) const {
	Matrix result(row, col);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			result.mtx[i][j] = mtx[i][j] * scalar; 
		}
	}
	return result;
    }

    Matrix operator/(const long double scalar) const {
	if (scalar == 0) {
		throw runtime_error("Division by zero!"); 
	}
	Matrix result(row, col);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			result.mtx[i][j] = mtx[i][j] / scalar;
		}
	}
	return result;
    }



    Matrix transpose() const {

    vector<vector<long double>> transposed(col, vector<long double>(row));

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            transposed[j][i] = mtx[i][j];
        }
    }
    return Matrix(transposed);
    }


    // Recursive helper function for determinant calculation 
    long double determinantRecursive(const vector<vector<long double>>& matrix) const {
        if (row != col) {
         throw invalid_argument("Matrix must be square .");
        }
        int n = matrix.size();
        if (n == 1) {
            return matrix[0][0];  // Base case: 1x1 matrix
        }
        if (n == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];  // 2x2 case
        }

        long double det = 0;

        for (int i = 0; i < n; i++) {
            vector<vector<long double>> minor = getMinorMatrix(matrix, 0, i);  // Get the minor matrix
            det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinantRecursive(minor);
        }

        return det;
    }


    // Get the minor of a matrix by excluding the given row and column
    vector<vector<long double>> getMinorMatrix(const vector<vector<long double>>& matrix, int row, int col) const {
        vector<vector<long double>> minor;
        for (int i = 0; i < matrix.size(); i++) {
            if (i == row) continue;
            vector<long double> newRow;
            for (int j = 0; j < matrix[i].size(); j++) {
              if (j == col) continue;
              newRow.push_back(matrix[i][j]);
            }
        minor.push_back(newRow);
        }
    return minor;
    }

    void identity() { 

	if (row != col) {
		cout << "Identity matrix is only for square matrices!" << endl;
		return;
	}

	for (int i = 0; i < row; i++) {

		for (int j = 0; j < row; j++) {
			
			if (i == j) {
				mtx[i][j] = 1; 
			}
			else{
				mtx[i][j] = 0;  
			}
			
		}

    }

    }
    
    bool isInvertible() {
    	if (det(*this) == 0) {
	    	return 0;
	    }
	    else {
		    return 1;
	    }
    }

    bool isSingular() { 
	    if (det(*this) == 0) {
		    return 1;
	    }
	    else {
		    return 0;
	    }
    }



    void add_row(vector<long double>& new_row){ 

        // add empty condition
        if (new_row.empty()) {
            throw invalid_argument("The new row must not be empty.");
        }
 
        if (col != new_row.size()) {
            throw invalid_argument("Row length must be equal to col. ");
        }


        
        mtx.push_back(new_row);
        row++;

    }

    void add_col(vector<long double>& new_col) {
    // Check if the new column is empty
    if (new_col.empty()) {
        throw invalid_argument("The new column must not be empty.");
    }

    // Ensure the new column size matches the number of rows
    if (row != new_col.size()) {
        throw invalid_argument("The number of elements in the new column must match the number of rows.");
    }

    // Add the new column to each row of the matrix
    for (int i = 0; i < row; i++) {
        mtx[i].push_back(new_col[i]);
    }

    // Increment the column count
    col++;
    }

    void setElementAt(int row1, int col1, long double elem) {
	    if (row1 < 0 || row1 >= row || col1 < 0 || col1 >= col) {
		    throw runtime_error("Index out of bounds!");
	    }
	

	mtx[row1][col1] = elem;
    }

    long double getElementAt(int row1, int col1) {
	    if (row1 < 0 || row1 >= row || col1 < 0 || col1 >= col) {
		    throw runtime_error("Index out of bounds!");
	    }
	

	return mtx[row1][col1];
    }

    // Getters
    int getRow() const { return row; }
    int getCol() const { return col; }
    vector<vector<long double>> getMatrix() const { return mtx; } 

    Matrix getCofMatrix() const {
	if (row != col) {
		throw runtime_error("Cofactor matrix can only be computed for square matrices!");
	}

	Matrix result(row, col); 

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result.setElementAt(i, j, getCofactor(i, j));
		}
	}

	return result;
    }

    Matrix getSubMatrix(int rowToExclude, int colToExclude) const { 
	    Matrix subMatrix(row - 1, col - 1);
	    for (int i = 0, subRow = 0; i < row; i++) {
	    	if (i == rowToExclude) continue;
		    for (int j = 0, subCol = 0; j < col; j++) {
			    if (j == colToExclude) continue;
			    subMatrix.mtx[subRow][subCol++] = mtx[i][j];
		    }
		subRow++;
	    }
	return subMatrix;
    } 

    long double getMinor(int rowToExclude, int colToExclude) const {
	return det(getSubMatrix(rowToExclude, colToExclude));
    }

    long double getCofactor(int rowToExclude, int colToExclude) const { 
	return ((rowToExclude + colToExclude) % 2 == 0 ? 1 : -1) * getMinor(rowToExclude, colToExclude);
    }

    Matrix getinverse() const {
	    if (det(*this)==0) {
		    throw runtime_error("Matrix is not invertible!");
	    }
	    Matrix cofactorMatrix = this->getCofMatrix().transpose();
	    long double deter = det(*this); 
	    Matrix result(row, col);
	    for (int i = 0; i < row; ++i) {
		    for (int j = 0; j < col; ++j) {
		    	result.setElementAt(i, j, cofactorMatrix.getMatrix()[i][j] / static_cast<long double>(deter));
		    }
	    }
	return result;
    }

    void inverse(){
        Matrix temp = this->getinverse();
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                mtx[i][j] = temp.getElementAt(i,j);
            }
        }

    }
    
    friend void printMatrix(const Matrix& mat);
    friend long double det(const Matrix& mat);

        // Destructor
    ~Matrix() = default;


private:
    // Member variables
    vector<vector<long double>> mtx;  // Renamed for clarity 
    int row, col;              // Renamed for clarity
};

long double det(const Matrix& mat) {
    return mat.determinantRecursive(mat.getMatrix());
}

void printMatrix(const Matrix& mat){
    
    for (const auto& row : mat.getMatrix()) {    
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }

}

#endif  // MATRIX_H

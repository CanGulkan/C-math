#ifndef FUNC_H
#define FUNC_H

using namespace std;

// Function implementations
long double func(long double x) { 

    long double result;

    result = pow(x,2)-4;   // x^2 - 4

    return result;
}



// Custom GCD function 
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

string doubleToFraction(double value, int maxDenominator = 1000) {
    long long bestNumerator = 0, bestDenominator = 1;
    double bestError = abs(value);

    for (int denominator = 1; denominator <= maxDenominator; ++denominator) {
        long long numerator = round(value * denominator);
        double error = abs(value - static_cast<double>(numerator) / denominator);

        if (error < bestError) {
            bestError = error;
            bestNumerator = numerator;
            bestDenominator = denominator;

            // Stop early if the error is negligible
            if (bestError < 1e-6) break;
        }
    }

    // Simplify the fraction using the custom GCD function
    long long divisor = gcd(bestNumerator, bestDenominator);
    bestNumerator /= divisor;
    bestDenominator /= divisor;
    
    if(bestDenominator == 1 ){
        return to_string(bestNumerator);
    }

    if(bestDenominator < 0){
        bestDenominator *= -1;
        bestNumerator *= -1;
    }
    
    return to_string(bestNumerator) + "/" + to_string(bestDenominator);
}


long double falsePositionMethod(long double a, long double b, int iter = 10, long double epsilon = 1e-7) {
    if (func(a) * func(b) >= 0) {
        cerr << "Error: The function values at the endpoints must have opposite signs." << endl;
        return NAN; // Return not-a-number to indicate failure
    }

    long double ref = a; // Initial approximation
    long double fa = func(a), fb = func(b); // Store function values

    for (int i = 0; i < iter; i++) {
        ref = (a * fb - b * fa) / (fb - fa); // Calculate the false position

        long double fref = func(ref); // Compute function value at ref
        //cout << "Iteration " << i << ": X = " << ref << " | f(X) = " << fref << endl;
         cout << "X" << i << " = " << ref << " | " << "f(X" << i << ")=" << fref << endl; 

        // Check for convergence
        if (fabs(fref) < epsilon || fabs(b - a) < epsilon) {
            cout << "Converged to root: " << ref << " after " << i + 1 << " iterations." << endl;
            return ref;
        }

        // Update the interval
        if (fref * fa < 0) {
            b = ref;
            fb = fref;
        } else {
            a = ref;
            fa = fref;
        }
    }

    cout << "Reached maximum iterations. Approximate root: " << ref << endl;
    return ref;
}

long double avg(long double m,long double n) {

    return (m + n) / 2;

}

long double avg(vector<long double> arr) {
    long double sum=0;
    for(int i=0;i<arr.size();i++){
    sum+=arr[i];
    }

    return sum / arr.size();

}

long double bisection(int _a, int _b, int inter) {
    long double lower = _a;
    long double upper = _b;
    long double ref;

    // Check if the root exists in the interval
    if (func(lower) * func(upper) > 0) {
        cout << "The function does not have opposite signs at the ends of the interval. No root guaranteed." << endl;
        return NAN;
    }

    cout << fixed << setprecision(10); // Set output precision
    for (int i = 0; i < inter; i++) {
        ref = (lower + upper) / 2.0; // Calculate midpoint
        long double f_ref = func(ref);

        cout << "P" << i << "= " << ref << " | f(P" << i <<") = " << f_ref << endl;

        if (abs(f_ref) < 1e-9) { // Check for convergence
            break;
        }

        if (f_ref > 0) {
            upper = ref;
        } else {
            lower = ref;
        }
    }

    return ref; // Return the approximated root
}


long double Riemann_Sum (int start , int end, int partition = 1000000) {

    long double area = 0;
     
    long double rate = (end - start) / (long double) partition;

    long double x = start;

    for (int i = 0; i < partition-1;i++) {

        area += func(x + rate) * rate; 
        
        x = x + rate;
    }

    return area;

}

long double integral_simson(long double start, long double end, int n = 10) {
    if (n % 2 == 1) {
        n++; // Make n even
    }

    long double h = (end - start) / n; // Step size
    long double sum_odd = 0;             // Sum for odd indices
    long double sum_even = 0;             // Sum for even indices

    // Summation for odd terms
    for (int i = 1; i < n; i += 2) {
        sum_odd += func(start + i * h);
    }

    // Summation for even terms
    for (int i = 2; i < n; i += 2) {
        sum_even += func(start + i * h); 
    }

    // Calculate the area using Simpson's rule
    long double area = (h / 3) * (func(start) + 4 * sum_odd + 2 * sum_even + func(end));
    return area;
}

long double integral_trapezoidal(long double start, long double end, int n = 10) {
    if (n % 2 == 1) {
        n++; // Make n even
    }

    long double h = (end - start) / n; // Step size
    long double sum = 0;             // Sum 
   

    
    for (int i = 1; i <= n-1; i++) {
        sum += func(start + i * h); 
    }

    long double area = (h / 2) * (func(start) + 2 * sum + func(end));
    return area;
}

long double derivative (long double x,long double h = 0.0001) {

    return (func(x + h) - func(x - h)) / (2*h);  

}


long double lagrange_interpolation(double x, const vector<vector<long double>>& matrix) {

    int n = matrix.size() - 1;

    if (n<1) {
        cout << " Error " << endl;
        return -1; 
    }

    long double sum=0;

    for (int i = 0; i <= n;i++) {

        long double Li = 1; 
        for (int j = 0; j <= n;j++) {
            
            if (j==i) {
                continue;
            }

            Li *= ((x)-matrix[j][0]) / (matrix[i][0] - matrix[j][0]);

        }
        sum += Li * matrix[i][1];

    }
    return sum;
}


#endif // FUNC_H

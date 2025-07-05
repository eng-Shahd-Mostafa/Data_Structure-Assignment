#include <iostream>
#include <fstream>

using namespace std;

class Polynomial {
public:
    int* coefficients; // Array to store coefficients of the polynomial
    int size; // Size of the coefficient array (degree + 2)

    // Constructor to initialize the polynomial with a given size
    Polynomial(int sz) 
    {
        size = sz + 2; // Adding extra space to store coefficients
        coefficients = new int[size](); // Dynamically allocate array and initialize with zeros
    }

    // Destructor to deallocate memory
    ~Polynomial()
    {
        delete[] coefficients;
    }

    // Display the polynomial in human-readable form
    void display(int order)
    {
        bool firstTerm = true; // To track whether we are printing the first term
        for (int i = size - 1; i >= 0; i--)
        {
            if (i == 0 && !firstTerm) // If last term is reached, print "=" sign before the constant
            {
                cout << " = " << coefficients[i];
                break;
            }

            if (coefficients[i] == 0) // If coefficient is zero, skip it
            {
                order--;
                continue;
            }

            if (!firstTerm) // If it is not the first term, print "+" or "-" sign based on the coefficient
            {
                if (coefficients[i] < 0)
                {
                    cout << " - ";
                }

                else 
                {
                    cout << " + ";
                }
            }

            if (firstTerm) // Handle sign of the first term separately
            {
                if (coefficients[i] < 0)
                {
                    cout << " - ";
                }
            }
            int coefficient = abs(coefficients[i]); // Get absolute value for proper display

            if (coefficient != 1 || order == 0) // Print coefficient unless it's 1 and not the constant term
            {
                cout << coefficient;
            }

            if (order > 0) // Print variable and its power if order is greater than 0
            {
                cout << "x";
                if (order > 1)
                {
                    cout << "^" << order << ' ';
                }

                else
                {
                    cout << ' ';
                }
            }
            order--;
            firstTerm = false; // Mark that first term has been printed
        }
        cout << endl;
    }

    // Check if all coefficients are zero (i.e., the polynomial is zero)
    bool iSallZero() const
    {
        for (int i = 0; i < size; i++)
        {
            if (coefficients[i] != 0) return false;
        }
        return true;
    }

    Polynomial add(const Polynomial& other)
    {
        int maxSize = max(size, other.size); // Determine the larger polynomial
        Polynomial sum(maxSize - 2); // Create a new polynomial to store the sum

        // Copy coefficients from the first polynomial
        for (int i = 0; i < size; i++)
        {
            sum.coefficients[i] = coefficients[i];
        }

        // Add coefficients from the second polynomial
        for (int i = 0; i < other.size; i++)
        {
            sum.coefficients[i] += other.coefficients[i];
        }
        return sum;
    }

    Polynomial subtract(const Polynomial& other) const
    {
        int maxSize = max(size, other.size); // Determine the larger polynomial
        Polynomial diff(maxSize - 2); // Create a new polynomial to store the difference

        // Copy coefficients from the first polynomial
        for (int i = 0; i < size; i++)
        {
            diff.coefficients[i] = coefficients[i];
        }

        // Subtract coefficients from the second polynomial
        for (int i = 0; i < other.size; i++)
        {
            diff.coefficients[i] -= other.coefficients[i];
        }
        return diff;
    }
};

int main() {
    string filename;
    cout << "Enter the filename (with .txt extension): ";
    cin >> filename;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int szA, szB;

    // Read first polynomial
    file >> szA;
    Polynomial poly1(szA);
    for (int i = 0; i < szA + 2; i++) // Read coefficients into the polynomial object
    {
        file >> poly1.coefficients[i];
    }

    if (!poly1.iSallZero()) // Check before printing
    { 
        cout << "First Polynomial: ";
        poly1.display(szA);
    }

    // Read second polynomial
    file >> szB;
    Polynomial poly2(szB);
    for (int i = 0; i < szB + 2; i++) // Read coefficients into the polynomial object
    {
        file >> poly2.coefficients[i];
    }

    if (!poly2.iSallZero()) // Check before printing
    {  
        cout << "Second Polynomial: ";
        poly2.display(szB);
    }

    // Perform addition
    Polynomial sum = poly1.add(poly2);
    if (!sum.iSallZero())  // Check if the result is not zero before displaying
    {  
        cout << "Sum of Polynomials: ";
        sum.display(sum.size - 2);
    }

    // Perform subtraction
    Polynomial diff = poly2.subtract(poly1);
    if (!diff.iSallZero()) // Check if the result is not zero before displaying
    { 
        cout << "Difference of Polynomials: ";
        diff.display(diff.size - 2);
    }

    file.close();
    return 0;
}

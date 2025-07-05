#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <string>
using namespace std;

template <typename T>
class StatisticalCalculation {
private:
    T* data;  // Pointer to dynamically allocated array
    int size; // Size of the array
public:
    // Constructor: Allocates memory for the given size
    StatisticalCalculation(int size) : size(size) {
        data = new T[size];
    }
    // Destructor: free memory
    ~StatisticalCalculation() {
        delete[] data;
    }

    // Sorts the array in ascending order using Selection Sort algorithm
    void sort() {
        for (int i = 0; i < size - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < size; j++) {
                if (data[j] < data[minIndex]) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                T temp = data[i];
                data[i] = data[minIndex];
                data[minIndex] = temp;
            }
        }
    }

    // Getting the median 
    double findMedian() {
        sort(); // Sorting before finding the median
        if (size % 2 == 0)
            return (data[size / 2 - 1] + data[size / 2]) / 2.0;
        else
            return data[size / 2];
    }

    // Return the minimum value
    T findMin() {
        T minVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] < minVal)
                minVal = data[i];
        }
        return minVal;
    }

    // Return the maximum value
    T findMax() {
        T maxVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > maxVal)
                maxVal = data[i];
        }
        return maxVal;
    }

    // Calculate the mean; always returns double regardless of T
    double findMean() {
        T sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i];
        }
        return static_cast<double>(sum) / size;
    }

    // Calculate the summation
    T findSummation() {
        T sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i];
        }
        return sum;
    }

    // Print the array elements
    void displayArray() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Get input for the data array
    void inputData() {
        cout << "Enter " << size << " elements:" << endl;
        for (int i = 0; i < size; i++) {
            cin >> data[i];
        }
        // To clear the leftover newline after numeric input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //read input from txt file
    void inputDatafile(string filename) {
        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Error: Could not open file." << endl;
            exit(1);
        }

        inputFile >> size;
        for (int i = 0; i < size; i++) {
            if (!(inputFile >> data[i])) {
                cerr << "Error: Not enough data in file." << endl;
                exit(1);
            }
        }

        inputFile.close();
    }


    // Provides a menu for statistical operations
    void statisticsMenu() {
        int choice;
        string choiceInput;
        do {
            cout << "\nStatistical Operations Menu:\n";
            cout << "1. Sort Data\n";
            cout << "2. Find Median\n";
            cout << "3. Find Min\n";
            cout << "4. Find Max\n";
            cout << "5. Find Mean\n";
            cout << "6. Find Summation\n";
            cout << "7. Display Data\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";
            
            getline(cin, choiceInput);
            try {
                size_t pos;
                choice = stoi(choiceInput, &pos);
                if (pos != choiceInput.length())
                    throw invalid_argument("Invalid input: extra characters found.");
            } catch (const exception& e) {
                cout << "Invalid input! Please enter a valid option between 1 and 8." << endl;
                continue;
            }
        
            switch (choice) {
                case 1:
                    sort();
                    cout << "Data sorted successfully!" << endl;
                    break;
                case 2:
                    cout << "Median: " << findMedian() << endl;
                    break;
                case 3:
                    cout << "Minimum Value: " << findMin() << endl;
                    break;
                case 4:
                    cout << "Maximum Value: " << findMax() << endl;
                    break;
                case 5:
                    cout << "Mean: " << findMean() << endl;
                    break;
                case 6:
                    cout << "Summation: " << findSummation() << endl;
                    break;
                case 7:
                    displayArray();
                    break;
                case 8:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice! Try again." << endl;
            }
        } while (choice != 8);
    }
};

int main() {
    int option;
    string input;

    // Data type selection menu
    cout << "Select Data Type:\n";
    cout << "1. int\n";
    cout << "2. double\n";
    cout << "Enter your choice: ";
    while (true) {
        getline(cin, input);
        try {
            size_t pos;
            option = stoi(input, &pos);
            if (pos != input.length() || (option != 1 && option != 2))
                throw invalid_argument("Invalid choice.");
            break;
        } catch (const exception& e) {
            cout << "Invalid input! Please enter '1' for int or '2' for double: ";
        }
    }

    // Choose input method
    cout << "Choose the way to input your data:\n";
    cout << "1. Input via txt file\n";
    cout << "2. Input manually\n";
    cout << "Enter your choice: ";
    
    int ch;
    while (true) {
        getline(cin, input);
        try {
            size_t pos;
            ch = stoi(input, &pos);
            if (pos != input.length() || (ch != 1 && ch != 2))
                throw invalid_argument("Invalid choice.");
            break;
        } catch (const exception& e) {
            cout << "Invalid input! Please enter '1' for file input or '2' for manual input: ";
        }
    }

    int size;
    
    if (ch == 2) {
        // Get number of elements
        cout << "Enter the number of elements: ";
        while (true) {
            getline(cin, input);
            try {
                size_t pos;
                size = stoi(input, &pos);
                if (pos != input.length() || size <= 0)
                    throw invalid_argument("Invalid input! Enter a positive integer.");
                break;
            } catch (const exception& e) {
                cout << "Invalid input! Enter a positive integer: ";
            }
        }

        // Execute based on selected data type
        if (option == 1) {
            StatisticalCalculation<int> stats(size);
            stats.inputData();
            stats.statisticsMenu();
        } else if (option == 2) {
            StatisticalCalculation<double> stats(size);
            stats.inputData();
            stats.statisticsMenu();
        }
    } else if (ch == 1) {
        // File input case
        cout << "Enter the filename: ";
        string filename;
        getline(cin, filename);

        // Open the file to read the size first
        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Error: Could not open file." << endl;
            exit(1);
        }
        int fileSize;
        inputFile >> fileSize;
        inputFile.close();

        // Construct the object with the correct size
        if (option == 1) {
            StatisticalCalculation<int> stats(fileSize);
            stats.inputDatafile(filename);
            stats.statisticsMenu();
        } else if (option == 2) {
            StatisticalCalculation<double> stats(fileSize);
            stats.inputDatafile(filename);
            stats.statisticsMenu();
        }
    }

    return 0;
}

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

int exceptionHandling(ifstream& file, const string& label) 
{
    int value;
    if (!(file >> value))
    {
        throw runtime_error("Invalid input for " + label + ". File must contain only valid numbers.");
    }

    cout << label << ": " << value << endl;
    return value;
}


int minKBitFlips(int* nums, int n, int k) 
{
    int r = 0, ans = 0;
    int* flips = new int[n];
    int head = 0, tail = 0;

    while (r + k - 1 < n) 
    {
        while (head < tail && flips[head] + k - 1 < r) head++;
        int num_flips = tail - head;
        int cur = (num_flips & 1) ? !nums[r] : nums[r];

        if (cur == 0) 
        {
            ans++;
            if (tail < n) flips[tail++] = r;
            else
            {
                delete[] flips;
                return -1;
            }
        }
        r++;
    }

    while (r < n)
    {
        while (head < tail && flips[head] + k - 1 < r) head++;
        int num_flips = tail - head;
        int cur = (num_flips & 1) ? !nums[r] : nums[r];

        if (cur == 0) 
        {
            delete[] flips;
            return -1;
        }
        r++;
    }

    delete[] flips;
    return ans;
}

int main()
{
    string filename;
    cout << "Enter the name of the input file: \n";
    cin>>filename;
    ifstream file(filename);

    if (!file.is_open()) 
    {
        cerr << "Error: Could not open the file.\n";
        return 1;
    }

    try {

        int n = exceptionHandling(file, "Array size");
        if (n <= 0) throw runtime_error("Array size must be greater than 0.");

        int* arr = new int[n];
        cout << "Reading array elements:" << '\n';
        for (int i = 0; i < n; i++) 
        {
            int val = exceptionHandling(file, "   Element [" + to_string(i) + "]");
            if (val != 0 && val != 1) 
            {
                throw runtime_error("Invalid array element. Only 0 or 1 allowed.");
            }

            arr[i] = val;
        }
        cout << '\n';

        int k = exceptionHandling(file, "   k -> value");
        if (k <= 0 || k > n) 
        {
            throw runtime_error("k must be between 1 and " + to_string(n) + ".");
        }

        cout << "Calculating minKBitFlips...\n";
        int result = minKBitFlips(arr, n, k);
        cout << "   Result: " << result << endl;

        delete[] arr;
    }
    catch (const exception& e) 
    {
        cerr << e.what() << endl;
        return 1;
    }

    file.close();
    return 0;
}

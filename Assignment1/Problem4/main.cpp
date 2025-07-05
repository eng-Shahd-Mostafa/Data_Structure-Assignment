#include <bits/stdc++.h>
#define ll long long
#define all(a) a.begin(), a.end()
#define allr(a) a.rbegin(), a.rend()
#define vi vector<int>
#define vll vector<ll>
#define vss vector<string>
#define el '\n'
#define pb push_back
#define st string
#define clos 3
#define an &&
#define loop for (int i=0;i<n;i++)
#define awoo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
//# include "SORTING_SYSTEM.h"
template <typename T>
class SortingSystem{
private:
    T* data;
    int size;
public:
    //template <typename T>
    SortingSystem(int n) {
        size = n;
        data = new T[size];
        string filename = "file.txt";
        ifstream file(filename);

        if (!file) {
            cerr << "Error: Could not open file " << filename << endl;
            exit(1);
        }

        for (int i = 0; i < size; i++) {
            T temp;
            if (!(file >> temp)) {  // Check if the input matches type T
                cerr << "Error: File data does not match the expected type!" << endl;
                exit(1);
            }
            data[i] = temp;
        }

        file.close();
    }

    ~SortingSystem() {
        delete[] data;
    }
///////////////////-> insertionSort()
    //template <typename T>
    void insertionSort() {
        cout << "Starting Insertion Sort...\n";
        for (int i = 1; i < size; i++) {
            T num = data[i];
            int inx = i;
            cout << "\nIteration " << i << ":"<<el;
            cout << "Current element: " << num <<el;
            cout << "Array before insertion: ";
            for (int j = 0; j < size; j++) {
                cout << data[j] << " ";
            }
            cout << endl;
            while (inx > 0 && num < data[inx - 1]) {
                data[inx] = data[inx - 1];
                inx--;
            }
            data[inx] = num;
            cout << "Array after insertion: ";
            for (int j = 0; j < size; j++) {
                cout << data[j] << " ";
            }
            cout <<el;
        }
        cout << el;
        cout << "Final Sorted Array: ";
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
    }
///////////////////-> bubbleSort()
    //template <typename T>
    void bubbleSort()
    {
        for(int i=0;i<size-1;i++)
        {bool f=0;
            for(int  j=0;j<size-i-1;j++)
            {
                if (data[j]>data[j+1]){swap(data[j],data[j+1]); f=1;}
            } std::cout << "Iteration " << i + 1 << ": ";
            print(data,size);
            if (!f)break;
            else if (f)f=0;
        }
        cout << el;
        cout << "Final Sorted Array: ";
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << el;
    }
////////////////////////////
//--------------------->>selectionSort()
    //template<class T>
    void selectionSort() {
        cout << "Starting Selection Sort"<<el;
        for (int i = 0; i < size - 1; i++) {
            int mn = i;
            cout << "\nIteration " << i + 1 << ":\n";
            cout << "Current minimum element: " << data[mn] << "\n";
            cout << "Array before selection: ";
            for (int k = 0; k < size; k++) {
                cout << data[k] << " ";
            }
            cout << endl;
            for (int j = i + 1; j < size; j++) {
                if (data[mn] > data[j]) {
                    mn = j;
                }
            }

            if (i != mn) {
                cout << "Swapping " << data[i] << " and " << data[mn] << "\n";
                swap(data[mn], data[i]);
            }
            cout << "Array after selection: ";
            for (int k = 0; k < size; k++) {
                cout << data[k] << " ";
            }
            cout << endl;
        }
        cout << el;

        cout << "Final Sorted Array: ";
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << el;
    }
//--------------------->>shellSort()
////////////////////////////////////////
    //template <typename T>
    void shellSort()
    {

        for(int gap=size/2;gap>0;gap/=2)
        {
            for(int j=gap;j<size;j++)
            {cout<<"gap = "<<gap;
                cout<<el;
                for(int i=j-gap;i>=0;i-=gap)
                {
                    cout << "    Comparing data[" << i << "] = " << data[i]
                         << " and data[" << i + gap << "] = " << data[i + gap] << ": ";
                    for (int k = 0; k < size; k++) {
                        cout << data[k] << " ";
                    }
                    cout << el;

                    if (data[i+gap]>=data[i]) { cout << "    No swap needed (data[" << i + gap << "] >= data[" << i << "])\n";break;}
                    else {swap (data[i],data[i+gap]);cout << "    Swapped data[" << i << "] and data[" << i + gap << "]: ";
                        for (int k = 0; k < size; k++) {
                            cout << data[k] << " ";
                        }
                        cout << el;}
                }
            }
        }

        cout << el;
        cout << "Final Sorted Array: ";
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << el;

    }
//////////////////////////////////
//--------------------->>mergeSort()
    //template<class T>
    void merge(int left, int mid, int right )
    {
        ll lSize=mid-left+1;ll rSize=right-mid;
        T ldata[lSize]; T rdata[rSize];
        for(ll i=0,k=left;i<lSize;i++,k++){
            ldata[i]=data[k];
        }
        for(int j=0,k=mid+1;j<rSize;j++,k++)
        {
            rdata[j]=data[k];

        }
        ll i=0,j=0,k=left;
        cout << "Merging: ";
        printArrayML(data, left, right); //
        while (i<lSize an j <rSize)
        {
            if (ldata[i]<rdata[j])
            {
                data[k]=ldata[i];
                i++,k++;
            }
            else
            {
                data[k]=rdata[j];
                j++,k++;

            }
        }
        while(i <lSize)
        { data[k]=ldata[i];
            i++,k++;

        }
        while(j <rSize)
        {  data[k]=rdata[j];
            j++,k++;
        }cout << "After merging: ";
        printArrayML(data, left, right);
        cout << "----------------------------------\n";
    }
////////////////////////////////
    //template <class T>
    void  mergeSort(int left,int right)
    {if (left>=right)return;
        else {
            int mid = (left + right) / 2;
            cout << "Dividing left subdataay: ";
            printArrayML(data, left, mid);
            cout << "Dividing right subdataay: ";
            printArrayML(data, mid + 1, right);
            cout << "----------------------------------\n";
            mergeSort(left, mid);
            mergeSort(mid + 1, right);
            cout << "Merging subdataays: ";
            printArrayML(data, left, right);
            merge(left,mid,right);
            cout << "After merging: ";
            printArrayML(data, left, right);
            cout << "----------------------------------\n";
        }
        cout << el;
    }
///////////////////////////
//---------------------->>quickSort
    //template <class T>
    void quickSort( int left, int right)
    {
        if (left < right)
        {  cout << "\nCurrent array: ";
            printArrayQ(data, left, right);
            //  printArrayQ(data,left, right);

            int mid = partition(left, right);
            cout << "Pivot: " << data[mid] << " at index " << mid << endl;

            cout << "Sorting left part: [" << left << " to " << mid - 1 << "]\n";
            quickSort(left, mid - 1);

            cout << "Sorting right part: [" << mid + 1 << " to " << right << "]\n";
            quickSort(mid + 1, right);

        }


    }
//////////////////////
    //template <class T>
    int   partition(int low, int high)
    {
        T pivot = data[high];
        cout << "\nPartitioning with pivot " << pivot << " at index " << high << endl;
        ll indx = low-1 ;
        for (ll i = low; i < high ; i++)
        {
            if (data[i] < pivot)
            {
                indx++;
                swap(data[i], data[indx]); cout << "Swapped " << data[indx] << " and " << data[i] << " -> ";
                printArrayQ(data,low, high);
            }
        }
        swap(data[indx + 1], data[high]);
        cout << "Moved pivot to index " << indx + 1 << " -> ";
        printArrayQ(data,low, high);
        return ++indx ;
    }
/////////////////
    //template <class T>
    void countSort(){
        if constexpr (is_same<T, int>::value){
            int mx = *max_element(data, data + size);
            int siz = mx + 1;
            int* freq = new int[siz]();
            cout << "Step 1: Frequency array initialized "<<el;
            cout << "Frequency array: ";
            for (int i = 0; i < siz; i++) {
                cout << freq[i] << " ";
            }
            cout << endl << endl;
            cout << "Step 2: Counting occurrences of each element"<<el;
            for (int i = 0; i < size; i++) {
                freq[data[i]]++;
                cout << "Element " << data[i] << " found. Frequency array updated: ";
                for (int j = 0; j < siz; j++) {
                    cout << freq[j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            cout << "Step 3: Reconstructing the sorted array."<<el;;
            int idx = 0;
            for (int i = 0; i < siz; i++) {
                while (freq[i] > 0) {
                    data[idx] = i;
                    cout << "Placing element " << i << " at index " << idx << ". Current array: ";
                    for (int j = 0; j < size; j++) {
                        cout << data[j] << " ";
                    }
                    cout << endl;
                    idx++;
                    freq[i]--;
                }
            }
            cout << endl;
            cout << el;
            cout << "Final Sorted Array: ";
            for (int i = 0; i < size; ++i) {
                cout << data[i] << " ";
            }
            cout << el;
            delete[] freq;
        }
        else {cerr << "Count Sort only supports integers!" << endl;}
    }
//////////////////////////////////////
    //template <typename T>
    void radixSort() {
        if constexpr (is_same<T, int>::value) {
            cout << "Starting Radix Sort"<<el;
            int digit = 1;
            int mx = *max_element(data, data + size);
            while (mx > 0) {
                cout << "Sorting based on digit place: " << digit << el;
                CountSort2(data, size, digit);
                digit *= 10;
                mx /= 10;
            }
            cout << el;
            cout << "Final Sorted Array: ";
            for (int i = 0; i < size; ++i) {
                cout << data[i] << " ";
            }
            cout << el;
        }
        else {
            cerr << "Count Sort only supports integers!" << endl;
        }
    }
///////////////////////////////
    //template <typename T>
    int getBucketIndex(T value, T minValue, T maxValue, int numBuckets) {
        if (maxValue == minValue) return 0;
        return ((value - minValue) * (numBuckets - 1)) / (maxValue - minValue);
    }

//////////////////////////
    // template <typename T>
    void  BucketSort() {
        int NUM_BUCKETS = is_same<T, string>::value ? 26 : 10;  // عدد الباكتات حسب نوع البيانات

        cout << "\n=== Starting Bucket Sort ===\n";

        T minValue = data[0], maxValue = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] < minValue) minValue = data[i];
            if (data[i] > maxValue) maxValue = data[i];
        }

        T** buckets = new T * [NUM_BUCKETS];
        int* bucketSizes = new int[NUM_BUCKETS]();
        for (int i = 0; i < NUM_BUCKETS; ++i) {
            buckets[i] = new T[size];
        }

        cout << "\nDistributing elements into buckets:\n";
        for (int i = 0; i < size; ++i) {
            int index = getBucketIndex(data[i], minValue, maxValue, NUM_BUCKETS) % NUM_BUCKETS; // تصحيح الحساب
            buckets[index][bucketSizes[index]++] = data[i];
            cout << "Placed element " << data[i] << " into bucket " << index << "\n";
        }

        cout << "\nBuckets before sorting:\n";
        for (int i = 0; i < NUM_BUCKETS; i++) {
            cout << "Bucket[" << i << "] : ";
            for (int j = 0; j < bucketSizes[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nSorting each bucket using Insertion Sort...\n";
        for (int i = 0; i < NUM_BUCKETS; ++i) {
            if (bucketSizes[i] > 1) {
                InsertionSort(buckets[i], bucketSizes[i]);
            }
        }

        cout << "\nBuckets after sorting:\n";
        for (int i = 0; i < NUM_BUCKETS; i++) {
            cout << "Bucket[" << i << "] : ";
            for (int j = 0; j < bucketSizes[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nReassembling sorted elements into the original dataay...\n";
        int index = 0;
        for (int i = 0; i < NUM_BUCKETS; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                data[index++] = buckets[i][j];
            }
        }
        cout << el;
        cout << "Final Sorted Array: ";
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << el;

        for (int i = 0; i < NUM_BUCKETS; ++i) {
            delete[] buckets[i];
        }
        delete[] buckets;
        delete[] bucketSizes;



    }
////////////////////////////////
#include <functional> // Add this include for std::function

    //template <typename T>
    void measureSortTime(std::function<void()> sortFunc) {
        auto start = chrono::high_resolution_clock::now(); // Start time
        sortFunc(); // Call the sorting function
        auto end = chrono::high_resolution_clock::now(); // End time

        chrono::duration<double> elapsed = end - start; // Calculate elapsed time
        cout << "Time taken: " << elapsed.count() << " seconds" << endl;
    }
////////////////////////
    // template <typename T>
    void displayData() {
        for(int i=0;i<size;i++) {
            cout << data[i] << " ";
        }
        cout << el;
    }
/////////////////////////
    //template <typename T>
    void showMenu() {
        int choice;
        do {
            cout << "\nSorting Algorithm Menu:\n";
            cout << "1. Insertion Sort\n";
            cout << "2. Selection Sort\n";
            cout << "3. Bubble Sort\n";
            cout << "4. Shell Sort\n";
            cout << "5. Merge Sort\n";
            cout << "6. Quick Sort\n";
            cout << "7. Count Sort (int only)\n";
            cout << "8. Radix Sort (int only)\n";
            cout << "9. Bucket Sort ()\n";
            cout << "10. Display Data\n";
            cout << "11. Measure Sorting Time\n";
            cout << "12. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;
            cout << endl;

            switch (choice) {
                case 1:
                    insertionSort();
                    break;
                case 2:
                    selectionSort();
                    break;
                case 3:
                    bubbleSort();
                    break;
                case 4:
                    shellSort();
                    break;
                case 5:
                    mergeSort(0, size - 1);
                    break;
                case 6:
                    quickSort(0, size - 1);
                    break;
                case 7:
                    if constexpr (is_same<T, int>::value) {
                        countSort();
                    } else {
                        cout << "Count Sort is only available for int type.\n";
                    }
                    break;
                case 8:
                    if constexpr (is_same<T, int>::value) {
                        radixSort();
                    } else {
                        cout << "Radix Sort is only available for int type.\n";
                    }
                    break;
                case 9:
                    BucketSort();
                    break;
                case 10:
                    displayData();
                    break;
                case 11: // Measure sorting time
                {
                    int sortChoice;
                    cout << "\nSelect a sorting algorithm to measure time:\n";
                    cout << "1. Insertion Sort\n";
                    cout << "2. Selection Sort\n";
                    cout << "3. Bubble Sort\n";
                    cout << "4. Shell Sort\n";
                    cout << "5. Merge Sort\n";
                    cout << "6. Quick Sort\n";
                    cout << "7. Count Sort (int only)\n";
                    cout << "8. Radix Sort (int only)\n";
                    cout << "9. Bucket Sort ()\n";
                    cout << "Choose an option: ";
                    cin >> sortChoice;
                    cout << endl;

                    switch (sortChoice) {
                        case 1:
                            measureSortTime([this]() { insertionSort(); });
                            break;
                        case 2:
                            measureSortTime([this]() { selectionSort(); });
                            break;
                        case 3:
                            measureSortTime([this]() { bubbleSort(); });
                            break;
                        case 4:
                            measureSortTime([this]() { shellSort(); });
                            break;
                        case 5:
                            measureSortTime([this]() { mergeSort(0, size - 1); });
                            break;
                        case 6:
                            measureSortTime([this]() { quickSort(0, size - 1); });
                            break;
                        case 7:
                            if constexpr (is_same<T, int>::value) {
                                measureSortTime([this]() { countSort(); });
                            } else {
                                cout << "Count Sort is only available for int type.\n";
                            }
                            break;
                        case 8:
                            if constexpr (is_same<T, int>::value) {
                                measureSortTime([this]() { radixSort(); });
                            } else {
                                cout << "Radix Sort is only available for int type.\n";
                            }
                            break;
                        case 9:
                            measureSortTime([this]() { BucketSort(); });
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                }
                    break;
                case 12:
                    cout << "Exiting menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 12);
    }

/////////////////////////
    //template <typename T>
    void InsertionSort(T arr[], int size) {
        for (int i = 1; i < size; ++i) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
// Function to print an array
    // template <typename T>
    void print(T arr[], int size) {
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;}






    void printArrayQ(T arr[], int s, int e)
    {
        cout << "[ ";
        for (int i = s; i <= e; i++) {
            cout << data[i] << " ";
        }
        cout << "]" << endl;
    }

    void printArrayML(T arr[], int s, int e)
    {
        for (ll i = s; i <=e; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
//    void print (T arr[],int n)
//    {
//        loop cout<<arr[i]<<" ";
//        cout<<el;
//    }

    ////////////////////////
    void CountSort2(int arr[], int n, int digit) {
        if constexpr (is_same<T, int>::value) {
            const int mx = 9; // Maximum digit value (0-9)
            int size = mx + 1;
            int *freq = new int[size](); // Frequency array
            int *output = new int[n](); // Output array (initialized to 0)

            cout << "\nStep 1: Counting occurrences of each digit (digit place: " << digit << ").\n";
            for (int i = 0; i < n; i++) {
                int value = (arr[i] / digit) % 10; // Extract the digit
                freq[value]++;
                cout << "Element " << arr[i] << " has digit " << value << ". Frequency array: ";
                for (int j = 0; j < size; j++) {
                    cout << freq[j] << " ";
                }
                cout << endl;
            }
            cout << endl;

            cout << "Step 2: Cumulative frequency array.\n";
            for (int i = 1; i < size; i++) {
                freq[i] += freq[i - 1];
                cout << "Cumulative frequency at " << i << ": " << freq[i] << endl;
            }
            cout << endl;

            cout << "Step 3: Building the output array.\n";
            for (int i = n - 1; i >= 0; i--) {
                int value = (arr[i] / digit) % 10; // Extract the digit
                output[freq[value] - 1] = arr[i]; // Place the element in the correct position
                freq[value]--;
                cout << "Placing element " << arr[i] << " at index " << freq[value] << ". Output array: ";
                for (int j = 0; j < n; j++) {
                    cout << output[j] << " ";
                }
                cout << endl;
            }
            cout << endl;

            cout << "Step 4: Copying the output array back to the original array.\n";
            for (int i = 0; i < n; i++) {
                arr[i] = output[i];
            }
            cout << "Array after sorting by digit place " << digit << ": ";
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
            }
            cout << endl << endl;

            // Clean up
            delete[] freq;
            delete[] output;
        }
        else {
            cerr << "Count Sort only supports integers!" << endl;
        }
    }

/////////////////////////////////



};

template <>
int SortingSystem<string>::getBucketIndex(string value, string minValue, string maxValue, int numBuckets) {
    return (toupper(value[0]) - 'A') % numBuckets;
}
/////////////////////////////////////////////////
void showTypeMenu() {
    cout << "Select data type:\n";
    cout << "1. int\n";
    cout << "2. double\n";
    cout << "3. char\n";
    cout << "4. string\n";
    cout << "Enter choice: ";
}
int main() {
    char repeat;
    do {
        int choice, size;
        showTypeMenu();
        cin >> choice;
        cout << "Enter number of elements: ";
        cin >> size;

        switch (choice) {
            case 1:
            {
                SortingSystem<int> sorter(size);
                sorter.showMenu();
            }
            break;
            case 2:
            {
                SortingSystem<double> sorter(size);
                sorter.showMenu();
            }
            break;
            case 3:
            {
                SortingSystem<char> sorter(size);
                sorter.showMenu();
            }
            break;
            case 4:
            {
                SortingSystem<string> sorter(size);
                sorter.showMenu();
            }
            break;
            default:
                cout << "Invalid choice!" << endl;
        }

        cout << "Do you want to sort another dataset? (y/n): ";
        cin >> repeat;

    } while (repeat == 'y' || repeat == 'Y');
    cout << "Thank you for using the sorting system. Goodbye!\n";
}







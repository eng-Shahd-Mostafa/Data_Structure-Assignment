#include <iostream>
#include <cassert>
#include "StatisticalCalculation.h"  // Include the header file for StatisticalCalculation

using namespace std;

int main() {
    cout << "Running extended test cases..." << endl;

    // Test Case 1: Typical Case
    {
        StatisticalCalculation<int> stats(5);
        int input[] = {3, 1, 4, 2, 5};
        for (int i = 0; i < 5; i++) stats.data[i] = input[i];
        stats.sort();
        assert(stats.findMedian() == 3);
        assert(stats.findMin() == 1);
        assert(stats.findMax() == 5);
        assert(stats.findMean() == 3.0);
        assert(stats.findSummation() == 15);
    }

    // Test Case 2: Single Element Array
    {
        StatisticalCalculation<int> stats(1);
        stats.data[0] = 10;
        assert(stats.findMedian() == 10);
        assert(stats.findMin() == 10);
        assert(stats.findMax() == 10);
        assert(stats.findMean() == 10.0);
        assert(stats.findSummation() == 10);
    }

    // Test Case 3: Empty Array (Edge Case)
    // {
    //     try {
    //         StatisticalCalculation<int> stats(0);
    //         stats.findMedian(); // Should throw an exception
    //         assert(false); // Should not reach here
    //     } catch (...) {
    //         // Expected behavior
    //     }
    // }

    // Test Case 4: Duplicate Values
    {
        StatisticalCalculation<int> stats(6);
        int input[] = {2, 2, 2, 2, 2, 2};
        for (int i = 0; i < 6; i++) stats.data[i] = input[i];
        stats.sort();
        assert(stats.findMedian() == 2);
        assert(stats.findMin() == 2);
        assert(stats.findMax() == 2);
        assert(stats.findMean() == 2.0);
        assert(stats.findSummation() == 12);
    }

    // Test Case 5: Alternating Positive and Negative
    {
        StatisticalCalculation<int> stats(6);
        int input[] = {-1, 1, -2, 2, -3, 3};
        for (int i = 0; i < 6; i++) stats.data[i] = input[i];
        stats.sort();
        assert(stats.findMedian() == 0);
        assert(stats.findMin() == -3);
        assert(stats.findMax() == 3);
        assert(stats.findMean() == 0.0);
        assert(stats.findSummation() == 0);
    }

    // Test Case 6: Zeroes Only
    {
        StatisticalCalculation<int> stats(5);
        int input[] = {0, 0, 0, 0, 0};
        for (int i = 0; i < 5; i++) stats.data[i] = input[i];
        stats.sort();
        assert(stats.findMedian() == 0);
        assert(stats.findMin() == 0);
        assert(stats.findMax() == 0);
        assert(stats.findMean() == 0.0);
        assert(stats.findSummation() == 0);
    }

    // Test Case 7: Increasing Order
    {
        StatisticalCalculation<int> stats(6);
        int input[] = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < 6; i++) stats.data[i] = input[i];
        stats.sort();
        assert(stats.findMedian() == 3.5);
        assert(stats.findMin() == 1);
        assert(stats.findMax() == 6);
        assert(stats.findMean() == 3.5);
        assert(stats.findSummation() == 21);
    }

    // Test Case 8: Decreasing Order
    {
        StatisticalCalculation<int> stats(6);
        int input[] = {6, 5, 4, 3, 2, 1};
        for (int i = 0; i < 6; i++) stats.data[i] = input[i];
        stats.sort();
        assert(stats.findMedian() == 3.5);
        assert(stats.findMin() == 1);
        assert(stats.findMax() == 6);
        assert(stats.findMean() == 3.5);
        assert(stats.findSummation() == 21);
    }

    // Test Case 9: Minimal Positive and Negative
    {
        StatisticalCalculation<int> stats(3);
        int input[] = {1, 0, -1};
        for (int i = 0; i < 3; i++) stats.data[i] = input[i];
        stats.sort();
        assert(stats.findMedian() == 0);
        assert(stats.findMin() == -1);
        assert(stats.findMax() == 1);
        assert(stats.findMean() == 0.0);
        assert(stats.findSummation() == 0);
    }

    // Test Case 10: Floating-Point Precision
    {
        StatisticalCalculation<double> stats(4);
        double input[] = {1.5, 2.5, 3.5, 4.5};
        for (int i = 0; i < 4; i++) stats.data[i] = input[i];
        stats.sort();
        assert(abs(stats.findMedian() - 3.0) < 1e-6);
        assert(abs(stats.findMin() - 1.5) < 1e-6);
        assert(abs(stats.findMax() - 4.5) < 1e-6);
        assert(abs(stats.findMean() - 3.0) < 1e-6);
        assert(abs(stats.findSummation() - 12.0) < 1e-6);
    }

    cout << "All extended test cases passed!" << endl;
    return 0;
}

#include<iostream>
#include <fstream>
using namespace std;

const int MAX_SIZE = 40;

struct patient
{
	string name;
	int severity;
	int arrivalTime;
};

bool higherPriority(patient p1, patient p2)
{
	if (p1.severity != p2.severity)
		return p1.severity > p2.severity;
	return p1.arrivalTime < p2.arrivalTime;

}

class maxHeap
{
	patient heap[MAX_SIZE];
	int size;

	void heapifyUp(int index)
	{
		while (index > 0)
		{
			int parent = (index - 1) / 2;
			if (higherPriority(heap[index], heap[parent]))
			{
				swap(heap[index], heap[parent]);
				index = parent;
			}
			else
				break;
		}
	}

	void heapifyDown(int index)
	{
		while (index < size) {
			int left = 2 * index + 1;
			int right = 2 * index + 2;
			int largest = index;

			if (left < size && higherPriority(heap[left], heap[largest]))
				largest = left;
			if (right < size && higherPriority(heap[right], heap[largest]))
				largest = right;

			if (largest != index) {
				swap(heap[index], heap[largest]);
				index = largest;
			}
			else break;
		}
	}

public:
	maxHeap()
	{
		size = 0;
	}

	void insert(patient p)
	{
		if (size == MAX_SIZE)
		{
			cout << "Heap is full" << endl;
			return;
		}

		else if (size == 0)
		{
			heap[size] = p;
			size++;
		}

		else
		{
			heap[size] = p;
			heapifyUp(size);
			size++;
		}
	}

	patient extractMax()
	{
		if (size == 0)
		{
			cout << "Heap is empty" << endl;
			return { "", -1, -1 };
		}

		patient maxPatient = heap[0];
		heap[0] = heap[size - 1];
		size--;
		heapifyDown(0);
		return maxPatient;
	}

	patient peek()
	{
		if (size == 0)
			return { "", -1, -1 };
		return heap[0];
	}

	void printHeap() {
		for (int i = 0; i < size; ++i) {
			cout << heap[i].name << " ";
		}
		cout << endl;
	}

	bool isEmpty() {
		return size == 0;
	}
};

int main()
{
	maxHeap emergencyQueue;
	string filename;
	cout << "Enter the file name ,please: " << endl;
	cin >> filename;
	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		cerr << "Error opening file!" << endl;
		return 1;
	}

	cout << "------ Insertions ------" << endl;
	string name;
	int severity, arrivalTime;
	while (inputFile >> name >> severity >> arrivalTime) {
		patient p = { name, severity, arrivalTime };
		cout << "Inserting: " << p.name << endl;
		emergencyQueue.insert(p);
		cout << "Heap: ";
		emergencyQueue.printHeap();
		cout << "--------------------------" << endl;
	}

	cout << "\n------ Treatment Order ------" << endl;
	while (!emergencyQueue.isEmpty()) {
		patient next = emergencyQueue.extractMax();
		cout << "Treating: " << next.name << endl;
	}

	return 0;
}
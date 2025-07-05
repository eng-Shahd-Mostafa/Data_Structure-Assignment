#include<iostream>

using namespace std;

class Node
{
public:
    int data; // Stores the value of the node
    Node* next; // Pointer to the next node in the list
    Node(int val);  // Constructor to initialize the node with a value
}; 

class SortedLinkedList
{
private:
    Node* head; // Pointer to the head of the list

public:
    SortedLinkedList(); 
    void insert(int value); // Insert a new element in the list in sorted order
    void remove(int index); // Remove an element at a specific index
    int operator[](int index); // Overloaded operator to access elements by index
    friend ostream& operator<<(ostream& os, const SortedLinkedList& list); // Overloaded operator to print the list
    ~SortedLinkedList();
};

Node::Node(int val)
{
    data = val; // Store the given value in the node
    next = NULL; // Set `next` to NULL since this is the last node initially
}

SortedLinkedList::SortedLinkedList()
{
    head = NULL; // Initialize the head pointer to NULL
}

void SortedLinkedList::insert(int value)
{
    // Create a new node with the given value
    Node* newnode = new Node(value); 

    // If the list is empty or the value is less than the head node's value, insert at the beginning
    if (head == NULL || head->data >= value)
    {
        newnode->next = head;
        head = newnode;
    }

    else
    {
        Node* temp = head;

        // Find the correct position to insert the new node
        while (temp->next != NULL && temp->next->data < value)
        {
            temp = temp->next;
        }

        // Insert the new node in the correct position
        newnode->next = temp->next;
        temp->next = newnode;
    }
}

void SortedLinkedList::remove(int index)
{
    if (!head) // Check if the list is empty
    {
        cerr << "Error: List is empty, cannot remove index " << index << "." << endl;
        return;
    }

    if (index < 0) // Ensure index is not negative
    {
        cerr << "Error: Index " << index << " is out of range!" << endl;
        return;
    }

    if (index == 0) // If index is 0, remove the head node
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head; 
    Node* previous = nullptr;
    int currentIndex = 0;

    // Traverse the list to find the node at the given index
    while (current)
    {
        if (currentIndex == index) // If the current node is the one to be removed
        {
            previous->next = current->next;
            delete current;
            return;
        }
        previous = current;
        current = current->next;
        currentIndex++;
    }

    cerr << "Error: Index " << index << " is out of range!" << endl;
}

int SortedLinkedList::operator[](int index)
{
    if (index < 0) // Ensure index is non-negative
    {
        cerr << "Error: Index " << index << " is out of range!" << endl;
        throw out_of_range("out of range");
    }

    Node* temp = head;
    int count = 0;

    while (temp != NULL)
    {
        if (index == count) // If the current node is the one at the given index
        {
            return temp->data;
        }

        count++;
        temp = temp->next;
    }

    cerr << "Error: Index " << index << " is out of range!" << endl; // If the index is out of range
    throw out_of_range("out of range");
}

ostream& operator<<(ostream& os, const SortedLinkedList& list)
{
    Node* temp = list.head;
    os << "[";
    
    while (temp) // Iterate through the list and print each element
    {
        os << temp->data;
        if (temp->next)
        {
            os << ", ";
        }
        temp = temp->next;
    }

    os << "]";
    return os;
}

SortedLinkedList::~SortedLinkedList()
{
    Node* temp = head;

    while (temp != NULL)
    {
        head = head->next;
        delete temp;
        temp = head;
    }
}

void run_tests()
{
    SortedLinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(-6);
    list.insert(7);
    list.insert(8);
    list.insert(9);
    list.insert(10);
    cout << "The content of the list is: " << endl;
    cout << list << endl;
    list.remove(5);

    cout << "The content of the list is: " << endl;
    cout << list << endl;
    list.remove(1);

    cout << "The content of the list is: " << endl;
    cout << list << endl;

    cout << "The content of the list[1] is: " << endl;
    cout << list[1] << endl;

    cout << "The content of the list[4] is: " << endl;
    cout << list[4] << endl;
}

int main()
{
    cout << "Running Test Cases...\n\n";
    run_tests();
    cout << "All tests completed.\n";
    return 0;
}

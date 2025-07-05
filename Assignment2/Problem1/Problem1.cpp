#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <typename T>
class stack 
{
private:
    T* data;
    size_t c;
    size_t cz;

    void resize() 
    {
        c *= 2;
        T* temp = new T[c];
        for (int i = 0; i < cz; ++i) 
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
public:
    stack() : c(1), cz(0) 
    {
        data = new T[c];
    }

    ~stack() 
    {
        delete[] data;
    }

    bool empty() const
    {
        return cz == 0;
    }

    void push(const T& v) 
    {
        if (cz + 1 >= c)
        {
            resize();
        }
        data[cz++] = v;
    }

    void pop() 
    {
        if (!empty())
            --cz;
    }

    T operator--(int) 
    {
        T temp = data[cz - 1];
        pop();
        return temp;
    }

    T& top() 
    {
        return data[cz - 1];
    }
};

class browserHistory 
{
public:
    stack<string> backStack;
    stack<string> forwardStack;
    string currentPage;

    browserHistory(string homepage) 
    {
        currentPage = homepage;
    }

    void visit(string url) 
    {
        backStack.push(currentPage);
        currentPage = url;
        while (!forwardStack.empty()) 
        {
            forwardStack.pop();
        }
    }

    string goBack(int steps) 
    {
        while (steps-- > 0 && !backStack.empty()) 
        {
            forwardStack.push(currentPage);
            currentPage = backStack--;  // use overloaded post-decrement
        }
        return currentPage;
    }

    string goForward(int steps) 
    {
        while (steps-- > 0 && !forwardStack.empty()) 
        {
            backStack.push(currentPage);
            currentPage = forwardStack--;  // use overloaded post-decrement
        }
        return currentPage;
    }
};

int main() 
{
    string filename;
    cout << "Enter the name of the file: \n";
    cin >> filename;

    ifstream infile(filename);
    if (!infile) 
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    browserHistory* browser = nullptr;

    while (getline(infile, line)) 
    {
        istringstream iss(line);
        string command, argument;
        int steps;

        iss >> command;
        if (command == "homepage") 
        {
            iss >> argument;
            browser = new browserHistory(argument);
        }

        else if (command == "visit") 
        {
            iss >> argument;
            browser->visit(argument);
        }

        else if (command == "back") 
        {
            iss >> steps;
            cout << browser->goBack(steps) << endl;
        }

        else if (command == "forward") 
        {
            iss >> steps;
            cout << browser->goForward(steps) << endl;
        }
    }

    delete browser;
    return 0;
}

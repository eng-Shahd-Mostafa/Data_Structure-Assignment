#include <iostream>
#include <fstream>
#include <string>
#include<functional>
#include<sstream>
#include<limits>

#define el '\n'
#define st string
using namespace std;

class person
{
private:
    int id;
    st name, phone, mail;

public:
    void setID(int Id)
    {
        id = Id;
    }

    void setName(const string& Name)
    {
        name = Name;
    }

    void setPhone(const string& Phone)
    {
        phone = Phone;
    }

    void setEmail(const string& Email)
    {
        mail = Email;
    }

    int getID() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    string getPhone() const
    {
        return phone;
    }

    string getEmail() const
    {
        return mail;
    }

};

class node
{
public:
    node* left = nullptr;
    node* right = nullptr;
    person data;
    int height = 1;

};

class AVL
{
public:
    node* root = nullptr;

    int height(node* root)
    {
        if (root == nullptr) return 0;
        return root->height;
    }

    int checkBalance(node* root)
    {
        if (root == nullptr) return 0;
        return height(root->left) - height(root->right);
    }

    void updateHeight(node* root)
    {
        if (root == nullptr) return;
        root->height = max(height(root->left), height(root->right)) + 1;
    }

    node* rightRotate(node* root)
    {
        if (root == nullptr || root->left == nullptr)
            return root;

        node* leftTemp = root->left;
        node* importCase = leftTemp->right;
        leftTemp->right = root;
        root->left = importCase;

        updateHeight(root);
        updateHeight(leftTemp);

        return leftTemp;
    }

    node* leftRotate(node* root)
    {
        if (root == nullptr || root->right == nullptr)
            return root;

        node* rightTemp = root->right;
        node* importCase = rightTemp->left;
        rightTemp->left = root;
        root->right = importCase;

        updateHeight(root);
        updateHeight(rightTemp);
        return rightTemp;
    }

    node* insert(node* root, person& p)
    {
        if (root == nullptr)
        {
            node* newNode = new node;
            newNode->data = p;
            newNode->height = 1;
            return newNode;
        }

        if (p.getID() < root->data.getID())
            root->left = insert(root->left, p);

        else if (p.getID() > root->data.getID())
            root->right = insert(root->right, p);

        else
            return root; // Duplicate ID, ignore

        updateHeight(root);
        int balance = checkBalance(root);


        if (balance > 1 && p.getID() < root->left->data.getID())
            return rightRotate(root);


        if (balance < -1 && p.getID() > root->right->data.getID())
            return leftRotate(root);


        if (balance > 1 && p.getID() > root->left->data.getID())
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }


        if (balance < -1 && p.getID() < root->right->data.getID())
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    node* maxNode(node* root)
    {
        if (root == nullptr) return nullptr;
        if (root->right == nullptr) return root;
        return maxNode(root->right);
    }

    node* deleteNode(node* root, int key)
    {
        if (root == nullptr)
            return root;

        if (key < root->data.getID())
            root->left = deleteNode(root->left, key);

        else if (key > root->data.getID())
            root->right = deleteNode(root->right, key);

        else
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }

            if (root->right == nullptr)
            {
                node* temp = root->left;
                delete root;
                return temp;
            }

            else if (root->left == nullptr)
            {
                node* temp = root->right;
                delete root;
                return temp;
            }

            node* need = maxNode(root->left);
            root->data = need->data;
            root->left = deleteNode(root->left, need->data.getID());
        }

        updateHeight(root);
        int balance = checkBalance(root);
        if (balance > 1 && checkBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance < -1 && checkBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance > 1 && checkBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && checkBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void insertPerson(person& n)
    {
        if (Search(n.getID()))
        {
            cout << "Error: Contact with ID " << n.getID() << " already exists." << el;
            return;
        }

        root = insert(root, n);
    }

    void listAll() const
    {
        if (root == nullptr)
        {
            cout << "Address Book is empty." << el;
            return;
        }

        cout << "Contacts in Address Book (sorted by ID)" << el;
        inOrder(root);
    }

    void inOrder(node* node) const
    {
        if (node == nullptr) return;
        inOrder(node->left);
        printContact(node);
        inOrder(node->right);
    }

    void printContact(node* node) const
    {
        cout << "ID: " << node->data.getID()
            << ", Name: " << node->data.getName()
            << ", Phone: " << node->data.getPhone()
            << ", Email: " << node->data.getEmail() << el;
    }

    bool search(node* root, int e)
    {
        if (root == nullptr)
            return false;

        if (e == root->data.getID())
            return true;

        if (e < root->data.getID())
            return search(root->left, e);

        return search(root->right, e);
    }

    bool Search(int key)
    {
        return search(root, key);
    }

    void deleteContact(int key)
    {
        if (search(root, key))
        {
            root = deleteNode(root, key);
            cout << "Contact with ID " << key << " deleted." << el;
        }

        else
        {
            cout << "Contact with ID " << key << " not found in the tree." << el;
        }
    }

    void printTree()
    {
        if (!root)
        {
            cout << "Tree is empty\n";
            return;
        }

        const int MAX_HEIGHT = 10;
        const int MAX_NODES = 1 << MAX_HEIGHT;
        string* levels[MAX_HEIGHT];
        int levelSizes[MAX_HEIGHT] = { 0 };


        for (int i = 0; i < MAX_HEIGHT; i++)
        {
            levels[i] = new string[MAX_NODES];

            for (int j = 0; j < MAX_NODES; j++)
            {
                levels[i][j] = " ";
            }
        }

        function<void(node*, int, int)> collectNodes = [&](node* root, int level, int pos)
            {
                if (!root || level >= MAX_HEIGHT)
                    return;

                levels[level][pos] = to_string(root->data.getID());
                levelSizes[level] = max(levelSizes[level], pos + 1);

                // Left child at 2*pos, right child at 2*pos+1
                collectNodes(root->left, level + 1, 2 * pos);
                collectNodes(root->right, level + 1, 2 * pos + 1);
            };

        collectNodes(root, 0, 0);


        int h = height(root);
        for (int i = 0; i < h; i++)
        {
            int spaces = (1 << (h - i - 1)) - 1;
            int between = (1 << (h - i)) - 1;

            for (int s = 0; s < spaces; s++)
                cout << " ";

            for (int j = 0; j < levelSizes[i]; j++)
            {
                cout << levels[i][j];
                for (int s = 0; s < between; s++) cout << " ";
            }

            cout << el;

            if (i < h - 1)
            {
                for (int s = 0; s < spaces - 1; s++)
                    cout << " ";

                for (int j = 0; j < levelSizes[i]; j++)
                {
                    bool hasLeft = (i + 1 < h) && (2 * j < levelSizes[i + 1]) && (levels[i + 1][2 * j] != " ");
                    bool hasRight = (i + 1 < h) && (2 * j + 1 < levelSizes[i + 1]) && (levels[i + 1][2 * j + 1] != " ");

                    cout << (hasLeft ? "/" : " ");
                    for (int s = 0; s < between / 2; s++)
                        cout << " ";

                    cout << (hasRight ? "\\" : " ");
                    for (int s = 0; s < between / 2; s++)
                        cout << " ";
                }
                cout << el;
            }
        }


        for (int i = 0; i < MAX_HEIGHT; i++)
        {
            delete[] levels[i];
        }
    }

    void loadFromFile(const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error opening file: " << filename << el;
            return;
        }

        string line;
        int loadedCount = 0;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            person p;
            int id;
            string name, phone, email;

            try
            {
                string id_str;
                if (!getline(ss, id_str, ','))
                {
                    cout << "Error: Bad format (missing ID): " << line << el;
                    continue;
                }

                id = stoi(id_str);

                if (!getline(ss, name, ','))
                {
                    cout << "Error: Bad format (missing name): " << line << el;
                    continue;
                }

                if (!getline(ss, phone, ','))
                {
                    cout << "Error: Bad format (missing phone): " << line << el;
                    continue;
                }

                if (!getline(ss, email))
                {
                    cout << "Error: Bad format (missing email): " << line << el;
                    continue;
                }

                name.erase(0, name.find_first_not_of(" \t\r\n"));
                name.erase(name.find_last_not_of(" \t\r\n") + 1);

                phone.erase(0, phone.find_first_not_of(" \t\r\n"));
                phone.erase(phone.find_last_not_of(" \t\r\n") + 1);

                email.erase(0, email.find_first_not_of(" \t\r\n"));
                email.erase(email.find_last_not_of(" \t\r\n") + 1);

                if (Search(id))
                {
                    cout << "Duplicate ID " << id << ", skipping." << el;
                    continue;
                }

                p.setID(id);
                p.setName(name);
                p.setPhone(phone);
                p.setEmail(email);
                insertPerson(p);
                loadedCount++;
                cout << "Loaded: " << id << " - " << name << el;
            }
            catch (...)
            {
                cout << "Invalid data in line: " << line << el;
                continue;
            }
        }

        cout << "Successfully loaded " << loadedCount << " contacts." << el;
        file.close();
    }
};

int main() {

    AVL book;
    int choice;

    while (true) {
        cout << "\n====== Address Book Menu ======\n";
        cout << "1. Add New Contact(s)\n";
        cout << "2. Delete Contact by ID\n";
        cout << "3. Search Contact by ID\n";
        cout << "4. List All Contacts (In-order)\n";
        cout << "5. Display Tree\n";
        cout << "6. Exit\n";
        cout << "7. Load Contacts from File\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1)
        {
            int count;
            cout << "How many contacts do you want to add? ";

            if (!(cin >> count) || count < 0)
            {
                cout << "Invalid number of contacts.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            for (int i = 0; i < count; ++i)
            {
                person p;
                int id;
                string name, phone, email;
                cout << "Enter ID: ";

                if (!(cin >> id))
                {
                    cout << "Invalid ID.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    --i;
                    continue;
                }

                if (book.Search(id))
                {
                    cout << "Error: Contact with ID " << id << " already exists." << el;
                    --i;
                    continue;
                }

                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Phone: ";
                getline(cin, phone);
                cout << "Enter Email: ";
                getline(cin, email);

                p.setID(id);
                p.setName(name);
                p.setPhone(phone);
                p.setEmail(email);
                book.insertPerson(p);
            }
        }

        else if (choice == 2)
        {
            int id;
            cout << "Enter ID to delete: ";
            if (!(cin >> id))
            {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            book.deleteContact(id);
        }

        else if (choice == 3)
        {
            int id;
            cout << "Enter ID to search: ";
            if (!(cin >> id))
            {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (book.Search(id))
            {
                cout << "Contact with ID " << id << " exists in the book.\n";
            }

            else
            {
                cout << "No contact found with ID " << id << ".\n";
            }
        }

        else if (choice == 4)
        {
            book.listAll();
        }

        else if (choice == 5)
        {
            cout << "Current AVL Tree: " << el;
            book.printTree();
            cout << el;
        }

        else if (choice == 6)
        {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }

        else if (choice == 7)
        {
            string filename;
            cout << "Enter filename as file.txt: ";
            cin >> filename;
            book.loadFromFile(filename);
        }

        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
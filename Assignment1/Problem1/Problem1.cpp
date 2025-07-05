/*
==========================================
                     Test Cases for Iftar Manager
==========================================

# 1. Valid Guests:
Omar 01011223344 10/5/2025
Ahmed 01122334455 5/6/2025
Hana 01555667788 12/7/2025
Kareem 01056781234 8/8/2025
Laila 01234567890 15/9/2025
Fatima 0112233445 22/6/2025
Hanan 0112233445 22/6/2025
Sara 0155566778 8/12/2025
Basmala 01048985766 08/12/2025

# 2. Guests with Past Dates (Should be rejected when added):
Tariq 01199988877 10/3/2024
Mona 01022233344 1/1/2023

# 3. Updating Invitations:
    # - Updating to a valid future date
    UPDATE Omar 15/5/2025
    UPDATE Ahmed 10/6/2025

    # - Trying to update with the same date (Should print "Guest already invited")
    UPDATE Laila 15/9/2025

    # - Trying to update to a past date (Should be rejected)
    UPDATE Kareem 1/1/2024

    # - Updating a non-existing guest (Should print "Guest not found")
    UPDATE Farah 20/7/2025

# 4. Sending Reminders:
REMINDER 2/6/2025
REMINDER 22/5/2025
REMINDER 08/12/2025  // Date format with leading zeros
REMINDER 5/8/2025    // No guests should be found
REMINDER 5/8/2005    // An old date should not send reminders

# 5. Removing Guests:
REMOVE Hana  // Should successfully remove Hana
REMOVE Tariq  // Should print "Guest not found" since Tariq had an invalid date

# 6. Sorting the Guest List:
SORT  // Should arrange guests by Iftar date correctly.

# 7. Displaying Guests:
DISPLAY  // Should print all guests in order.

*/


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;

// Class representing a guest and their invitation details.
class Guest
{
private:
    string name, contact, iftar_date;

public:
    Guest();
    Guest(const string& guest_name, const string& guest_contact, const string& guest_iftar_date);
    string get_name();
    string get_contact();
    string get_iftar_date();
    void display_guest();
    void update_invitation(string new_date);
};


Guest::Guest()
{
    name = "";
    contact = "";
    iftar_date = "";
}

Guest::Guest(const string& guest_name, const string& guest_contact, const string& guest_iftar_date)
{
    this->name = guest_name;
    this->contact = guest_contact;
    this->iftar_date = guest_iftar_date;
}

string Guest::get_name()
{
    return name;
}

string Guest::get_contact()
{
    return contact;
}

string Guest::get_iftar_date()
{
    return iftar_date;
}

// Display guest information in a readable format
void Guest::display_guest()
{
    cout << "Guest: " << name << ", "
        << "Contact: " << contact << ", "
        << "Iftar Date: " << iftar_date << endl;
}

// Get current date to validate new invitation date.
void Guest::update_invitation(string new_date)
{
    auto now = chrono::system_clock::now(); // Get current date and time
    time_t time_now = chrono::system_clock::to_time_t(now); // Convert to time_t -> is the number of seconds since 1900
    tm today; // tm struct to store the current date and time
    localtime_s(&today, &time_now); // Convert time_t to a readable date and time

    // Extract day, month, and year from the input string
    int day1, month1, year1;
    char slash;
    istringstream date_stream1(iftar_date);
    date_stream1 >> day1 >> slash >> month1 >> slash >> year1;

    int day2, month2, year2;
    istringstream date_stream2(new_date);
    date_stream2 >> day2 >> slash >> month2 >> slash >> year2;

    //Check if the new date is in the future before updating the invitation
    if (year2 < today.tm_year + 1900 ||
        (year2 == today.tm_year + 1900 && month2 < today.tm_mon + 1) ||
        (year2 == today.tm_year + 1900 && month2 == today.tm_mon + 1 && day2 < today.tm_mday))
    {
        cout << "Warninig: We can't update this invitation.\n";
        return;
    }

    // Check if the new date is the same as the current date
    if (day1 == day2 && month1 == month2 && year1 == year2)
    {
        cout << "Guest already invited on this date.\n";
    }

    // Update the invitation date
    else
    {
        iftar_date = new_date;
        cout << "Updating invitation for " << name << "...\n";
    }
}

// Class managing Iftar invitations
class IftarManager
{
private:
    Guest* guest_list;  // Dynamic array to store guests.
    int guest_count;  // Number of guests currently stored.
    int guest_capacity;  // Capacity of the guest list array.
    void resize();  // Resize the guest list array.
    void to_lower(string& str); // Convert string to lowercase

public:
    IftarManager();
    void add_guest(Guest guest);
    void remove_guest(const string& guest_name);
    void display_all_guests();
    void update_guest_invitation(const string& guest_name, const string& new_date);
    void send_remainder(const string& guest_date);
    void sort_guest_list();
    ~IftarManager();
};

// Double the array size when capacity is reached
void IftarManager::resize()
{
    guest_capacity *= 2;
    Guest* newList = new Guest[guest_capacity]();

    //copy elements from old array to new array
    for (int i = 0; i < guest_count; i++)
    {
        newList[i] = guest_list[i];
    }

    delete[] guest_list;
    guest_list = newList;
}

void IftarManager::to_lower(string& str)
{
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A'); // Convert uppercase to lowercase
        }
    }
}

IftarManager::IftarManager() : guest_count(0), guest_capacity(10)
{
    guest_list = new Guest[guest_capacity]();
}

// Ensure the iftar date is in the future before adding the guest
void IftarManager::add_guest(Guest guest)
{
    auto now = chrono::system_clock::now(); // Get current date and time
    time_t time_now = chrono::system_clock::to_time_t(now); // Convert to time_t -> is the number of seconds since 1900
    tm today; // tm struct to store the current date and time
    localtime_s(&today, &time_now); // Convert time_t to a readable date and time

    // Extract day, month, and year from the input string
    int day, month, year;
    char slash;
    istringstream date_stream(guest.get_iftar_date());
    date_stream >> day >> slash >> month >> slash >> year;

    //Check if the new date is in the future before updating the invitation
    if (year < today.tm_year + 1900 ||
        (year == today.tm_year + 1900 && month < today.tm_mon + 1) ||
        (year == today.tm_year + 1900 && month == today.tm_mon + 1 && day < today.tm_mday))
    {
        cout << "Warninig: We can't update this invitation.\n";
        return;
    }

    // Resize the array if it's full
    if (guest_count == guest_capacity)
    {
        resize();
    }
    guest_list[guest_count++] = guest;
}

// Find the guest and remove them from the list
void IftarManager::remove_guest(const string& guest_name)
{
    // Convert guest name to lowercase for case-insensitive comparison
    string lower_guest_name = guest_name;
    to_lower(lower_guest_name);

    for (int i = 0; i < guest_count; i++)
    {
        // Convert current guest name to lowercase for case-insensitive comparison
        string lower_current_name = guest_list[i].get_name();
        to_lower(lower_current_name);

        // Ensure the new date is in the future before updating the invitation
        if (lower_current_name == lower_guest_name)
        {
            for (int j = i; j < guest_count - 1; j++)
            {
                guest_list[j] = guest_list[j + 1];
            }

            guest_count--;
            cout << "Guest removed.\n";
            return;
        }
    }
    cout << "Guest not found.\n";
}

// Display all guests in the list
void IftarManager::display_all_guests()
{
    if (guest_count == 0) // Print message if no guests are found
    {
        cout << "No guests to display.\n";
        return;
    }

    else // Print all guests
    {
        for (int i = 0; i < guest_count; i++)
        {
            guest_list[i].display_guest();
        }
    }
}

// Search for a guest and update their iftar date
void IftarManager::update_guest_invitation(const string& guest_name, const string& new_date)
{
    // Convert guest name to lowercase for case-insensitive comparison
    string lower_guest_name = guest_name;
    to_lower(lower_guest_name);

    for (int i = 0; i < guest_count; i++)
    {
        // Convert current guest name to lowercase for case-insensitive comparison
        string lower_current_name = guest_list[i].get_name();
        to_lower(lower_current_name);

        // Ensure the new date is in the future before updating the invitation
        if (lower_current_name == lower_guest_name)
        {
            guest_list[i].update_invitation(new_date);
            return;
        }
    }
    cout << "Guest not found.\n";
}

// Send reminders to guests with matching iftar dates
void IftarManager::send_remainder(const string& guest_date)
{
    bool isfound = false;
    for (int i = 0; i < guest_count; i++)
    {
        if (guest_list[i].get_iftar_date() == guest_date)
        {
            cout << "Reminder sent to " << guest_list[i].get_name() << ": Your Iftar invitation is on " << guest_date << "!\n";
            isfound = true;
        }
    }

    if (!isfound)
    {
        cout << "No guests found for the given date.\n";
    }
}

// Sort guests by iftar date using insertion sort
void IftarManager::sort_guest_list()
{
    for (int i = 1; i < guest_count; i++)
    {
        Guest key = guest_list[i];
        int j = i - 1;

        string date1 = guest_list[j].get_iftar_date();
        string date2 = key.get_iftar_date();

        // Convert iftar dates to streames for comparison
        int day1, month1, year1;
        char slash; // For neglect "/"
        istringstream date_stream1(date1);
        date_stream1 >> day1 >> slash >> month1 >> slash >> year1;

        int day2, month2, year2;
        istringstream date_stream2(date2);
        date_stream2 >> day2 >> slash >> month2 >> slash >> year2;

        // Compare dates
        while (j >= 0 && (year1 > year2 || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2)))
        {
            guest_list[j + 1] = guest_list[j];
            j--;

            if (j >= 0)
            {
                // Update date1 with the next guest's iftar date
                date1 = guest_list[j].get_iftar_date();
                istringstream date_stream1(date1);
                date_stream1 >> day1 >> slash >> month1 >> slash >> year1;
            }
        }

        guest_list[j + 1] = key;
    }
    cout << "Guest list sorted by Iftar date.\n";
}

// Free allocated memory when manager is destroyed
IftarManager::~IftarManager()
{
    delete[] guest_list;
}

// Handle invalid input
int handling_exception(int choice)
{
    while (true)
    {
        try
        {
            cout << "Enter your choice: ";
            cin >> choice;
            if (cin.fail())
            {
                throw runtime_error("Invalid input. Please enter a number.");
            }
            return choice;
        }

        catch (const runtime_error& e)
        {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main()
{
    IftarManager manager;

    string fileName;
    cout << "Enter the File name with its extension.\n";
    cin >> fileName;

    // Read from file
    ifstream input_file(fileName);
    if (!input_file) {
        cerr << "Error: Unable to open file.\n";
        return 1;
    }

    while (true)
    {
        cout << "\n                             Welcome to Fatima's Iftar Manager\n";
        cout << "                           =====================================\n";
        cout << "1. Add Guest\n"
            << "2. Delete Guest\n"
            << "3. Display All Guests\n"
            << "4. Update Guest Invitation\n"
            << "5. Send Remainder\n"
            << "6. Sort Guest List\n"
            << "7. Exit\n";
        int choice = 0;
        choice = handling_exception(choice);

        switch (choice)
        {
        case 1: // Add guest
        {
            string name, contact, iftar_date;
            if (!(input_file >> name >> contact >> iftar_date)) {
                cout << "This is the end of the file....\n";
                break;
            }
            Guest guest(name, contact, iftar_date);
            manager.add_guest(guest);
        }
        break;

        case 2: // Remove guest
        {
            string name;
            cout << "Enter guest name: ";
            cin >> name;
            manager.remove_guest(name);
        }
        break;

        case 3: // Display all guests
            manager.display_all_guests();
            break;

        case 4: // Update guest invitation
        {
            string name, new_date;
            cout << "Enter guest name: ";
            cin >> name;
            cout << "Enter new Iftar date: ";
            cin >> new_date;
            manager.update_guest_invitation(name, new_date);
        }
        break;

        case 5: // Send remainder
        {
            string date;
            cout << "Enter Iftar date: ";
            cin >> date;
            manager.send_remainder(date);
        }
        break;

        case 6: // Sort guest list
            manager.sort_guest_list();
            break;

        case 7: // Exit
        {
            cout << "Exiting program...\n";
            input_file.close();
            return 0;
        }
        break;

        default: // Invalid choice
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    }
}

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include "ValidationLib.h"
#include "UtilityLib.h"

using namespace std;

enum enSearchBy { enSearchByName = 1, enSearchByPhone = 2 };
enum enMainMenuChoice
{
    enListContacts = 1,
    enAddContact = 2,
    enDeleteContact = 3,
    enUpdateContact = 4,
    enFindContact = 5,
    enExit = 6
};

struct stContact
{
    string FirstName = "";
    string LastName = "";
    string Phone = "";
    string Email = "";
    string Address = "";
};
string FullName(stContact Contact)
{
    return Contact.FirstName + " " + Contact.LastName;
}

void PrintContactCard(stContact &Contact)
{
    cout << "\n";
    cout << string(40, '-') << "\n";
    cout << left << setw(12) << "Name"
        << ": " << FullName(Contact) << "\n";
    cout << left << setw(12) << "Phone"
        << ": " << Contact.Phone << "\n";
    cout << left << setw(12) << "Email"
        << ": " << Contact.Email << "\n";
    cout << left << setw(12) << "Address"
        << ": " << Contact.Address << "\n";
    cout << string(40, '-') << "\n";
}

void PrintContactList(vector<stContact>& vContacts)
{
    if (vContacts.empty())
    {
        cout << "\nNo Contacts Found!\n";
        return;
    }

    cout << "\n";
    cout << left
        << setw(5) << "No."
        << setw(20) << "Name"
        << setw(15) << "Phone"
        << setw(25) << "Email" << "\n";
    cout << string(65, '-') << "\n";

    for (int i = 0; i < vContacts.size(); i++)
    {
        cout << left
            << setw(5) << i + 1
            << setw(20) << FullName(vContacts[i])
            << setw(15) << vContacts[i].Phone
            << setw(25) << vContacts[i].Email << "\n";
    }
    cout << string(65, '-') << "\n";
    cout << "Total Contacts: " << vContacts.size() << "\n";
}

int main()
{
    return 0;
}
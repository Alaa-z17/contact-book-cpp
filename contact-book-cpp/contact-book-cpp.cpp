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
void SaveContactsToFile(vector<stContact>& vContacts)
{
    ofstream MyFile("Contacts.txt");
    for (stContact& Contact : vContacts)
    {
        MyFile << Contact.FirstName << "#";
        MyFile << Contact.LastName << "#";
        MyFile << Contact.Phone << "#";
        MyFile << Contact.Email << "#";
        MyFile << Contact.Address << "\n";
    }
    MyFile.close();
}

stContact LoadContactFromLine(string Line)
{
    stContact Contact;
    string Value = "";
    short FieldNumber = 0;

    for (char& C : Line)
    {
        if (C == '#')
        {
            switch (FieldNumber)
            {
            case 0: Contact.FirstName = Value; break;
            case 1: Contact.LastName = Value; break;
            case 2: Contact.Phone = Value; break;
            case 3: Contact.Email = Value; break;
            }
            Value = "";
            FieldNumber++;
        }
        else
        {
            Value += C;
        }
    }
    Contact.Address = Value;
    return Contact;
}

void LoadContactsFromFile(vector<stContact>& vContacts)
{
    ifstream MyFile("Contacts.txt");
    if (!MyFile.is_open())
        return;

    vContacts.clear();
    string Line = "";
    while (getline(MyFile, Line))
    {
        if (Line.empty()) continue;
        vContacts.push_back(LoadContactFromLine(Line));
    }
    MyFile.close();
}
int main()
{
    return 0;
}
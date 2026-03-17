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
string GetFullName(stContact Contact)
{
    return Contact.FirstName + " " + Contact.LastName;
}

void PrintContactCard(stContact &Contact)
{
    cout << "\n";
    cout << string(40, '-') << "\n";
    cout << left << setw(12) << "Name"
        << ": " << GetFullName(Contact) << "\n";
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
            << setw(20) << GetFullName(vContacts[i])
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
stContact* FindContactByName(string FullName,
    vector<stContact>& vContacts)
{
    string LowerName = UtilityLib::ConvertToLower(FullName);
    for (stContact& Contact : vContacts)
    {
        if (UtilityLib::ConvertToLower(GetFullName(Contact)) == LowerName)
            return &Contact;
    }
    return nullptr;
}

stContact* FindContactByPhone(string Phone,
    vector<stContact>& vContacts)
{
    for (stContact& Contact : vContacts)
    {
        if (Contact.Phone == Phone)
            return &Contact;
    }
    return nullptr;
}

stContact* FindContact(vector<stContact>& vContacts)
{
    short Choice = 0;
    do
    {
        cout << "Search By [1] Name, [2] Phone? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 2);

    cin.ignore();
    string SearchTerm = "";

    if (Choice == enSearchBy::enSearchByName)
    {
        cout << "Enter Name: ";
        getline(cin, SearchTerm);
        return FindContactByName(
            UtilityLib::TrimString(SearchTerm), vContacts);
    }
    else
    {
        cout << "Enter Phone: ";
        getline(cin, SearchTerm);
        return FindContactByPhone(
            UtilityLib::TrimString(SearchTerm), vContacts);
    }
}

void ShowFindContact(vector<stContact>& vContacts)
{
    if (vContacts.empty())
    {
        cout << "\nNo Contacts Found!\n";
        return;
    }

    stContact* pContact = FindContact(vContacts);
    if (pContact == nullptr)
        cout << "\nContact Not Found!\n";
    else
        PrintContactCard(*pContact);
}
string ReadFirstName()
{
    string FirstName = "";
    do
    {
        cout << "Enter First Name: ";
        cin.ignore();
        getline(cin, FirstName);
        FirstName = UtilityLib::TrimString(FirstName);
    } while (FirstName.empty());
    return FirstName;
}

string ReadLastName()
{
    string LastName = "";
    do
    {
        cout << "Enter Last Name: ";
        getline(cin, LastName);
        LastName = UtilityLib::TrimString(LastName);
    } while (LastName.empty());
    return LastName;
}

string ReadPhone()
{
    string Phone = "";
    do
    {
        cout << "Enter Phone: ";
        getline(cin, Phone);
        Phone = UtilityLib::TrimString(Phone);
        if (!ValidationLib::IsValidPhone(Phone))
            cout << "Invalid Phone! Try again.\n";
    } while (!ValidationLib::IsValidPhone(Phone));
    return Phone;
}

string ReadEmail()
{
    string Email = "";
    do
    {
        cout << "Enter Email: ";
        getline(cin, Email);
        Email = UtilityLib::TrimString(Email);
        if (!ValidationLib::IsValidEmail(Email))
            cout << "Invalid Email! Try again.\n";
    } while (!ValidationLib::IsValidEmail(Email));
    return Email;
}

string ReadAddress()
{
    string Address = "";
    cout << "Enter Address: ";
    getline(cin, Address);
    return UtilityLib::TrimString(Address);
}

stContact ReadNewContact()
{
    stContact Contact;
    Contact.FirstName = ReadFirstName();
    Contact.LastName = ReadLastName();
    Contact.Phone = ReadPhone();
    Contact.Email = ReadEmail();
    Contact.Address = ReadAddress();
    return Contact;
}

void AddContact(vector<stContact>& vContacts)
{
    vContacts.push_back(ReadNewContact());
    SaveContactsToFile(vContacts);
    cout << "\nContact Added Successfully!\n";
}
int main()
{
    return 0;
}
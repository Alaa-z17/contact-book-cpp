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
    enSortContacts = 6,
    enExit = 7
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
/**
 * @brief Merges two sorted halves of a contacts vector.
 *
 * @param vContacts The full contacts vector.
 * @param Left      Start index of the left half.
 * @param Mid       End index of the left half.
 * @param Right     End index of the right half.
 *
 * @details
 * Takes two already-sorted halves and merges them into
 * one sorted sequence. Compares contacts by full name
 * alphabetically using ConvertToLower for case-insensitive sort.
 *
 * @example
 * Before: [John, Alice, Mark, Bob]
 *          Left half   Right half
 *          [John,Alice] [Mark,Bob]  ← already sorted individually
 * After:  [Alice, Bob, John, Mark]  ← merged and sorted
 */
void MergeContacts(vector<stContact>& vContacts,
    int Left, int Mid, int Right)
{
    int LeftSize = Mid - Left + 1;
    int RightSize = Right - Mid;

    vector<stContact> vLeft(LeftSize);
    vector<stContact> vRight(RightSize);

    for (int i = 0; i < LeftSize; i++)
        vLeft[i] = vContacts[Left + i];
    for (int i = 0; i < RightSize; i++)
        vRight[i] = vContacts[Mid + 1 + i];

    int i = 0, j = 0, k = Left;
    while (i < LeftSize && j < RightSize)
    {
        if (UtilityLib::ConvertToLower(GetFullName(vLeft[i])) <=
            UtilityLib::ConvertToLower(GetFullName(vRight[j])))
        {
            vContacts[k] = vLeft[i];
            i++;
        }
        else
        {
            vContacts[k] = vRight[j];
            j++;
        }
        k++;
    }
    while (i < LeftSize)
    {
        vContacts[k] = vLeft[i];
        i++;
        k++;
    }
    while (j < RightSize)
    {
        vContacts[k] = vRight[j];
        j++;
        k++;
    }
}

/**
 * @brief Sorts contacts alphabetically using Merge Sort algorithm.
 *
 * @param vContacts The contacts vector to sort.
 * @param Left      Start index of the current segment.
 * @param Right     End index of the current segment.
 *
 * @details
 * This is a RECURSIVE function — it calls itself twice
 * on smaller segments until it reaches the base case.
 *
 * Why is it called Recursion?
 * Because SortContacts calls SortContacts itself:
 *
 *   SortContacts(vContacts, 0, 3)        ← original call
 *    ├── SortContacts(vContacts, 0, 1)   ← calls itself (left half)
 *    │    ├── SortContacts(vContacts, 0, 0) ← base case, stops
 *    │    └── SortContacts(vContacts, 1, 1) ← base case, stops
 *    └── SortContacts(vContacts, 2, 3)   ← calls itself (right half)
 *         ├── SortContacts(vContacts, 2, 2) ← base case, stops
 *         └── SortContacts(vContacts, 3, 3) ← base case, stops
 *
 * Base case (Left >= Right):
 * A segment of 1 element is already sorted — no need to go further.
 * Without a base case, the function would call itself forever.
 *
 * @example
 * Input:  [John, Alice, Mark, Bob]
 * Output: [Alice, Bob, John, Mark]
 */
void SortContacts(vector<stContact>& vContacts,
    int Left, int Right)
{
    // Base case - recursion stops here
    if (Left >= Right)
        return;

    int Mid = Left + (Right - Left) / 2;

    // Recursive calls
    SortContacts(vContacts, Left, Mid);
    SortContacts(vContacts, Mid + 1, Right);

    // Merge the sorted halves
    MergeContacts(vContacts, Left, Mid, Right);
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
        cout << "Enter Full Name: ";
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
void DeleteContact(vector<stContact>& vContacts)
{
    if (vContacts.empty())
    {
        cout << "\nNo Contacts Found!\n";
        return;
    }

    PrintContactList(vContacts);

    stContact* pContact = FindContact(vContacts);
    if (pContact == nullptr)
    {
        cout << "\nContact Not Found!\n";
        return;
    }

    PrintContactCard(*pContact);

    char Confirm = 'N';
    cout << "\nAre you sure you want to delete? Y/N? ";
    cin >> Confirm;

    if (Confirm == 'Y' || Confirm == 'y')
    {
        for (int i = 0; i < vContacts.size(); i++)
        {
            if (vContacts[i].Phone == pContact->Phone)
            {
                vContacts.erase(vContacts.begin() + i);
                break;
            }
        }
        SaveContactsToFile(vContacts);
        cout << "\nContact Deleted Successfully!\n";
    }
}

void UpdateContact(vector<stContact>& vContacts)
{
    if (vContacts.empty())
    {
        cout << "\nNo Contacts Found!\n";
        return;
    }

    PrintContactList(vContacts);

    stContact* pContact = FindContact(vContacts);
    if (pContact == nullptr)
    {
        cout << "\nContact Not Found!\n";
        return;
    }

    PrintContactCard(*pContact);

    cout << "\nEnter New Details:\n";
    cin.ignore();
    pContact->FirstName = ReadFirstName();
    pContact->LastName = ReadLastName();
    pContact->Phone = ReadPhone();
    pContact->Email = ReadEmail();
    pContact->Address = ReadAddress();

    SaveContactsToFile(vContacts);
    cout << "\nContact Updated Successfully!\n";
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void PrintMainMenu()
{
    cout << "\n";
    cout << string(40, '=') << "\n";
    cout << "        CONTACT BOOK SYSTEM\n";
    cout << string(40, '=') << "\n";
    cout << "[1] List All Contacts\n";
    cout << "[2] Add New Contact\n";
    cout << "[3] Delete Contact\n";
    cout << "[4] Update Contact\n";
    cout << "[5] Find Contact\n";
    cout << "[6] Sort Contacts A-Z\n";
    cout << "[7] Exit\n";
    cout << string(40, '=') << "\n";
    cout << "Enter your choice: ";
}

enMainMenuChoice ReadMainMenuChoice()
{
    short Choice = 0;
    do
    {
        PrintMainMenu();
        cin >> Choice;
    } while (Choice < 1 || Choice > 7);
    return (enMainMenuChoice)Choice;
}

void RunContactBook()
{
    vector<stContact> vContacts;
    LoadContactsFromFile(vContacts);

    enMainMenuChoice Choice;
    do
    {
        ResetScreen();
        Choice = ReadMainMenuChoice();
        switch (Choice)
        {
        case enMainMenuChoice::enListContacts:
            PrintContactList(vContacts);
            break;
        case enMainMenuChoice::enAddContact:
            AddContact(vContacts);
            break;
        case enMainMenuChoice::enDeleteContact:
            DeleteContact(vContacts);
            break;
        case enMainMenuChoice::enUpdateContact:
            UpdateContact(vContacts);
            break;
        case enMainMenuChoice::enFindContact:
            ShowFindContact(vContacts);
            break;
        case enMainMenuChoice::enSortContacts:
            if (vContacts.empty())
            {
                cout << "\nNo Contacts Found!\n";
            }
            else
            {
                SortContacts(vContacts, 0, static_cast<int>(vContacts.size()) - 1);
                SaveContactsToFile(vContacts);
                cout << "\nContacts Sorted A-Z Successfully!\n";
            }
            break;
        case enMainMenuChoice::enExit:
            cout << "\nGoodbye!\n";
            break;
        }
        if (Choice != enMainMenuChoice::enExit)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (Choice != enMainMenuChoice::enExit);
}
int main()
{
    RunContactBook();
    return 0;
}
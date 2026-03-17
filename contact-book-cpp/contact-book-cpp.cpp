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

int main()
{
    return 0;
}
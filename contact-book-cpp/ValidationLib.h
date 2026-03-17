#pragma once
#include<string>
#include<cctype>
using namespace std;
namespace ValidationLib
{
    bool IsValidPhone(string Phone)
    {
        if (Phone.length() < 7 || Phone.length() > 15)
            return false;
        for (char& C : Phone)
        {
            if (!isdigit(C) && C != '+' && C != '-')
                return false;
        }
        return true;
    }

    bool IsValidEmail(string Email)
    {
        int AtPos = Email.find('@');
        if (AtPos == string::npos)
            return false;
        int DotPos = Email.find('.', AtPos);
        if (DotPos == string::npos)
            return false;
        return true;
    }
}

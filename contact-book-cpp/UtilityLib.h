#pragma once
#include<string>
#include<cctype>
using namespace std;

namespace UtilityLib
{
    string ConvertToLower(string Text)
    {
        string LowerText = "";
        for (char& C : Text)
        {
            LowerText += tolower(C);
        }
        return LowerText;
    }

    string ConvertToUpper(string Text)
    {
        string UpperText = "";
        for (char& C : Text)
        {
            UpperText += toupper(C);
        }
        return UpperText;
    }

    string TrimString(string Text)
    {
        int Start = Text.find_first_not_of(" ");
        int End = Text.find_last_not_of(" ");
        if (Start == string::npos)
            return "";
        return Text.substr(Start, End - Start + 1);
    }
}


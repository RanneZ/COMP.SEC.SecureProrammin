#include "utility.h"
#include <iostream>

using namespace std;

string VERSION = "v.0.0.2.alpha";

void utility::cursor()
{
    cout << "\\> ";
}

void utility::separet()
{
    cout << "============================================================" << endl;
}

void utility::marginal()
{
    cout << "     ";
}

void utility::versio()
{
    cout << "                                               " << VERSION << endl;
}

void utility::date()
{
    cout << "                                                  00.00.0000" << endl;
}

void utility::space()
{

}

void utility::textField(std::string text)
{

}

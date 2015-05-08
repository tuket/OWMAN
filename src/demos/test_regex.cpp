/*
* It seems the gcc has not fully implemented
* regex. So I won't be using it in my application.
*/

#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{

    regex r
    (
        "(cell_)((([1-9])([0-9])*)|0)(_)(([1-9][0-9]*)|0)(.xml)",
        regex_constants::basic
    );

    if( regex_match("cell_0_0.xml", r) )
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }

}

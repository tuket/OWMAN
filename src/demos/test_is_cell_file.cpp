#include <iostream>
#include <string>
#include <cassert>
#include "../math/vec2i.hpp"

using namespace std;

bool isCellFile(string fileName)
{

    string minSample = "cell_0_0.xml";
    if( fileName.size() < minSample.size() ) return false;

    int slash = 0;
    for(int i = fileName.size(); i>=0; i--)
    if( fileName[i] == '/' )
    {
        slash = i;
        slash++;
        break;
    }
    int i = slash;

    string s1 = "cell_";

    for(int j=0; j<s1.size(); j++, i++)
    {
        if( s1[j] != fileName[i] ) return false;
    }

    if( fileName[i] == '0' )
    {

        if( fileName[i+1] != '_' ) return false;
        i += 2;

    }
    else
    {

        if( !('1' <= fileName[i] && fileName[i] <= '9') ) return false;
        i++;

        while( '0' <= fileName[i] && fileName[i] <= '9' )
        {
            i++;
        }

        if( fileName[i] != '_' ) return false;

        i++;

    }

    if( fileName[i] == '0' )
    {

        if( fileName[i+1] != '.' ) return false;
        i += 2;

    }
    else
    {

        if( !('1' <= fileName[i] && fileName[i] <= '9') ) return false;
        i++;

        while( '0' <= fileName[i] && fileName[i] <= '9' )
        {
            i++;
        }

        if( fileName[i] != '.' ) return false;

        i++;

    }

    string s2 = "xml";

    for(int j=0; j<s2.size(); j++, i++)
    {
        if( fileName[i] != s2[j] ) return false;
    }

    return true;

}

Vec2i getCell(string fileName)
{

    int slash = 0;
    for(int i = fileName.size(); i>=0; i--)
    if( fileName[i] == '/' )
    {
        slash = i;
        slash++;
        break;
    }
    int i = slash;

    while( !('0' <= fileName[i] && fileName[i] <= '9')  )
    {
        i++;
    }

    int x = 0;
    while( '0' <= fileName[i] && fileName[i] <= '9' )
    {
        x *= 10;
        x += (int)(fileName[i] - '0');

        i++;
    }

    while( !('0' <= fileName[i] && fileName[i] <= '9')  )
    {
        i++;
    }

    int y = 0;
    while( '0' <= fileName[i] && fileName[i] <= '9' )
    {
        y *= 10;
        y += (int)(fileName[i] - '0');

        i++;
    }

    return Vec2i(x, y);

}

int main()
{

    string t1 = "hole/cell_0_0.xml";
    string t2 = "hole/cell_0_01.xml";
    string t3 = "cell_0_01.xml";
    string t4 = "cell_0_0.xml";
    string t5 = "cell_10_10.xml";

    assert( isCellFile(t1) );
    assert( !isCellFile(t2) );
    assert( !isCellFile(t3) );
    assert( isCellFile(t4) );
    assert( isCellFile(t5) );

    string s1 = "hole/cell_400435_0.xml";
    Vec2i cell = getCell( s1 );
    assert( cell.x == 400435 && cell.y == 0 );


}

#ifndef FUNCTIONS
#define FUNCTIONS

/**
* \brief compute a % b for floats
*/
float fmod(float a, float b)
{
    while(a>b) a -= b;
    return a;
}

#endif // FUNCTIONS

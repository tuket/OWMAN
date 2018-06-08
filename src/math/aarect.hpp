#ifndef AARECT_HPP_INCLUDED
#define AARECT_HPP_INCLUDED

/* Axially aligned rectangle */
class AARect{

public:

    float x, y;
    float w, h;

    AARect(){}
    AARect(float x, float y, float w, float h);
    AARect(const AARect& rect);

    AARect operator=(const AARect& rect);

};

#endif // AARECT_HPP_INCLUDED

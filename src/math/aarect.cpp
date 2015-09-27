#include "aarect.hpp"

AARect::AARect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

AARect::AARect(const AARect& rect)
{
    x = rect.x;
    y = rect.y;
    w = rect.w;
    h = rect.h;
}

AARect AARect::operator=(const AARect& rect)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    return *this;
}

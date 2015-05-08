#include "vec2i.hpp"

Vec2i::Vec2i(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vec2i Vec2i::operator=(const Vec2i& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return *this;
}

Vec2i Vec2i::operator+(const Vec2i& vec)const
{
	Vec2i res(x, y);
	res.x += vec.x;
	res.y += vec.y;
	return res;
}

Vec2i Vec2i::operator-(const Vec2i& vec)const
{
	Vec2i res(x, y);
	res.x -= vec.x;
	res.y -= vec.y;
	return res;
}

Vec2i Vec2i::operator-()const
{
	Vec2i res(-x, -y);
	return res;
}

bool Vec2i::operator<(const Vec2i& v)const
{

    if( x == v.x ) return y < v.y;

    return x < v.x;

}

bool Vec2i::operator==(const Vec2i& v)const
{

    return x == v.x && y == v.y;

}

bool Vec2i::operator!=(const Vec2i& v)const
{

    return x != v.x || y != v.y;

}

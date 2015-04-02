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
}

Vec2i Vec2i::operator+(const Vec2i& vec)
{
	Vec2i res(x, y);
	res.x += vec.x;
	res.y += vec.y;
	return res;
}

Vec2i Vec2i::operator-(const Vec2i& vec)
{
	Vec2i res(x, y);
	res.x -= vec.x;
	res.y -= vec.y;
	return res;
}

Vec2i Vec2i::operator-()
{
	Vec2i res(-x, -y);
	return res;
}

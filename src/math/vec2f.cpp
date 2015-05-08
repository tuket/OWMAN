#include "vec2f.hpp"

Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2f Vec2f::operator=(const Vec2f& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

Vec2f Vec2f::operator+(const Vec2f& vec)const
{
	float x = this->x + vec.x;
	float y = this->y + vec.y;
	Vec2f res(x, y);
	return res;
}

Vec2f Vec2f::operator-(const Vec2f& vec)const
{
	float x = this->x - vec.x;
	float y = this->y - vec.y;
	Vec2f res(x, y);
	return res;
}

Vec2f Vec2f::operator-()const
{
	float x = -(this->x);
	float y = -(this->y);
	Vec2f res(x, y);
	return res;
}

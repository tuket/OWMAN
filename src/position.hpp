#include "math/vec2f.hpp"
#include "math/vec2i.hpp"

#ifndef POSITION
#define POSITION

class Position
{
	
	Vec2i cell;
	Vec2f offset;
	
public:

	Position(){}
	Position(const Vec2i& cell, const Vec2f& offset);
	Position(const Position& pos);
	
	const Vec2i& getCell()const;
	const Vec2f& getOffset()const;
	
	Vec2i& getCell();
	Vec2f& getOffset();
	
	void setCell(const Vec2i& cell);
	void setOffset(const Vec2f& offset);
	
	Position operator=(const Position& pos);
	
	Position operator+(const Position& pos)const;
	Position operator-(const Position& pos)const;
	
	Position operator-()const;
	
};

#endif

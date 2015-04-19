#include "cell_size.hpp"
#include "position.hpp"

Position::Position(const Vec2i& cell, const Vec2f& offset)
{
	this->cell = cell;
	this->offset = offset;
}

Position::Position(const Position& pos)
{
	cell = pos.cell;
	offset = pos.offset;
}

const Vec2i& Position::getCell()const
{
	return cell;
}

const Vec2f& Position::getOffset()const
{
	return offset;
}

Vec2i& Position::getCell()
{
	return cell;
}

Vec2f& Position::getOffset()
{
	return offset;
}

void Position::setCell(const Vec2i& cell)
{
	this->cell = cell;
}

void Position::setOffset(const Vec2f& offset)
{
	this->offset = offset;
}

Position Position::operator=(const Position& pos)
{
	
	cell = pos.cell;
	offset = pos.offset;
	return *this;
	
}

Position Position::operator+(const Position& pos)const
{
	
	Position res(*this);
	res.cell += pos.cell;
	res.offset += pos.offset;
	return res;
	
}

Position Position::operator-(const Position& pos)const
{
	
	Position res(*this);
	res.cell -= pos.cell;
	res.offset -= pos.offset;
	return res;
	
}

Position Position::operator-()const
{
	
	Position res(*this);
	res.cell = -res.cell;
	res.offset = -res.offset;
	return res;
	
}

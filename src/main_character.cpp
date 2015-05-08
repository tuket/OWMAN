#include "main_character.hpp"

MainCharacter::MainCharacter()
{
	id = 0;		// 0 is invalid
	typeId = "";
	graphicsComponent = 0;
}

const Vec2i& MainCharacter::getCell()const
{

    return cell;

}

Vec2i& MainCharacter::getCell()
{

    return cell;

}

void MainCharacter::setCell( const Vec2i& cell )
{

    this->cell = cell;

}

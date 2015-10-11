#include "sprite_status.hpp"

SpriteStatus::SpriteStatus(Sprite* sprite)
{
    mySprite = sprite;
    currentFrame = 0;
    elapsedTime = 0.0f;
}

int SpriteStatus::getCurrentFrame()const
{
    return currentFrame;
}

float SpriteStatus::getElapsedTime()const
{
    return elapsedTime;
}

void SpriteStatus::setCurrentFrame(int frame)
{
    currentFrame = frame;
}

void SpriteStatus::setElapsedTime(float time)
{
    elapsedTime = time;
}

Sprite* SpriteStatus::getSprite()
{
    return sprite;
}

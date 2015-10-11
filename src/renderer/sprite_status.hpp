#ifndef SPRITE_STATUS_HPP_INCLUDED
#define SPRITE_STATUS_HPP_INCLUDED

#ifndef SPRITE_HPP
class Sprite;
#endif

class SpriteStatus
{
    int currentAnimation;
    int currentFrame;
    float elapsedTime;  //< elapsed time in the current frame
    Sprite* mySprite;

public:

    SpriteStatus(Sprite* sprite);

    int getCurrentFrame()const;
    float getElapsedTime()const;

    void setCurrentFrame(int frame);
    void setElapsedTime(float time);

    Sprite* getSprite();

};

#endif // SPRITE_STATUS_HPP_INCLUDED

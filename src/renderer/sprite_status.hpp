#ifndef SPRITE_STATUS
#define SPRITE_STATUS

#ifndef SPRITE
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

#endif // SPRITE_STATUS

#ifndef SPRITE_STATUS
#define SPRITE_STATUS

#include "graphics_component.hpp"

class Sprite;
class SpriteManager;

class SpriteStatus : public GraphicsComponent
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
    SpriteManager* getSpriteManager();

    bool isReady()const;
    void update(float delta);
    void draw()const;

    rapidxml::xml_node<>* createXmlNode(rapidxml::xml_document<>* doc);

    void destroyDispatcher();

};

#endif // SPRITE_STATUS

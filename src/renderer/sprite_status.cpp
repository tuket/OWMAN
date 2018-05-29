#include "sprite_status.hpp"
#include "sprite.hpp"
#include "animation.hpp"
#include "animation_frame.hpp"
#include "../math/functions.hpp"
#include "sprite_manager.hpp"
#include "graphics_system.hpp"
#include "texture.hpp"
#include "../util/xmlstr.hpp"
#include <iostream>

using namespace std;
using namespace rapidxml;

SpriteStatus::SpriteStatus(Sprite* sprite)
:
    GraphicsComponent(sprite->getSpriteManager()->getGraphicsSystem())
{
    mySprite = sprite;
    currentAnimation = 0;
    currentFrame = 0;
    elapsedTime = 0.0f;
    //cout << "-" << endl;
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
    return mySprite;
}

SpriteManager* SpriteStatus::getSpriteManager()
{
    return getSprite()->getSpriteManager();
}

bool SpriteStatus::isReady()const
{
    return mySprite->isReady();
}

void SpriteStatus::update(float delta)
{
    if(isReady())
    {
        elapsedTime += delta;
        const Animation& anim = mySprite->animations[currentAnimation];
        const AnimationFrame& frame = anim.frames[currentFrame];
        float frameDuration = frame.frameDuration;
        if(elapsedTime >= frameDuration)
        {
            unsigned incf = (unsigned)(elapsedTime/frameDuration);
            elapsedTime = fmod(elapsedTime, frameDuration);
            currentFrame += incf;
            currentFrame %= anim.frames.size();
        }
    }
}

void SpriteStatus::draw()const
{
    if(isReady())
    {
        const Animation& anim = mySprite->animations[currentAnimation];
        const AnimationFrame& frame = anim.frames[currentFrame];
        const Texture* texture = mySprite->textures[frame.textureIndex];

        const Vec2f& pos = position;
        const Vec2f& scale = this->scale;
        const LowLevelRenderer2D::SpriteVbo& vbo = frame.vbo;

        texture->draw(pos, scale, vbo);

        /// //////////////
        if(mySprite->name == "castle")
        {
            cout << "currentFame: " << currentFrame << endl;
            cout << "tex: " << frame.textureIndex << endl;
        }
    }
}

unsigned SpriteStatus::getAnimationIndex()const
{
    return currentAnimation;
}

void SpriteStatus::setAnimation(const string& animName)
{
    unsigned index = mySprite->getAnimIndex(animName);
    if(index != currentAnimation)
    {
        currentAnimation = index;
        currentFrame = 0;
    }
}

void SpriteStatus::setAnimation(unsigned animIndex)
{
    if(animIndex != currentAnimation)
    {
        currentAnimation = animIndex;
        currentFrame = 0;
    }
}

rapidxml::xml_node<>* SpriteStatus::createXmlNode(rapidxml::xml_document<>* doc)
{
    const string& spriteName = mySprite->getName();

    xml_node<>* root = GraphicsComponent::createXmlNode(doc);
    const char* str_spriteName = doc->allocate_string(spriteName.c_str());
    xml_node<>* node_sprite = doc->allocate_node(node_element, xmlstr::sprite, str_spriteName);
    root->prepend_node(node_sprite);

    return root;
}

void SpriteStatus::destroyDispatcher()
{
    getSpriteManager()->releaseSpriteInstance(this);
}

#include "sprite_manager.hpp"
#include "../resource_manager/resource_manager.hpp"
#include <cassert>

using namespace std;

// constants
const std::string spritesPath = "sprites";

// private
SpritesSet::iterator getSpriteByName(const std::string& name)
{
    Sprite spr(0, name);    //< temporal sprite
    SpriteRefCountEntry entry;  //< temporal entry
    entr.sprite = &spr;
    SpriteSet::iterator it;
    it = sprites.find(entry);
    return it;
}

//public
SpriteManager::SpriteManager(GraphicsSystem* graphicsSystem)
{
    this->graphicsSystem = graphicsSystem;
    sprites = set<SpriteRefCountEntry, decltype(compareSpriteByName)>(compareSpriteByName);
}

GraphicsSystem* SpriteManager::getGraphicsSystem()
{
    return graphicsSystem;
}

SpriteStatus* SpriteManager::instanceSprite(const std::string name)
{
    auto it = sprites.find(name);
    Sprite* sprite;

    // if is already instanced
    if(it != sprites.end())
    {
        sprite = it->second.sprite;
        // increment reference count to the sprite
        it->second.count++;
    }

    // sprite not instanced, need to create
    else{
        sprite = new Sprite(this);
        SpriteRefCountEntry entry;
        entry.sprite = sprite;
        entry.count = 1;
        sprites[name] = entry;
    }

    SpriteStatus* spriteStatus = new SpriteStatus(sprite);
    return spriteStatus;

}

void SpriteManager::releaseSpriteInstance(SpriteStatus* spriteStatus)
{
    auto it = sprites.find(spriteStatus->sprite->getName());

    assert
    (
        it != sprites.end() &&
        "Attempt to release a SpriteStatus whose sprite is not in the table"
    );

    SpriteRefCountEntry& entry = it->second;
    if(entry.count == 1)
    {
        // TODO
        entry.count = 0;
        entry.sprite->//kill
        sprites.erase(it);
    }
    else
    {
        entry.count--;
    }

}

void SpriteManager::update(float delta)
{
    // 1: check if resoruces have been laoded

    // 2: handle animations

}

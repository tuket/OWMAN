#include "sprite_manager.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "sprite.hpp"
#include "sprite_status.hpp"
#include <cassert>

using namespace std;

// constants
const std::string SpriteManager::spritesPath = "sprites";

// private
SpritesSet::iterator SpriteManager::getSpriteByName(const std::string& name)
{
    /* TODO: This is the fast way of implementing \
    * but it is inefficient since we have to create \
    * a temporal sprite to search. We could improve this \
    * by implementing a custom RB tree
    */
    Sprite spr(0, name);    //< temporal sprite
    SpriteRefCountEntry entry;  //< temporal entry
    entry.sprite = &spr;
    SpritesSet::iterator it;
    it = sprites.find(entry);
    return it;
}

void SpriteManager::releaseSprite(Sprite* sprite)
{
    sprite->release();
    delete sprite;
}

//public
SpriteManager::SpriteManager(GraphicsSystem* graphicsSystem)
{
    this->graphicsSystem = graphicsSystem;
    sprites = set<SpriteRefCountEntry, CompareSpriteByName>(CompareSpriteByName());
}

GraphicsSystem* SpriteManager::getGraphicsSystem()
{
    return graphicsSystem;
}

SpriteStatus* SpriteManager::instanceSprite(const std::string name)
{
    SpritesSet::iterator it = getSpriteByName(name);
    Sprite* sprite;

    // if is already instanced
    if(it != sprites.end())
    {
        sprite = it->sprite;
        // increment reference count to the sprite
        (it->count)++;
    }

    // sprite not instanced, need to create
    else{
        sprite = new Sprite(this, name);
        SpriteRefCountEntry entry;
        entry.sprite = sprite;
        entry.count = 1;
        sprites.insert(entry);
    }

    SpriteStatus* spriteStatus = new SpriteStatus(sprite);
    return spriteStatus;

}

void SpriteManager::releaseSpriteInstance(SpriteStatus* spriteStatus)
{
    SpritesSet::iterator it;
    it = getSpriteByName(spriteStatus->getSprite()->getName());

    assert
    (
        it != sprites.end() &&
        "Attempt to release a SpriteStatus whose sprite is not in the table"
    );

    if(it->count == 1)
    {
        // TODO
        it->count = 0;
        releaseSprite(it->sprite);
        sprites.erase(it);
    }
    else
    {
        it->count--;
    }

    delete spriteStatus;

}

void SpriteManager::update(float delta)
{
    SpritesSet::iterator it;
    for(it = sprites.begin(); it != sprites.end(); ++it)
    {
        it->sprite->update();
    }

    // the sprite statuses are not updated here but in GraphicsSystem
}


// CompareSpriteByName functor

bool CompareSpriteByName::operator()
(
    const SpriteRefCountEntry& entry1,
    const SpriteRefCountEntry& entry2
)
{
    return entry1.sprite->getName() < entry2.sprite->getName();
}

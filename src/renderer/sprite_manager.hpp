#ifndef SPRITE_MANAGER
#define SPRITE_MANAGER

#include <vector>
#include <string>
#include <map>
#include <set>

class GraphicsSystem;
class SpriteStatus;
class Sprite;

// We use this struct to keep track of how many
// sprite statuses use each sprite
struct SpriteRefCountEntry
{
    SpriteRefCountEntry()
    :count(0), sprite(0)
    {}

    mutable int count;  //< this variable is not involved in the comp function
    Sprite* sprite;

};

struct CompareSpriteByName
{
    bool operator()(const SpriteRefCountEntry& entry1, const SpriteRefCountEntry& entry2) const;
};

typedef
std::set<SpriteRefCountEntry, CompareSpriteByName>
SpritesSet;

class SpriteManager
{

public:
    // constants
    static const std::string spritesPath;

private:
    // friendship
    friend class GraphicsSystem;

    // members
    GraphicsSystem* graphicsSystem;

    SpritesSet sprites;
    //std::vector<SpriteStatus*> spriteStatuses;

    // functions
    SpriteManager(){}

    SpritesSet::iterator getSpriteByName(const std::string& name);

    /**
    * \brief release a sprite and all its resources
    * This should called only by SpriteManager when releaseSpriteInstance
    * reaches 0
    */
    void releaseSprite(Sprite* sprite);

public:

    SpriteManager(GraphicsSystem* graphicsSystem);

    GraphicsSystem* getGraphicsSystem();

    SpriteStatus* instanceSprite(const std::string name);
    void releaseSpriteInstance(SpriteStatus* spriteStatus);

    void update(float delta);

};

#endif // SPRITE_MANAGER

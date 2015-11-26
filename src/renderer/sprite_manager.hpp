#ifndef SPRITE_MANAGER
#define SPRITE_MANAGER

#include <vector>
#include <string>
#include <map>
#include <set>

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem;
#endif

#ifndef SPRITE_STATUS
class SpriteStatus;
#endif

#ifndef SPRITE
class Sprite;
#endif

// We use this struct to keep track of how many
// sprite statuses use each sprite
struct SpriteRefCountEntry
{
    SpriteRefCountEntry()
    :count(0), sprite(0)
    {}

    int count;
    Sprite* sprite;

};

struct CompareSpriteByName
(
    bool operator()(const SpriteRefCountEntry& entry1, const SpriteRefCountEntry& entry2)
    {

    }
);

typedef
std::set<SpriteRefCountEntry, decltype(SpriteRefCountEntry::compareSpriteByName)>
SpritesSet;

class SpriteManager
{

    // constants
    static const std::string spritesPath;

    // friendship
    friend class GraphicsSystem;

    // members
    GraphicsSystem* graphicsSystem;

    SpritesSet sprites;
    std::vector<SpriteStatus*> spriteStatuses;

    // functiones
    SpriteManager(){}

    SpritesSet::iterator getSpriteByName(const std::string& name);

public:

    SpriteManager(GraphicsSystem* graphicsSystem);

    GraphicsSystem* getGraphicsSystem();

    SpriteStatus* instanceSprite(const std::string name);
    void releaseSpriteInstance(SpriteStatus* spriteStatus);

    void update(float delta);

};

#endif // SPRITE_MANAGER

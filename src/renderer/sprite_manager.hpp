#ifndef SPRITE_MANAGER
#define SPRITE_MANAGER

#include <vector>
#include <string>
#incldue <map>

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem
#endif

#ifndef SPRITE_STATUS
class SpriteStatus;
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

class SpriteManager
{

    static const std::string spritesPath = "sprites";

    friend class GraphicsSystem

    GraphicsSystem* graphicsSystem;

    std::map<std::string, SpriteRefCountEntry> sprites;
    std::vector<SpriteStatus*> spriteStatuses;

    SpriteManager(){}

public:

    GraphicsSystem* getGraphicsSystem();

    SpriteStatus* instanceSprite(const std::string name);
    void releaseSpriteInstance(SpriteStatus* spriteStatus);

    void update(float delta);

};

#endif // SPRITE_MANAGER

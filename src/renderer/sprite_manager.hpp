#ifndef SPRITE_MANAGER
#define SPRITE_MANAGER

#include <vector>
#include <string>
#incldue <map>

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem
#endif

class SpriteManager
{

    friend class GraphicsSystem

    GraphicsSystem* graphicsSystem;
    std::map<std::string, Sprite*> sprites;
    std::vector<SpriteStatus*> spriteStatuses;

    SpriteManager(){}

public:

    SpriteStatus* instanceSprite(const std::string name);
    void releaseSpriteInstance(SpriteStatus* spriteStatus);

    void update(float delta);

};

#endif // SPRITE_MANAGER

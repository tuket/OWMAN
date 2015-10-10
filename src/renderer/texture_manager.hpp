#ifndef TEXTURE_MANAGER_HPP_INCLUDED
#define TEXTURE_MANAGER_HPP_INCLUDED

#include "texture.hpp"
#include <map>
#include <string>
#include <vector>

class GraphicsSystem;

class TextureRefCountEntry
{
    friend class TextureManager;
    Texture* texture;
    unsigned count;
};

class TextureManager
{

    GraphicsSystem* graphicsSystem;
    std::map<std::string, TextureRefCountEntry> textures;

public:

    TextureManager(GraphicsSystem* graphicsSystem);

    Texture* getTexture(const std::string &name);
    void releaseTexture(Texture* texture);

    GraphicsSystem* getGraphicsSystem();

    void update();

};

#endif // TEXTURE_MANAGER_HPP_INCLUDED

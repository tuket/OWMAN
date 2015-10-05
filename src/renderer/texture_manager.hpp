#ifndef TEXTURE_MANAGER_HPP_INCLUDED
#define TEXTURE_MANAGER_HPP_INCLUDED

#include "texture.hpp"
#include <map>
#include <string>
#include <vector>

class TextureRefCountEntry
{
    Texture* texture;
    unsigned count;
};

class TextureManager
{

    std::map<std::string, TextureRefCountEntry> textures;

public:

    Texture* getTexture();
    void releaseTexture(Texture* texture);

};

#endif // TEXTURE_MANAGER_HPP_INCLUDED

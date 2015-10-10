#include "texture_manager.hpp"
#include "texture.hpp"
#include <cassert>

using namespace std;

TextureManager::TextureManager(GraphicsSystem* graphicsSystem)
{
    this->graphicsSystem = graphicsSystem;
}

Texture* TextureManager::getTexture(const std::string &name)
{
    map<string, TextureRefCountEntry>::iterator it;
    it = textures.find(name);
    Texture* tex;
    if(it == textures.end())
    {
        tex = new Texture();
        TextureRefCountEntry entry;
        entry.texture = tex;
        entry.count = 1;
        textures[name] = entry;
    }
    else
    {
        tex = it->second.texture;
        it->second.count++;
    }
    return tex;
}

void TextureManager::releaseTexture(Texture* texture)
{
    const string& name = texture->getName();
    map<string, TextureRefCountEntry>::iterator it;
    it = textures.find(name);
    assert(it != textures.end());
    TextureRefCountEntry& entry = it->second;
    if(entry.count == 1)
    {
        // last reference
        entry.texture->release();
        textures.erase(it);
    }
    else
    {
        entry.count--;
    }
}

GraphicsSystem* TextureManager::getGraphicsSystem()
{
    return graphicsSystem;
}

void TextureManager::update()
{
    map<string, TextureRefCountEntry>::iterator it;
    for(it = textures.begin(); it != textures.end(); ++it)
    {
        TextureRefCountEntry& entry = it->second;
        Texture* texture = entry.texture;

        if(texture->isLoaded())
        {
            // must upload to VRAM
            texture->loadToGPU();
            texture->releaseResource();
        }
        else if(texture->status == Texture::Status::START)
        {
            // must upload to RAM
        }
    }
}

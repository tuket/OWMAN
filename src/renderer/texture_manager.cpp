#include "texture_manager.hpp"
#include "texture.hpp"
#include <cassert>
#include "../resource_manager/resource_texture.hpp"
#include "../resource_manager/resource_manager.hpp"

using namespace std;

const string TextureManager::texturesPath = "img/";

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
        tex = new Texture(this, name);
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
        // what if the texture is not in MM yet?
        // this problem is solved in the release function
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

        if(texture->status == Texture::Status::LOADING)
        {
            if(texture->resourceTexture->getStatus() == Resource::Status::LOADED)
            {
                texture->status = Texture::Status::LOADED;
            }
        }

        if(texture->isLoaded())
        {
            // must upload to VRAM
            texture->loadToGPU();
            texture->releaseResource();
            texture->status = Texture::Status::READY;
        }
        else if(texture->status == Texture::Status::START)
        {
            // must upload to RAM
            ResourceManager* resMan = ResourceManager::getSingleton();
            texture->resourceTexture = resMan->obtain<ResourceTexture>(texture->name);
            texture->status = Texture::Status::LOADING;
        }
    }
}

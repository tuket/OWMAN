#include "texture.hpp"
#include "texture_manager.hpp"

Texture::Texture(TextureManager* textureManager, const std::string& name)
{
    this->textureManager = textureManager;
    this->name = name;
    status = Status::START;
    llTexture = 0;
    resourceTexture = 0;
    filterMode = FilterMode::NEAREST;
}

void Texture::setFilterMode(FilterMode filterMode)
{
    this->filterMode = filterMode;
}

bool Texture::isLoaded()const
{
    return Status::LOADED == status;
}

bool Texture::isReady()const
{
    return Status::READY == status;
}

void Texture::loadResource()
{
    assert(resourceTexture == 0);
    ResourceManager* resMan = ResourceManager::getSingleton();
    resourceTexture = resMan->obtain<ResourceTexture>(texturesPath + "/" + name);
    status = Status::LOADING;
}

void Texture::loadToGPU()
{
    assert(resourceTexture != 0);
    assert(isLoaded && resourceTexture->getStatus() == ResourceTexture::Status::LOADED);

    GraphicsSystem* gs = textureManager->getGraphicsSystem();
    LowLevelRenderer2D* llr = gs->getRenderer();
    llTexture =
    llr->createTexture
    (
        resourceTexture->getTextureData(),
        resourceTexture->getWidth(),
        resourceTexture->getHeight()
    );
    llTexture->setFilterMode(filterMode);
}

void Texture::releaseResource()
{
    ResourceManager* resMan = ResourceManager::getSingleton();
    resMan->release(resourceTexture);
}

void Texture::release()
{
    if( isReady() )
    {
        // the texture is un VRAM
        GraphicsSystem* gs = textureManager->getGraphicsSystem();
        LowLevelRenderer2D* llr = gs->getRenderer();
        llr->destroyTexture(llTexture);
    }
    else
    {
        // Even if the resource is still loading the ResourceManager will
        // take care of this
        releaseResource();
    }
}

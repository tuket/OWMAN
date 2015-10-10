#include "texture.hpp"
#include "texture_manager.hpp"

Texture::Texture(TextureManager* textureManager, const std::string& name)
{
    this->textureManager = textureManager;
    this->name = name;
    status = Status::START;
    llTexture = 0;
    resourceTexture = 0;
    filterMode = FilterMode::NOT_SET;
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
    // TODO
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
    resourceTexture->free();
}

void Texture::release()
{
    // TODO
}

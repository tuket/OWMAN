#ifndef TEXTURE
#define TEXTURE

#include "low_level_renderer_2d.hpp"
#include "../math/aarect.hpp"

class TextureManager;
class ResourceTexture;

class Texture
{
    friend class TextureManager;

public:

    const static std::string texturesPath;

    typedef LowLevelRenderer2D::Texture::FilterMode FilterMode;

    enum class Status
    {
        START,
        LOADING,
        LOADED,
        READY,
    };

    Texture(){}

    Texture(TextureManager* TextureManager, const std::string& name);

    /**
    * \brief get the name of the texture file
    */
    const std::string& getName()const;

    /**
    * \brief set the filter mode
    */
    void setFilterMode(FilterMode filterMode);

    /**
    * \brief is loaded in main memory
    */
    bool isLoaded()const;

    /**
    * \brief is laoded in graphics card
    */
    bool isReady()const;

    /**
    * \brief load this texture to RAM
    * The brings the texture resource from disk to MM.\
    * You will know that the secondary thread of the resource manager
    * has finished loading this resource when isLoaded() returns true.
    */
    void loadResource();

    /**
    * \brief load this texture to the GPU
    * The texture data will remain in MM unless you
    * release it with releaseResource()
    */
    void loadToGPU();

    /**
    * \brief release the data in MM
    * You should call this function after using loadToGPU().
    */
    void releaseResource();

    /**
    * \brief release from GPU
    * Call this *only* after loadToGPU
    */
    void release();

    /**
    * \brief draw a texture in the screen
    */
    void draw
    (
        const Vec2f& pos,
        const Vec2f& scale,
        const LowLevelRenderer2D::SpriteVbo& sVbo
    )const;

    /**
    * \brief draw a texture in the screen
    */
    void draw
    (
        const Vec2f& pos,
        const LowLevelRenderer2D::SpriteVbo& sVbo
    )const;

private:

    TextureManager* textureManager;

    std::string name;
    Status status;
    FilterMode filterMode;

    LowLevelRenderer2D::Texture llTexture;
    ResourceTexture* resourceTexture;

};

#endif // TEXTURE

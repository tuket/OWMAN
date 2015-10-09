#ifndef TEXTURE
#define TEXTURE

#include "low_level_renderer_2d.hpp"
#include "../math/aarect.hpp"

class GraphicsSystem;
class ResourceTexture;

class Texture
{
    LowLevelRenderer2D::Texture llTexture;
    ResourceTexture* resourceTexture;

public:

    enum class FilterMode
    {
        LINEAR,
        NEAREST
    };

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

};

#endif // TEXTURE

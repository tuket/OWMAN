#ifndef ANIMATION_FRAME
#define ANIMATION_FRAME

#include "../math/aarect.hpp"
#include "low_level_renderer_2d.hpp"

class AnimationFrame
{

public:

    unsigned textureIndex;
    LowLevelRenderer2D::SpriteVbo vbo;
    float frameDuration;

};

#endif // ANIMATION_FRAME

#ifndef ANIMATION_FRAME
#define ANIMATION_FRAME

#include "../math/aarect.hpp"

class AnimationFrame
{

    friend class Animation;

    unsigned textureIndex;
    AARect rect;
    float frameDuration;

};

#endif // ANIMATION_FRAME

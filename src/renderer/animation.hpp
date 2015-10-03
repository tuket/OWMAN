#ifndef ANIMATION
#define ANIMATION

#include <string>
#include <vector>
#include "animation_frame.hpp"

class Animation
{

    friend class Sprite;

    std::string name;
    std::vector<AnimationFrame> frames;

};

#endif // ANIMATION

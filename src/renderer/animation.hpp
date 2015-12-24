#ifndef ANIMATION
#define ANIMATION

#include <string>
#include <vector>
#include "animation_frame.hpp"

class Animation
{

public:

    std::string name;
    std::vector<AnimationFrame> frames;

};

#endif // ANIMATION

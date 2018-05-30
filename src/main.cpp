#include "engine.hpp"

int main()
{

    Engine engine("init_file.xml", "world_folder");

    engine.init();

    engine.mainLoop();

    return 0;
}

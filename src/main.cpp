#include "engine.hpp"

int main(int argc, char* argv[])
{

    Engine engine("init_file.xml", "world_folder");

    engine.init();

    engine.mainLoop();

    return 0;
}

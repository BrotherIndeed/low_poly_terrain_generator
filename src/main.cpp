
#include "engine.cpp"
int main()
{    

    Engine terrain_generator;

    terrain_generator.init();
    terrain_generator.run();
    terrain_generator.terminate();
    
    return 0;
}
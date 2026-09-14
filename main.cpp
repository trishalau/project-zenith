#include "splashkit.h"
#include "game_engine.h"

/**
 * @brief The main execution entry point.
 * 
 * Instantiates the Game Engine object and starts the main game loop.
 */
int main() 
{
    game_engine project_zenith_engine;
    project_zenith_engine.play();
    
    return 0;
}
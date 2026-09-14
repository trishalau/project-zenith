#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "player_state.h"
#include "world_state.h"
#include "day_scenario.h"
#include "game_mode.h"
#include "rival.h" 
#include <vector>

using std::vector;
using std::string;

/**
 * @class game_engine
 * @brief The brain of the program. It connects all major components together.
 */
class game_engine 
{
    private:
        /**
         * @brief The current state of the user (Loyalty/Trust/Tags Gained).
         * Passed by reference to each day scenario.
         */
        player_state player;

        /**
         * @brief The current state of the world (Public Awareness).
         */
        world_state world;

        /**
         * @brief The selected difficulty level (Easy/Normal/Hard).
         */
        game_mode selected_mode;
        
        /**
         * @brief The rival AI agent.
         * Active only during Hard mode to sabotage the player.
         */
        rival generated_rival; 

        /**
         * @brief To store the game chapters.
         */
        vector<day_scenario*> days;     // Pointers to different day_scenario derived classes

        /**
         * @brief Subroutine function to print text with a delay.
         * @param text The text to print.
         * @param ms The delay in milliseconds after printing.
         */
        void print_slow(string text, int ms = 500);

    public:

        /**
         * @brief Constructor to sets up the game environment, asks player for game mode and
         * populates the 'days' vector with new day_scenario objects.
         */
        game_engine(); 

        /**
         * @brief Destructor for memory cleanup.
         * 
         * It deletes all dynamically allocated day_scenario objects in the vector to prevent memory leaks.
         */
        ~game_engine();

        /**
         * @brief The Main Game loop.
         * 
         * Iterates through the 'days' vector and runs each scenario, then 
         * triggers the Ending sequence based on accumulated final stats.
         */
        void play();
};

#endif
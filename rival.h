#ifndef RIVAL_H
#define RIVAL_H

#include "player_state.h" 
#include "world_state.h"  
#include "splashkit.h"    

using std::string;

/**
 * @class rival
 * @brief Represents the rival AI agent active in Hard Mode.
 *
 * The rival (Executive X) exists to increase difficulty by actively 
 * working against the player at every turn. 
 * The rival appears during Sabotage Events to lower player stats for both loyalty and trust.
 */

class rival 
{
    private:
        string name;

    /**
     *
     * @brief Constructor to create the rival agent.
     * @param name The name to display in dialogue logs.
     */
    public:
        rival(string name);
        string get_name();

    /**
     * @brief Triggers a random negative event against the player.
     * 
     * This function generates a random value to decrease
     * either the player's loyalty or trust stats.
     * @param p Reference to the player_state to modify stats.
     * @param w Reference to the world_state to modify public awareness.
     */
        void sabotage(player_state &p, world_state &w);
};

#endif
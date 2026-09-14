#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "splashkit.h"
#include "game_tags.h" 
#include <vector>

using std::vector;

/**
 * @class player_state
 * @brief Manages the player's personal progress, in-game stats, and story decisions.
 *
 * This class acts as the memory of the player. It tracks:
 * 1. Player Stats (Loyalty to NeoCorp and Trust with the Rebels).
 * 2. Narrative Game Tags that remember past choices (e.g., if you saved a character).
 * 
 * It is the primary data source used by the Game Engine to determine which
 * ending the player receives.
 */
class player_state 
{
    private:
    
        int corporate_loyalty;             // Score representing loyalty to NeoCorp
        int rebel_trust;                   // Score representing trust with the Rebels
        vector<game_tags> memory_tags;     // Tags to remember key story choices

    public:
        /**
         * @brief Constructor to initializes the player with starting value of 0 Loyalty and 0 Trust.
         */
        player_state();
        
        /**
         * @brief Remembers a specific story event by adding a tag to the player's memory.
         * @param tag The specific game_tag enum to store.
         */
        void add_tag(game_tags tag);      

        /**
         * @brief Checks if the player has performed a specific action in the past.
         * @param tag The tag to search for.
         * @return true if the tag exists in memory, false otherwise.
         */
        bool has_tag(game_tags tag);      

        /**
         * @brief Modifies the player's Corporate Loyalty score.
         * @param amount The value to add or subtract.
         */
        void adjust_loyalty(int amount);

        /**
         * @brief Modifies the player's Rebel Trust score.
         * @param amount The value to add or subtract.
         */
        void adjust_trust(int amount);

        /**
         * @brief Gets the current Corporate Loyalty score.
         * @return The loyalty score.
         */
        int get_loyalty() const;

        /**
         * @brief Gets the current Rebel Trust score.
         * @return The trust score.
         */
        int get_trust() const;
};

#endif
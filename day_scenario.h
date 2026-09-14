#ifndef DAY_SCENARIO_H
#define DAY_SCENARIO_H

#include "splashkit.h"
#include "player_state.h"
#include "world_state.h"
#include "game_tags.h"
#include "game_mode.h" 
#include "rival.h"   

using std::string;

/**
 * @class day_scenario
 * @brief The blueprint for a generic "Day" in the game.
 * Each specific day will inherit from this class and implement its own story and event logic.
 */
class day_scenario 
{
    public:
        /**
         * @brief Virtual Destructor.
         * Ensures proper cleanup of derived classes.
         */
        virtual ~day_scenario() {}

        /**
         * @brief Gets the title of the specific day.
         * @return The string title.
         */
        virtual string get_title() = 0;

        /**
         * @brief Displays the narrative text for this day.
         * Must be implemented by the child class.
         * 
         * @param p Player state (for checking past choices/tags).
         * @param w World state (for reacting to public awareness levels).
         * @param mode Current difficulty mode.
         * @param r The rival agent.
         */
        virtual void print_story(player_state &p, world_state &w, game_mode mode, rival &r) = 0;

        /**
         * @brief Runs the interactive logic (Choices/Input) for this day.
         * Must be implemented by the child class.
         * 
         * @param p Player state (to update stats).
         * @param w World state (to update public awareness).
         * @param mode Current difficulty mode.
         * @param r The rival agent.
         */
        virtual void run_event(player_state &p, world_state &w, game_mode mode, rival &r) = 0;

    protected: 

        /**
         * @brief Displays a strategic hint if the player is in EASY mode.
         * @param mode Checks if it is EASY mode.
         * @param message The hint text to display.
         */
        void print_hint(game_mode mode, string message);
        
        /**
         * @brief Checks difficulty mode and triggers the Rival's sabotage logic.
         * Only runs in HARD mode.
         */
        void trigger_rival(game_mode mode, rival &r, player_state &p, world_state &w);
        
        /**
         * @brief Reads user input with a time limit.
         * In hard mode, the player has a time limit to make a decision.
         * Otherwise, returns "TIMEOUT" and decision is forced.
         * 
         * @param mode Current difficulty mode.
         * @param limit_ms Time limit in milliseconds.
         * @return The string entered by the user.
         */
        string get_timed_input(game_mode mode, unsigned long limit_ms);
};

#endif
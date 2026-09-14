#ifndef WORLD_STATE_H
#define WORLD_STATE_H

/**
 * @class This class observes the collective consequences of player actions.
 * @brief It shows the current state of the in-game world. 
 * 
 * Specifically, how much of Project Zenith has been revealed to the public.
 */
class world_state 
{
    private:
    /**
     * @brief Tracks the percentage of public awareness about Project Zenith.
     * Range: 0 (Total Control) to 100 (Maximum Chaos)
     */
        int public_awareness;               

    public:
    /**
     * @brief Constructor to initializes the world state with default values.
     * Sets initial public awareness to 0 (hidden).
     */
        world_state();                      

    /**
     * @brief Updates the public awareness score based on player actions.
     * Handles range check (0-100) and prints
     * a formatted status update to the terminal output.
     * @param value The amount to add or subtract .
     */
        void update_awareness(int value);   
       
    /**
     * @brief Gets the current public awareness level.
     * @return The current awareness percentage (0-100).
     */
        int get_awareness() const;         
};

#endif
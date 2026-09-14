#ifndef GAME_MODE_H
#define GAME_MODE_H

/**
 * @enum game_mode
 * @brief Represents the selected game difficulty.
 */
enum class game_mode 
{
    EASY,       // Story focus, mini games skipped, has strategy hints
    NORMAL,     // Balanced experience with mini games and standard difficulty
    HARD        // Increased minigame difficulty, rival agent present, time pressure limit for decisions
};

#endif
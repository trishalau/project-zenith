#ifndef MINIGAMES_H
#define MINIGAMES_H

#include "splashkit.h"
#include "game_mode.h" 
#include <string>

using std::string;
using std::to_string;

// SOMETHING AWESOME FEATURE

/**
 * Runs the minigame needed in Day 1 for Option 2.
 * 
 * Gameplay:
 * The player must type out the following sequence of numbers shown 
 * on the pop up window within the time limit.
 * Time Limit: 6.0s (Normal Mode) or 4.0s (Hard Mode).
 * 3 rounds with the sequence getting longer each round.
 * @param mode The current difficulty (Normal/Hard).
 * @return true if all 3 rounds are completed, false if time runs out.
 */
bool run_minigame_1(game_mode mode);

/**
 * Runs the minigame needed in Day 2 for Option 2.
 * 
 * Gameplay:
 * - A red bar moves back and forth.
 * - The player must press SPACE when the bar is inside the Green Zone.
 * - Requirement: 3 Locks (Normal) and 5 Locks (Hard).
 * @param mode The current difficulty (Normal/Hard).
 * @return true if the signal is locked, false if the player misses.
 */
bool run_minigame_2(game_mode mode);

#endif
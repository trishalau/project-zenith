#ifndef GAME_TAGS_H
#define GAME_TAGS_H

/**
 * @enum game_tags
 * @brief Represents key story events or items the player has acquired.
 * 
 * These tags are stored in the player_state and checked later to unlock 
 * special adaptive dialogue options or endings.
 */
enum class game_tags 
{
    NONE,                       // Default tag for no event
    DECRYPTED_COORDINATES,      // Awarded if player successfully completes the first minigame in Day 1
    ECHO_CAPTURED,              // Awarded if player captures Echo in Day 2
    BACKDOOR_KEY,               // Awarded if player successfully completes the second minigame in Day 2
    SEAL_LEAK,                  // Awarded if player chooses to seal the data leak in Day 3
    HAS_BLUEPRINTS,             // Awarded if player steals the blueprints in Day 3
    MARCUS_ALLY,                // Awarded if player helps Marcus escape in Day 4
    INTEGRITY_RECORD            // Awarded if player refuses to betray Marcus in Day 4
};

/**
 * @brief World State modifiers.
 * Determines how much "Public Awareness" increases or decreases.
 */
const int IMPACT_LOW = 10;      
const int IMPACT_MED = 25;      
const int IMPACT_HIGH = 50;     

/**
 * @brief Player Stat modifiers
 * Determines how many points are added/subtracted from Loyalty or Trust.
 */
const int POINTS_SMALL = 15;    
const int POINTS_MED = 25;    
const int POINTS_HIGH = 40;

/**
 * @brief Narrative thresholds.
 * Determines the public awareness level to trigger specific endings or adaptive dialogue options.
 */
const int THRESHOLD_LOW = 15;  
const int THRESHOLD_MED = 25;  
const int THRESHOLD_HIGH = 40;  
const int THRESHOLD_CRITICAL = 50;  

#endif
#include "day_scenario.h"

// Hint display logic
void day_scenario::print_hint(game_mode mode, string message)
{
    if (mode == game_mode::EASY)
    {
        write_line("");
        write_line("💡 [HINT]: " + message);
    }
}

// Rival trigger logic
void day_scenario::trigger_rival(game_mode mode, rival &r, player_state &p, world_state &w)
{
    if (mode == game_mode::HARD)
    {
        r.sabotage(p, w);
    }
}

// Timed input logic
string day_scenario::get_timed_input(game_mode mode, unsigned long limit_ms)
{
    unsigned long start_time = current_ticks();         // Record start time
    
    string input = read_line();                     
    
    if (mode == game_mode::HARD)                        // Only enforce time limit in HARD mode
    {
        if (current_ticks() - start_time > limit_ms)    // Check if time limit exceeded
        {
            return "TIMEOUT";
        }
    }

    return input;
}
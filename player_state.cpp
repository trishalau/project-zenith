#include "player_state.h"
#include "splashkit.h"

using std::to_string;

// Constructors
player_state::player_state()
{
    corporate_loyalty = 0;
    rebel_trust = 0;
}

void player_state::add_tag(game_tags tag) 
{
    if (tag == game_tags::NONE) return;     // Ignore NONE tags
    
    if (!has_tag(tag))                      // Avoid duplicates  
    {
        memory_tags.push_back(tag);
    }
}

bool player_state::has_tag(game_tags tag) 
{
    for (game_tags t : memory_tags) 
    {
        if (t == tag) return true;          // Check if tag exists
    }
    return false;
}

// Setters 
void player_state::adjust_loyalty(int amount) 
{
    corporate_loyalty += amount;

    delay(1000);
    write_line("");

    if (amount > 0)
    {
        write_line("    🏢 Corporate Loyalty increased by " + to_string(amount));
    }
    else
    {
        write_line("    🏢 Corporate Loyalty decreased by " + to_string(amount * -1));
    }
    
    write_line("    📊 Current Corporate Loyalty: " + to_string(corporate_loyalty));
    write_line(""); 
}

void player_state::adjust_trust(int amount) 
{
    rebel_trust += amount;

    delay(1000);
    write_line(""); 
    if (amount > 0)
    {
        write_line("    ⚔️  Rebel Trust increased by " + to_string(amount));
    }
    else
    {
        write_line("    ⚔️  Rebel Trust decreased by " + to_string(amount * -1));
    }

    write_line("    📊 Current Rebel Trust: " + to_string(rebel_trust));
    write_line(""); 
}

// Getters
int player_state::get_loyalty() const 
{
    return corporate_loyalty;
}

int player_state::get_trust() const 
{
    return rebel_trust;
}


#include "rival.h"
#include "splashkit.h"

using std::to_string;

rival::rival(string name)
{
    this->name = name;
}

string rival::get_name()
{
    return name;
}

void rival::sabotage(player_state &p, world_state &w)
{
    int damage = 10 + rnd(11); 

    write_line("");
    write_line("╔══════════════════════════════════════════════════╗");
    write_line("║           💀 RIVAL AGENT INTERVENTION 💀         ║");
    write_line("╚══════════════════════════════════════════════════╝");
    delay(500);

    write_line(">> WARNING: " + name + " is tracking your movements...");
    delay(1500);

    double chance = rnd();

    // Decrease loyalty value
    if (chance < 0.33)
    {
        write_line(">> SABOTAGE: " + name + " corrupted your corporate file.");
        write_line(">> RESULT: NeoCorp trusts you less.");
        p.adjust_loyalty(-damage); 
    }
    // Decrease trust value
    else if (chance < 0.66)
    {
        write_line(">> SABOTAGE: " + name + " ambushed a rebel supply line.");
        write_line(">> RESULT: The rebels trust you less.");
        p.adjust_trust(-damage); 
    }
    // Increase public awareness
    else
    {
        write_line(">> SABOTAGE: " + name + " leaked sensitive info to the public.");
        write_line(">> RESULT: Public awareness about Project Zenith has increased.");
        w.update_awareness(damage); 
    }

    write_line("");
    delay(1500); 
}
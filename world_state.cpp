#include "world_state.h"
#include "splashkit.h"

using std::string;
using std::to_string;

world_state::world_state() 
{
    public_awareness = 0;     
}

void world_state::update_awareness(int value) 
{
    public_awareness += value;

    // Ensure public awareness stays within 0-100 range
    if (public_awareness < 0) public_awareness = 0;
    if (public_awareness > 100) public_awareness = 100;

    string status_tag = ""; 

    // Assigns a status tag to describe the current awareness level
    if (public_awareness == 0) status_tag = " [TOTAL CONTROL]";
    else if (public_awareness <= 25) status_tag = " [SUSPICION RISING]";
    else if (public_awareness <= 50) status_tag = " [CITIZENS UNREST]";
    else if (public_awareness <= 75) status_tag = " [RIOTS ERUPTING]";
    else status_tag = " [MAXIMUM CHAOS]";

    write_line(""); 
    
    // Formats and prints the update message
    string update_msg = "    🌍 Public Awareness ";

    if (value > 0) update_msg += "increased by " + to_string(value);
    else if (value < 0) update_msg += "decreased by " + to_string(value * -1);
    else update_msg += "did not change.";

    write_line(update_msg);
    write_line("    📡 Current Public Awareness:  " + to_string(public_awareness) + "%" + status_tag);
    write_line(""); 
}

int world_state::get_awareness() const 
{
    return public_awareness;
}
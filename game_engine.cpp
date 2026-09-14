#include "game_engine.h"
#include "all_days.h"
#include "splashkit.h"
#include <vector>

using std::string;
using std::to_string;
using std::vector;

void game_engine::print_slow(string text, int ms)
{
    write_line(text);
    delay(ms);
}

// Constructor
game_engine::game_engine() : player(), world(), generated_rival("Executive X") 
{
    selected_mode = game_mode::NORMAL;  // Default to normal mode

    // Load the chapters of the story
    days.push_back(new day_1());
    days.push_back(new day_2());
    days.push_back(new day_3());
    days.push_back(new day_4());
    days.push_back(new day_5());
    days.push_back(new day_6());
}

// Destructor
game_engine::~game_engine()
{
    for (int i = 0; i < days.size(); i++)
    {
        delete days[i];
    }
}

// Main Game Loop with mode selection
void game_engine::play() 
{
    bool mode_selected = false;

    write_line("========================================");
    write_line("       WELCOME TO PROJECT ZENITH        ");
    write_line("========================================");
    write_line("[1] EASY MODE   (Includes Strategic Hints)");
    write_line("[2] NORMAL MODE (Standard Story Experience)");
    write_line("[3] HARD MODE   (Includes a Rival Agent + Time Pressure)");
    write_line("========================================");

    while (!mode_selected)
    {
        write(">> CHOOSE YOUR DIFFICULTY MODE (1-3): ");
        string input = read_line();

        if (input == "1") 
        {
            selected_mode = game_mode::EASY;
            write_line(">> SYSTEM: EASY MODE SELECTED.");
            mode_selected = true;
        }
        else if (input == "2") 
        {
            selected_mode = game_mode::NORMAL;
            write_line(">> SYSTEM: NORMAL MODE SELECTED.");
            mode_selected = true;
        }
        else if (input == "3") 
        {
            selected_mode = game_mode::HARD;
            write_line(">> SYSTEM: HARD MODE SELECTED.");
            write_line(">> Rival can force your decisions and sabotage you. Be quick!");
            mode_selected = true;
        }
        else 
        {
            write_line(">> ERROR: Invalid Input.");
        }
    }
    
    delay(1000);
    write_line(""); 

    // Narrative Introduction
    print_slow("The year is 2072. The world has grown quiet - not because of peace, but because of control.", 500);
    print_slow("", 500);
    print_slow("Inside the towers of NeoCorp, the Executives are developing Project Zenith.", 500);
    print_slow("They plan to bring Order to the chaotic world.", 500);
    print_slow("", 500);
    print_slow("An underground group known as the Rebels is plotting to expose the truth", 500);
    print_slow("and halt Project Zenith for Freedom.", 500);
    print_slow("", 500);
    print_slow("You are an Insider. You have six days to decide the fate of the world.", 500);
    print_slow("If you discover the truth, what will you do with it?", 500);
    print_slow("", 500);
    print_slow("Will you side with the Executives?", 500);
    print_slow("Or will you fight along the Rebels?", 500);
    print_slow("", 500);
    print_slow("The clock is ticking...", 500);
    print_slow("", 500);

    // Wait for user to start
    bool ready = false;
    while (!ready) 
    {
        write("Start Game? Enter 1 to start: ");
        string input = read_line();
        
        if (input == "1") 
        {
            ready = true;
            write_line("");
            write_line("GAME STARTING...");
            delay(500);
        }
        else 
        {
            write_line("System: Waiting for user input...");
        }
        write_line("");
    }

    // Main Game Loop - iterate through days
    for (int i = 0; i < days.size(); i++) 
    {
        // UI header for each day
        write_line("\n\n\n"); 
        write_line("========================================");
        write_line("DAY [" + to_string(i + 1) + "]: " + days[i]->get_title());        
        write_line("🌍 Public Awareness: " + to_string(world.get_awareness()));
        write_line("🛡️  Corporate Loyalty: " + to_string(player.get_loyalty()));
        write_line("⚔️  Rebel Trust: " + to_string(player.get_trust()));
        write_line("========================================");
        write_line("");

        // Run the day's scenario
        days[i]->print_story(player, world, selected_mode, generated_rival);
        days[i]->run_event(player, world, selected_mode, generated_rival);
        
        // Pause between days
        if (i < days.size() - 1)
        {
            write_line("");
            write_line("[PRESS ENTER TO CONTINUE]");
            read_line();
        }
    }
}
#include "minigames.h"
#include "splashkit.h"
#include "game_mode.h"
#include <vector>

using std::vector;
using std::to_string;

bool run_minigame_1(game_mode mode)
{
    window game_window = open_window("ZENITH V.01 - RUN DECRYPTION", 800, 600);
    
    int total_rounds = 3;   
    int current_round = 1;

    // Time Limit: Hard Mode 5.0s, Normal Mode 7.0s
    double round_time = (mode == game_mode::HARD) ? 5.0 : 7.0;
    
    // Initial sequence length: Hard Mode 5, Normal Mode 4
    int sequence_length = (mode == game_mode::HARD) ? 5 : 4;
    
    // Generate random sequence
    vector<int> sequence_needed;
    for(int i = 0; i < sequence_length; i++) 
    {
        sequence_needed.push_back(rnd(10));     // Numbers 0-9
    }

    int current_index = 0;                         // Tracks which digit the player has to type next
    unsigned long start_time = current_ticks();    // Start time for the round
    
    bool game_running = true;
    bool success = false;

    while (game_running && !window_close_requested(game_window))
    {
        process_events();
        clear_screen(COLOR_BLACK);

        unsigned long now = current_ticks();
        double elapsed = (now - start_time) / 1000.0;
        double remaining = round_time - elapsed;

        // Background UI 
        for(int i = 0; i < 800; i+=40) draw_line(COLOR_DARK_GREEN, i, 0, i, 600);
        fill_rectangle(COLOR_BLACK, 50, 100, 700, 400);
        draw_rectangle(COLOR_BRIGHT_GREEN, 50, 100, 700, 400);

        // Display Info UI
        draw_text("DECRYPTION IN PROGRESS: " + to_string(current_round) + " / " + to_string(total_rounds), COLOR_BRIGHT_GREEN, 300, 140);
        draw_text("TYPE OUT THE FOLLOWING SEQUENCE WITHIN THE TIME LIMIT!", COLOR_WHITE, 220, 180);

        // Display Sequence Boxes UI
        int start_x = 400 - (sequence_length * 30); 
        for(int i = 0; i < sequence_length; i++)
        {
            // Coloring Design Logic: Green = Typed, White = Current, Gray = To be Typed
            color box_color = (i < current_index) ? COLOR_BRIGHT_GREEN : ((i == current_index) ? COLOR_WHITE : COLOR_GRAY);
            color text_color = (i <= current_index) ? COLOR_BLACK : COLOR_DARK_GRAY;

            fill_rectangle(box_color, start_x + (i * 60), 250, 50, 50);
            draw_text(to_string(sequence_needed[i]), text_color, start_x + (i * 60) + 20, 265);
        }

        // Timer Bar UI
        double bar_width = (remaining / round_time) * 600.0;
        if (bar_width < 0) bar_width = 0;
        color bar_color = (remaining < 1.5) ? COLOR_RED : COLOR_BRIGHT_GREEN;
        
        draw_text("TIME REMAINING:", COLOR_WHITE, 100, 400);
        fill_rectangle(bar_color, 100, 420, bar_width, 20);
        draw_rectangle(COLOR_WHITE, 100, 420, 600, 20);

        // Input Handling
        int key_pressed = -1;
        if (key_typed(NUM_0_KEY)) key_pressed = 0;
        if (key_typed(NUM_1_KEY)) key_pressed = 1;
        if (key_typed(NUM_2_KEY)) key_pressed = 2;
        if (key_typed(NUM_3_KEY)) key_pressed = 3;
        if (key_typed(NUM_4_KEY)) key_pressed = 4;
        if (key_typed(NUM_5_KEY)) key_pressed = 5;
        if (key_typed(NUM_6_KEY)) key_pressed = 6;
        if (key_typed(NUM_7_KEY)) key_pressed = 7;
        if (key_typed(NUM_8_KEY)) key_pressed = 8;
        if (key_typed(NUM_9_KEY)) key_pressed = 9;

        if (key_pressed != -1)
        {
            // Correct key logic
            if (key_pressed == sequence_needed[current_index])
            {
                current_index++; 
                // Complete one round logic
                if (current_index >= sequence_length)
                {
                    fill_rectangle(COLOR_WHITE, 50, 100, 700, 400);
                    refresh_screen();
                    delay(200);

                    current_round++;
                    // Check if all rounds completed (GAME SUCCESS)
                    if (current_round > total_rounds)
                    {
                        clear_screen(COLOR_BLACK);
                        draw_text("SYSTEM HACKED SUCCESSFULLY", COLOR_BRIGHT_GREEN, 300, 300);
                        refresh_screen();
                        delay(1500); 
                        success = true;
                        game_running = false; 
                    }
                    // Prepare next round - increase sequence length and reset timer
                    else
                    {
                        sequence_length++;
                        current_index = 0;
                        sequence_needed.clear();
                        for(int i = 0; i < sequence_length; i++) sequence_needed.push_back(rnd(10));
                        start_time = current_ticks();
                    }
                }
            }
            // Incorrect key logic
            else
            {
                fill_rectangle(COLOR_RED, 0, 0, 800, 600);
                refresh_screen();
                delay(100); 
            }
        }

        // Lose condition - Time out
        if (remaining <= 0)
        {
            clear_screen(COLOR_RED);
            draw_text("CONNECTION TIMED OUT - DECRYPTION FAILED", COLOR_BLACK, 280, 300);
            refresh_screen();
            delay(2000); 
            success = false;
            game_running = false; 
        }

        refresh_screen(60);
    }

    close_window(game_window);

    process_events();
    
    return success;
}

bool run_minigame_2(game_mode mode)
{
    window game_window = open_window("DRONE SENSORS - SIGNAL HACKING", 800, 600);
    
    // Number of locks needed: Hard Mode 5, Normal Mode 3
    int locks_needed = (mode == game_mode::HARD) ? 5 : 3; 
    int current_locks = 0;
    
    // Bar Setup 
    double bar_x = 0;
    double bar_y = 300;
    double bar_width = 20;
    double bar_height = 100;

    // Movement Speed Setup: Hard Mode 6.0, Normal Mode 4.0
    double speed = (mode == game_mode::HARD) ? 6.0 : 4.0; 
    bool moving_right = true;

    // Target Zone Setup
    double target_x = 350; 

    // Target Zone Width: Hard Mode 80, Normal Mode 120
    double target_width = (mode == game_mode::HARD) ? 80 : 120; 
    
    bool success = false;
    bool game_running = true;

    while (game_running && !window_close_requested(game_window))
    {
        process_events(); 
        clear_screen(COLOR_BLACK);

        // Background UI
        draw_text("DRONE HACKING IN PROGRESS...", COLOR_GREEN, 300, 50);
        draw_text("PRESS [SPACE] WHEN BAR IS IN GREEN ZONE", COLOR_WHITE, 280, 80);
        draw_text("LOCKS REMAINING: " + to_string(locks_needed - current_locks), COLOR_RED, 300, 500);

        // Draw Moving Bar and Target Zone
        fill_rectangle(COLOR_DARK_GREEN, target_x, bar_y - 10, target_width, bar_height + 20);
        fill_rectangle(COLOR_RED, bar_x, bar_y, bar_width, bar_height);

        // Bar Movement Logic
        if (moving_right) bar_x += speed; else bar_x -= speed;
        if (bar_x > 800 - bar_width) moving_right = false;      // Bounce off edges
        if (bar_x < 0) moving_right = true;

        if (key_typed(SPACE_KEY))
        {
            // Check if the red bar is inside the green target zone
            // Success as long as right side of bar pass target zone's left side and 
            // left side of bar pass target zone's right side
            if (bar_x + bar_width > target_x && bar_x < target_x + target_width)
            {
                current_locks++;
                speed += 2.0;               // Increase speed for added challenge
                target_x = rnd(100, 600);   // Move target zone to new random position
                
                fill_rectangle(COLOR_WHITE, 0, 0, 800, 600);
                refresh_screen();
                delay(50);

                // Check if all locks are achieved (GAME SUCCESS)
                if (current_locks >= locks_needed)
                {
                    clear_screen(COLOR_BLACK);
                    draw_text("SIGNAL LOCKED - CONNECTION SECURE", COLOR_BRIGHT_GREEN, 280, 300);
                    refresh_screen();
                    delay(1500); 

                    success = true;
                    game_running = false; 
                }
            }
            // Missed the target zone (GAME FAIL)
            else
            {
                fill_rectangle(COLOR_RED, 0, 0, 800, 600); 
                draw_text("SIGNAL LOST!", COLOR_WHITE, 350, 300);
                refresh_screen();
                delay(1000); 

                success = false;
                game_running = false; 
            }
        }
        refresh_screen(60); 
    }

    close_window(game_window);

    process_events();
    
    return success;
}
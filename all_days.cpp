#include "all_days.h" 
#include "player_state.h"
#include "world_state.h"
#include "game_tags.h"
#include "minigames.h" 
#include "splashkit.h"

using std::string;
using std::to_string;

// Day 1
string day_1::get_title() 
{
    return "THE CORRUPTED ARCHIVE";
}

void day_1::print_story(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    write_line("While performing a routine check of an abandoned terminal,");
    write_line("you discover an encrypted file named ZenithV.01.");
}

void day_1::run_event(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    // Provides Hint for EASY mode
    print_hint(mode, "Option [2] gives you 'Decrypted Coordinates'. This is useful later.");

    write_line("");
    write_line("--- ACTION EVENT ---");
    write_line("[1] Submit to Security Chief for Disposal (Order)");
    write_line("[2] Hide the File and Secretly Decrypt It (Freedom)");
    write_line("");
    
    // Hard mode time warning
    if (mode == game_mode::HARD) 
    {
        write_line("⚠️ URGENT: EXECUTIVE X IS WATCHING. DECIDE IN 10 SECONDS.");
        write_line("");
    }

    bool valid = false;
    while (!valid)
    {
        write("Select your option: ");
        string input = get_timed_input(mode, 10000);    // 10 second limit

        if (input == "TIMEOUT")
        {
            write_line("");
            write_line(">> ⏳ TOO SLOW! Security noticed your hesitation.");
            write_line(">> " + r.get_name() + " forced the outcome.");
            write_line(">> FORCED OUTCOME: OPTION [1] (Submitted to Security)");
            input = "1"; 
        }

        if (input == "1") 
        {
            write_line("");
            write_line("🔵 The Security Chief notices your loyalty to NeoCorp.");
            p.adjust_loyalty(POINTS_SMALL);
            w.update_awareness(-IMPACT_LOW); 
            valid = true;
        } 

        else if (input == "2") 
        {
            bool success = true; 

            if (mode != game_mode::EASY)
            {
                write_line(">> LAUNCHING DECRYPTION PROTOCOL...");
                delay(1000);
                success = run_minigame_1(mode);          // Launch minigame for decryption
            }

            if (success)
            {
                write_line("");
                write_line("🔵 SUCCESS: You decrypted the coordinates for Project Zenith.");
                p.adjust_trust(POINTS_SMALL);
                w.update_awareness(IMPACT_LOW);
                p.add_tag(game_tags::DECRYPTED_COORDINATES); 
            }
            else
            {
                write_line("");
                write_line(">> FAILURE: The file encryption was too strong.");
                write_line(">> You gained nothing but suspicion.");
                w.update_awareness(IMPACT_LOW); 
            }
            valid = true;
        }
        else
        {
            write_line("Invalid input. Please enter 1 or 2.");
        }
    }

    trigger_rival(mode, r, p, w);   // Rival action at end of day for hard mode only
}

// Day 2
string day_2::get_title() 
{
    return "THE INTERCEPTED SIGNAL";
}

void day_2::print_story(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    write_line("You follow the trail to a maintenance tunnel and meet Echo.");
    write_line("He is part of the Whistleblowers.");
    write_line("");
    
    // Adaptive dialogue based on public awareness level
    if (w.get_awareness() < THRESHOLD_LOW)
    {
        write_line("The tunnels are damp and silent.");
        write_line("Echo (Calm): 'You're hard to find. NeoCorp didn't even notice you.'");
    }
    else
    {
        write_line("The distant sound of sirens echoes through the vents.");
        write_line("Echo (Tense): 'The city is falling apart. We don't have much time.'");
    }

    write_line("");
    write_line("A security drone suddenly appears.");
}

void day_2::run_event(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    print_hint(mode, "Option [1] is required to unlock 'Eliminate Marcus' on Day 4.");

    write_line("");
    write_line("--- ACTION EVENT ---");
    write_line("[1] Command Drone to Arrest Echo (Order)");
    write_line("[2] Disable Drone Sensors to let Echo Speak (Freedom)");
    write_line("");

    if (mode == game_mode::HARD) 
    {
        write_line("⚠️ URGENT: DRONE SENSORS LOCKING ON. 10 SECONDS.");
        write_line("");
    }

    bool valid = false;
    while (!valid)
    {
        write("Select your option: ");
        string input = get_timed_input(mode, 10000);

        if (input == "TIMEOUT")
        {
            write_line("");
            write_line(">> ⏳ TOO SLOW! Drone auto-engaged target.");
            write_line(">> " + r.get_name() + " override confirmed.");
            write_line(">> FORCED OUTCOME: OPTION [1] (Echo Arrested)");
            input = "1"; 
        }

        if (input == "1") 
        {
            write_line("");
            write_line("🔵 Echo is captured. He spits, 'You'll regret this.'");
            p.adjust_loyalty(POINTS_MED);
            w.update_awareness(-IMPACT_LOW);
            p.add_tag(game_tags::ECHO_CAPTURED);
            valid = true;
        } 

        else if (input == "2") 
        {
            bool success = true;

            if (mode != game_mode::EASY)
            {
                write_line(">> INITIATING SIGNAL JAMMER...");
                delay(1000);
                success = run_minigame_2(mode);         // Launch minigame 2
            }

            if (success)
            {
                write_line("");
                write_line("🔵 SUCCESS: Drone sensors scrambled.");
                write_line(">> Echo sighs in relief and gives you a Key.");
                p.adjust_trust(POINTS_MED);
                w.update_awareness(IMPACT_LOW);
                p.add_tag(game_tags::BACKDOOR_KEY);
            }
            else
            {
                write_line("");
                write_line(">> FAILURE: Signal Lock Lost.");
                write_line(">> The drone detected you. You were forced to flee.");
                write_line(">> CONSEQUENCE: You missed the Key.");
                w.update_awareness(IMPACT_MED); 
            }
            valid = true;
        }
        else
        {
            write_line("Invalid input. Please enter 1 or 2.");
        }
    }

    trigger_rival(mode, r, p, w);
}

// Day 3
string day_3::get_title() 
{
    return "THE ARCHIVE INFILTRATION";
}

void day_3::print_story(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    write_line("You access the Deep Archives.");
    
    // Adaptive dialogue based on public awareness level
    if (w.get_awareness() > THRESHOLD_MED) 
        write_line("You hear protesters screaming outside the building.");
    else 
        write_line("The halls are eerily silent.");

    write_line("");
    write_line("You discover Zenith is a vaccine designed to control people, ");
    write_line("disguised as a cure to all diseases.");
}

void day_3::run_event(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    print_hint(mode, "'Copy Blueprints' (Option 2) is REQUIRED for the 'Compromise' ending.");

    write_line("");
    write_line("--- ACTION EVENT ---");
    write_line("[1] Seal the leak (Order)");
    write_line("[2] Copy blueprints (Freedom)");
    write_line("");

    if (mode == game_mode::HARD) 
    {
        write_line("⚠️ URGENT: SECURITY SWEEP INBOUND. 10 SECONDS.");
        write_line("");
    }

    bool valid = false;
    while (!valid)
    {
        write("Select your option: ");
        string input = get_timed_input(mode, 10000);

        if (input == "TIMEOUT")
        {
            write_line("");
            write_line(">> ⏳ TOO SLOW! Security sweep imminent.");
            write_line(">> " + r.get_name() + " locked the terminal remotely.");
            write_line(">> FORCED OUTCOME: OPTION [1] (Leak Sealed)");
            input = "1";
        }

        if (input == "1") 
        {
            write_line("");
            write_line("🔵 The world remains stable but blind.");
            p.adjust_loyalty(POINTS_SMALL);
            w.update_awareness(-IMPACT_MED);
            p.add_tag(game_tags::SEAL_LEAK);
            valid = true;
        } 
        else if (input == "2") 
        {
            write_line("");
            write_line("🔵 You now contain a copy of the blueprints.");
            p.adjust_trust(POINTS_SMALL);
            w.update_awareness(IMPACT_MED);
            p.add_tag(game_tags::HAS_BLUEPRINTS);
            valid = true;
        }
        else
        {
            write_line("Invalid input. Please enter 1 or 2.");
        }
    }

    trigger_rival(mode, r, p, w);
}

// Day 4
string day_4::get_title() 
{
    return "THE SCAPEGOAT";
}

void day_4::print_story(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    write_line("Your friend Marcus was caught on tape near the Archives.");
    write_line("You are both detained.");
    write_line("");

    // Adaptive dialogue based on player tags
    if (p.has_tag(game_tags::SEAL_LEAK))
        write_line("Officer: 'You saved our vision. Now dispose of Marcus.'");
    else if (p.has_tag(game_tags::HAS_BLUEPRINTS))
        write_line("Officer: 'A thief is among us. Who stole the blueprints?!'");
    else
        write_line("Officer: 'Explain yourselves.'");
}

void day_4::run_event(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    print_hint(mode, "Refusing to cooperate (Option 3) damages Loyalty severely.");

    write_line("");
    write_line("--- ACTION EVENT ---");
    
    if (p.has_tag(game_tags::ECHO_CAPTURED)) 
        write_line("[1] Eliminate Marcus (Order)");
    else 
        write_line("[LOCKED] Eliminate Marcus (Requires: Arrested Echo)");

    if (p.has_tag(game_tags::BACKDOOR_KEY)) 
        write_line("[2] Help Marcus Escape (Freedom)");
    else 
        write_line("[LOCKED] Help Marcus Escape (Requires: Backdoor Key)");
    
    write_line("[3] Refuse to Cooperate (Neutral)");
    write_line("");

    if (mode == game_mode::HARD) 
    {
        write_line("⚠️ URGENT: INTERROGATOR LOSING PATIENCE. 10 SECONDS.");
        write_line("");
    }

    bool valid = false;
    while (!valid)
    {
        write("Select your option: ");
        string input = get_timed_input(mode, 10000);

        if (input == "TIMEOUT")
        {
            write_line("");
            write_line(">> ⏳ TOO SLOW! The Officer sighs.");
            write_line(">> " + r.get_name() + " steps in to finish the job.");
            write_line(">> FORCED OUTCOME: OPTION [3] (Refused Cooperation)");
            input = "3"; 
        }

        if (input == "1" && p.has_tag(game_tags::ECHO_CAPTURED)) 
        {
            write_line("");
            write_line("🔵 The Executives trust you more.");
            p.adjust_loyalty(POINTS_MED);
            w.update_awareness(-IMPACT_LOW);
            valid = true;
        }
        else if (input == "2" && p.has_tag(game_tags::BACKDOOR_KEY)) 
        {
            write_line("");
            write_line("🔵 You gave Marcus the key. He escapes.");
            p.adjust_trust(POINTS_MED);
            w.update_awareness(IMPACT_LOW);
            p.add_tag(game_tags::MARCUS_ALLY);
            valid = true;
        }
        else if (input == "3") 
        {
            write_line("");
            write_line(">> Security wipes Marcus' memories.");
            p.adjust_loyalty(-POINTS_MED);
            w.update_awareness(IMPACT_LOW);
            p.add_tag(game_tags::INTEGRITY_RECORD);
            valid = true;
        }
        else 
        {
            write_line("Invalid selection or Locked path.");
        }
    }

    trigger_rival(mode, r, p, w);
}

// Day 5
string day_5::get_title() 
{
    return "THE SHADOW STRIKE";
}

void day_5::print_story(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    write_line("The CEO commands a strike on the rebels.");
    write_line("");
    
    // Adaptive dialogue based on public awareness level
    if (w.get_awareness() < THRESHOLD_HIGH)
        write_line("CEO (Calm): 'The public is asleep. Strike now for Total Order.'");
    else
        write_line("CEO (Shouting): 'The streets are a war zone! Trigger the strike now!'");
}

void day_5::run_event(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    print_hint(mode, "This decision has the biggest stat impact in the game.");

    write_line("");
    write_line("📍 CRITICAL DECISION POINT");
    write_line("[1] Command the Strike (Order)");
    write_line("[2] Warn the Rebels (Freedom)");
    write_line("");

    if (mode == game_mode::HARD) 
    {
        write_line("⚠️ URGENT: CEO AWAITING CONFIRMATION. 10 SECONDS.");
        write_line("");
    }

    bool valid = false;
    while (!valid)
    {
        write("Select your option: ");
        string input = get_timed_input(mode, 10000);

        if (input == "TIMEOUT")
        {
            write_line("");
            write_line(">> ⏳ TOO SLOW! CEO overrides your terminal.");
            write_line(">> " + r.get_name() + " confirmed the coordinates.");
            write_line(">> FORCED OUTCOME: OPTION [1] (Strike Confirmed)");
            input = "1"; 
        }

        if (input == "1") 
        {
            write_line("");
            write_line("🔵 The rebellion is broken.");
            p.adjust_loyalty(POINTS_HIGH);
            w.update_awareness(-IMPACT_HIGH);
            valid = true;
        } 
        else if (input == "2") 
        {
            write_line("");
            write_line("🔵 The city enters a state of high tension.");
            p.adjust_trust(POINTS_HIGH);
            w.update_awareness(IMPACT_HIGH);
            valid = true;
        }
        else
        {
            write_line("Invalid input. Please enter 1 or 2.");
        }
    }

    trigger_rival(mode, r, p, w);
}

// Day 6
string day_6::get_title() 
{
    return "THE FINALE";
}

void day_6::print_story(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    write_line("Highest floor of NeoCorp. Upload bar at 99%.");
    write_line("");

    // Adaptive dialogue based on public awareness level
    if (w.get_awareness() < THRESHOLD_CRITICAL) 
    {
        write_line("The city is terrifyingly quiet. Citizens stare blankly.");
        write_line("CEO: 'Perfect. Let's finish this.'");
    } 
    else 
    {
        write_line("The building shakes. Riots consume the lower districts.");
        write_line("Echo (Comms): 'Don't let their sacrifice be for nothing!'");
    }

    write_line("You have the Kill Switch in your hands.");
}
    
void day_6::run_event(player_state &p, world_state &w, game_mode mode, rival &r)  
{
    write_line("");
    write_line("📍 FINAL DECISION POINT");
    write_line("Every action you made has led to this point.");
    write_line("Choose wisely. This determines the fate of the world.");
    write_line("");
    write_line("--- ACTION EVENT ---");
    write_line("[1] Destroy Kill Switch (Order)");
    write_line("[2] Trigger Kill Switch (Freedom)");
    write_line("[3] Release Code (Compromise)");
    write_line("");

    if (mode == game_mode::HARD) write_line("⚠️ URGENT: UPLOAD AT 99%. DECIDE IN 10 SECONDS.");

    bool valid = false;
    while (!valid)
    {
        write_line("");
        write("Select your option: ");
        string input = get_timed_input(mode, 10000);

        // Timeout handling
        if (input == "TIMEOUT")
        {
            write_line("");
            write_line(">> ⏳ TIME OUT! The Upload completed automatically.");
            write_line(">> " + r.get_name() + " smiles from the shadows.");
            write_line(">> FORCED OUTCOME: OPTION [1] (Kill Switch Destroyed)");
            input = "1";
        }

        if (input == "1") 
        {
            trigger_order_ending(p);
            valid = true;
        }
        else if (input == "2") 
        {
            trigger_freedom_ending(p);
            valid = true;
        }
        else if (input == "3") 
        {
            trigger_compromise_ending(p, w);
            valid = true;
        }
        else 
        {
            write_line("Invalid selection.");
        }

        delay(500);
        write_line("");
        write_line("👾 GAME OVER - THANK YOU FOR PLAYING!");
    }
}
    
// Ending logic (Order)
void day_6::trigger_order_ending(player_state &p)
{
    write_line(">> You attempt to smash the Kill Switch...");
    p.adjust_loyalty(POINTS_MED); 

    // SUCCESS CONDITION: High Loyalty OR You arrested Echo earlier
    if (p.get_loyalty() > 50 || p.has_tag(game_tags::ECHO_CAPTURED))
    {
        write_line("🏆 ENDING ACHIEVED: TOTAL ORDER");
        write_line("The CEO nods approvingly. You help distribute the vaccine.");
        write_line("The world becomes peaceful, but they are mindless slaves to NeoCorp.");
        write_line("You are promoted to Head of Security.");
    }
    // FAIL CONDITION: Order but low stats/no tag
    else
    {
        write_line("🏆 ENDING ACHIEVED: THE TRAITOR'S FATE");
        write_line("The CEO frowns. 'Your performance review... was lacking.'");
        write_line("Security guards seize you. You weren't loyal enough to be trusted.");
        write_line("NeoCorp wins, but you are disposed of.");
    }
}

// Ending logic (Freedom)
void day_6::trigger_freedom_ending(player_state &p)
{
    write_line(">> You attempt to trigger the Kill Switch...");
    p.adjust_trust(POINTS_MED);

    if (p.get_trust() > 50 || p.has_tag(game_tags::MARCUS_ALLY))
    {
        write_line("🏆 ENDING ACHIEVED: TOTAL FREEDOM");
        write_line("Rebel hackers intercept the security turrets.");
        write_line("People regain free will, but the city collapses into riots.");
    }
    else if (p.has_tag(game_tags::DECRYPTED_COORDINATES))
    {
        write_line("🏆 ENDING ACHIEVED: THE SILENT HERO");
        write_line("The rebels didn't help, but you used the Day 1 Coordinates to hack it yourself!");
    }
    else
    {
        write_line("🏆 ENDING ACHIEVED: THE LONE WOLF");
        write_line("You reach for the switch, but a turret shoots you instantly.");
    }
}

// Ending logic (Compromise)
void day_6::trigger_compromise_ending(player_state &p, world_state &w)
{
    bool has_blueprints = p.has_tag(game_tags::HAS_BLUEPRINTS);
    bool integrity_or_chaos = (p.has_tag(game_tags::INTEGRITY_RECORD) || w.get_awareness() > THRESHOLD_CRITICAL);
    
    if (has_blueprints && integrity_or_chaos) 
    {
        write_line("🏆 ENDING ACHIEVED: COMPROMISE");
        write_line("You leak the formula's data. NeoCorp is forced to remove the brainwashing agent.");
    }
    else 
    {
        write_line("🏆 ENDING ACHIEVED: INCOMPLETE DATA");
        write_line("You try to release the code, but you are missing the Blueprints.");
    }
}
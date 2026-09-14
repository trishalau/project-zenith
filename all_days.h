#ifndef ALL_DAYS_H
#define ALL_DAYS_H

#include "day_scenario.h"
#include "splashkit.h"

using std::string;

// Day 1
class day_1 : public day_scenario 
{
    public:
        string get_title() override;
        void print_story(player_state &p, world_state &w, game_mode mode, rival &r) override;
        void run_event(player_state &p, world_state &w, game_mode mode, rival &r) override;
};

// Day 2
class day_2 : public day_scenario 
{
    public:
        string get_title() override;
        void print_story(player_state &p, world_state &w, game_mode mode, rival &r) override;
        void run_event(player_state &p, world_state &w, game_mode mode, rival &r) override;
};

// Day 3
class day_3 : public day_scenario 
{
    public:
        string get_title() override;
        void print_story(player_state &p, world_state &w, game_mode mode, rival &r) override;
        void run_event(player_state &p, world_state &w, game_mode mode, rival &r) override;
};

// Day 4
class day_4 : public day_scenario 
{
    public:
        string get_title() override;
        void print_story(player_state &p, world_state &w, game_mode mode, rival &r) override;
        void run_event(player_state &p, world_state &w, game_mode mode, rival &r) override;
};

// Day 5
class day_5 : public day_scenario 
{
    public:
        string get_title() override;
        void print_story(player_state &p, world_state &w, game_mode mode, rival &r) override;
        void run_event(player_state &p, world_state &w, game_mode mode, rival &r) override;
};

// Day 6
class day_6 : public day_scenario 
{
    public:
        string get_title() override;
        void print_story(player_state &p, world_state &w, game_mode mode, rival &r) override;
        void run_event(player_state &p, world_state &w, game_mode mode, rival &r) override;

    private:
        void trigger_order_ending(player_state &p);
        void trigger_freedom_ending(player_state &p);
        void trigger_compromise_ending(player_state &p, world_state &w);
};

#endif
# Project Zenith

A C++ text-based narrative and decision-making game set in a dystopian future (2072), built using the [SplashKit] (https://splashkit.io/) library.

## Overview

In **Project Zenith**, you play as an insider working inside the towers of NeoCorp. 
Over six intense days, you must navigate high-stakes choices between absolute corporate order and complete human freedom. 
Your decisions directly impact public awareness, corporate loyalty, and rebel trust, leading to one of several unique endings.

## Key Features

- **6-Day Narrative Arc:** Experience a branching storyline with dynamic dialogue that changes based on your past choices and the world's public awareness state.
- **Three Difficulty Modes:**
  - **Easy Mode:** Includes strategic hints to guide your decisions.
  - **Normal Mode:** Standard story experience with interactive minigames.
  - **Hard Mode:** Features a rival agent (Executive X) who sabotages your progress and introduces strict time pressure to your choices.
- **Interactive Minigames:** Engage in terminal-style hacking and decryption sequences built via SplashKit graphical windows.
- **Stat Tracking & Memory Tags:** The game remembers key actions through memory tags and stat systems (Corporate Loyalty vs. Rebel Trust).

## Prerequisites

To compile and run this project, you need:
- A C++ compiler supporting C++17 or later
- [SplashKit SDK](https://splashkit.io/install/) installed on your system

## Building and Running

1. Clone the repository:
   ```
   git clone [https://github.com/trishalauu-ai/project-zenith.git]
   cd ProjectZenith

3. Compile source files:
   ```
   g++ main.cpp game_engine.cpp player_state.cpp world_state.cpp rival.cpp day_scenario.cpp all_days.cpp minigames.cpp -lSplashKit -o project_zenith

5. Run game:
   ```
   ./project_zenith

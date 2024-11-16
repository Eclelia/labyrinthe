# Labyrinth Game

Welcome to **Labyrinth Game**, a maze-solving adventure where players navigate through challenging labyrinths, collect items, avoid traps, and try to set a high score! This game is built in C and uses the `ncurses` library for console-based graphics.

## Table of Contents
- [Game Objective](#game-objective)
- [Features](#features)
- [Installation](#installation)
- [Controls](#controls)
- [Gameplay](#gameplay)
- [Configuration](#configuration)
- [Documentation](#documentation)

## Game Objective

In **Labyrinth Game**, your goal is to navigate through a labyrinth and reach the exit:

- **Easy Mode**: Simply find your way to the exit.
- **Hard Mode**: Find the key first, avoid monsters, navigate around traps, and collect bonus cells to maximize your score.

The score is based on:
- The number of steps taken
- Encounters with traps, monsters, or bonus cells

The fewer steps and the more bonuses collected, the higher your score!

## Features

- **Main Menu**: At the start of the game, the player can choose one of the following options:
  1. **Create a New Labyrinth**: Define the size, name, and difficulty of a labyrinth and save it to a file.
  2. **Load an Existing Labyrinth**: Load a pre-existing labyrinth by entering its filename.
  3. **Play a Loaded Labyrinth**: Play the loaded labyrinth using `zqsd` controls. If you achieve a high score, you can enter your name into the leaderboard.
  4. **View Leaderboard**: Display the leaderboard for a specified labyrinth by entering its name.
  
- **Two Difficulty Modes**: Players can choose between Easy and Hard modes for different levels of challenge.
- **High Score Tracking**: Records and displays high scores for each labyrinth.
- **File Management**: Save and load labyrinths and their high scores.
- **Dynamic Labyrinth Creation**: Players can create and name custom labyrinths with various sizes and difficulties.

## Installation

1. **Install Dependencies**:
   - Ensure `ncurses` library is installed on your system.
     - **Ubuntu**: `sudo apt-get install libncurses5-dev libncursesw5-dev`
     - **MacOS**: `brew install ncurses`
   
2. **Build the Project**:
   - Run `make` at the root of the folder to compile the game.
   - Use `./labyrinth` to play the main game.
   - Use `./test_labyrinth` to run tests.

## Controls

The game is played by entering keyboard inputs based on the prompt. Controls vary depending on the game mode:

- **Main Menu Navigation**: Enter a number, letter, or string when prompted.
- **In-Game Movement**:
  - **z** - Move Up
  - **q** - Move Left
  - **s** - Move Down
  - **d** - Move Right
  - **ESC** - Exit the game

## Gameplay

1. **Creating a Labyrinth**: 
   - Choose "Create New Labyrinth" in the main menu.
   - Enter the labyrinth’s size, name, and difficulty level (Easy or Hard).
   - The program will save the labyrinth as a file.

2. **Loading and Playing a Labyrinth**:
   - Select "Load Existing Labyrinth" and specify the labyrinth file to load.
   - Then, choose "Play Loaded Labyrinth" to start the game.
   - Navigate through the maze using `zqsd` controls.
   - If you achieve a high score, you can enter your name to be saved in the leaderboard.

3. **Viewing Leaderboard**:
   - Select "View Leaderboard" from the main menu.
   - Enter the labyrinth’s name to see the current high scores.

## Configuration

To view the maze creation as an animation, you can set the `DISPLAY` constant to `1` in the source code. This will provide a step-by-step animated view of labyrinth generation.

## Documentation

This project includes documentation compatible with **Doxygen**. You can generate HTML documentation by opening the provided HTML file:

1. Open the generated HTML documentation file in a browser to view detailed descriptions of the project’s code, functions, and modules.

## License

This project is licensed under the MIT License.

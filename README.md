# Minesweeper-Game
Welcome to the Minesweeper game! This project is a recreation of the classic Minesweeper game using SFML (Simple and Fast Multimedia Library) in C++. The project is designed to provide an engaging experience while also exploring advanced programming concepts like graphics rendering, event handling, and file I/O.

# Features

    Classic Minesweeper gameplay: reveal tiles, avoid mines, and flag potential danger zones.
    Configurable grid size and mine count via a config.cfg file.
    Graphical interface including:
        A Welcome Window for player name entry.
        A Game Window displaying the grid and buttons (reset, debug, pause/play).
        A Leaderboard Window showcasing the top scores.
    Customizable buttons and interactive elements:
        Victory and defeat states with appropriate graphics.
        Real-time timer and mine counter.
        Debug mode for testing (shows all mine locations).
        
# Setup and Requirements
To run this project, you need the following:

    C++ Compiler:
        Ensure you have a compiler that supports C++11 or later.
    SFML (Simple and Fast Multimedia Library):
        Download and install SFML from SFML's website.
        Set up the environment variables to include SFML's library and include paths.

# Setting Up SFML

    If you are using CLion, configure CMakeLists.txt as per the provided project structure.
    Alternatively, follow these steps for manual setup:
        Download the appropriate version of SFML for your system.
        Add SFML's bin folder to your system's PATH (on Windows).
        Configure the library and include directories in your IDE/compiler.

For detailed guidance, refer to SFML tutorials.

Gameplay

    Welcome Window:
        Enter your name (up to 10 characters). Invalid inputs (numbers or special characters) are ignored.
        Press Enter to proceed to the game.

    Game Window:
        Left-click to reveal tiles.
        Right-click to place or remove flags.
        Use the Reset button to restart the game.
        Use the Debug button to toggle mine visibility (for testing).
        Press the Pause button to freeze the game.

    Victory Condition:
        Reveal all non-mine tiles to win. The remaining mines are flagged automatically.

    Defeat Condition:
        Clicking a mine ends the game. All mines are revealed.
        
# Leaderboard

The leaderboard stores the top five scores in files/leaderboard.txt. When a player wins, their time is compared with existing records. If the player makes it to the top five, the leaderboard is updated.


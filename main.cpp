#include <iostream>
#include <SFML/Graphics.hpp>
#include <cctype> // for std::alpha?
#include "Board.h"
#include "helpers.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string formatName(const std::string &input){
    std::string formatted;
    if(!input.empty()){
        formatted += std::toupper(input[0]);
        for(int i = 1; i < input.size(); i++){
            formatted += std::tolower(input[i]);
        }
    }
    return formatted;
}


void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

std::vector<std::string> readLeaderboard() {
    std::vector<std::string> leaderboard;
    std::ifstream file("files/leaderboard.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::replace(line.begin(), line.end(), ',', '\t'); // Replace commas with tabs
        leaderboard.push_back(line);
    }
    return leaderboard;
}

void displayLeaderboard(const std::vector<std::string>& leaderboard, int width, int height, bool &isClicked){
    sf::RenderWindow leaderBoardWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setFillColor(sf::Color::Blue);

    sf::Font font;
    if(!font.loadFromFile("files/font.ttf")){
        // error
    }
    sf::Text title;
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(20);
    setText(title, width / 2, height / 2 - 120);

    std::string leaderboardTextStr;
    for (const auto& entry : leaderboard) {
        leaderboardTextStr += entry + "\n\n";
    }
    sf::Text leaderboardText;
    leaderboardText.setFont(font);
    leaderboardText.setString(leaderboardTextStr);
    leaderboardText.setStyle(sf::Text::Bold);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setCharacterSize(18);
    setText(leaderboardText, width / 2, height / 2 + 20);



    // Window event loop for displaying the leaderboard
    while (leaderBoardWindow.isOpen()){
        sf::Event leaderEvent;
        while(leaderBoardWindow.pollEvent(leaderEvent)){
            if(leaderEvent.type == sf::Event::Closed){
                leaderBoardWindow.close();
                isClicked = false;
            }
        }

        leaderBoardWindow.clear();
        leaderBoardWindow.draw(background);
        leaderBoardWindow.draw(title);
        leaderBoardWindow.draw(leaderboardText);

        leaderBoardWindow.display();
    }
}
void updateLeaderboard(vector<std::string>& leaderboard, const std::string& playerName, int minutes, int seconds) {
    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << minutes << ":"
       << std::setw(2) << std::setfill('0') << seconds;
    std::string playerTime = ss.str();

    // Insert the new entry with an asterisk
    leaderboard.push_back(playerTime + "," + playerName + "*");

    // Sort the leaderboard based on time
    std::sort(leaderboard.begin(), leaderboard.end(), [](const std::string& a, const std::string& b) {
        // Extract the time part before the comma for comparison
        auto getTime = [](const std::string& entry) -> std::string {
            size_t commaPos = entry.find(',');
            return entry.substr(0, commaPos);
        };
        return getTime(a) < getTime(b);
    });

    // Keep only the top 5 entries
    if (leaderboard.size() > 5) {
        leaderboard.resize(5);
    }

    // Write the updated leaderboard back to the file
    std::ofstream file("leaderboard.txt");
    for (const auto& entry : leaderboard) {
        file << entry << std::endl;
    }
}

int main() {

    int value1;
    int value2;
    int value3;
    vector<int> configNums = helpers::readConfigValues("files/config.cfg", value1, value2, value3);
    int windowWidth = configNums[0] * 32;
    int windowHeight = (configNums[1] * 32) + 100;
    int mineCount = configNums[2];

    sf::RenderWindow welcomeWindow(sf::VideoMode(windowWidth, windowHeight), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
    sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));
    background.setFillColor(sf::Color::Blue);
    sf::Font font;
    if(!font.loadFromFile("files/font.ttf")){
        // error
    }
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("WELCOME TO MINESWEEPER!");
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setCharacterSize(24);
    setText(welcomeText, windowWidth / 2, windowHeight/2 - 150);

    sf::Text queryText;
    queryText.setFont(font);
    queryText.setString("Enter your name:");
    queryText.setStyle(sf::Text::Bold);
    queryText.setFillColor(sf::Color::White);
    queryText.setCharacterSize(20);
    setText(queryText, windowWidth / 2, windowHeight/2 - 75);

    sf::String playerInput;
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setStyle(sf::Text::Bold);
    playerText.setFillColor(sf::Color::Yellow);
    playerText.setCharacterSize(18);
    setText(playerText, windowWidth / 2, windowHeight/2 - 45);

    sf::RectangleShape cursor(sf::Vector2f(2, playerText.getCharacterSize()));
    cursor.setFillColor(sf::Color::Yellow);

    std::string currentText; // stores the user's name
    bool launchWindow = false;
    while(welcomeWindow.isOpen()){
        sf::Event event;
        while(welcomeWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                welcomeWindow.close();
            }
            if(event.type == sf::Event::TextEntered){
                if(std::isalpha(static_cast<char>(event.text.unicode))){
                    if(currentText.size() < 10){
                        currentText += static_cast<char>(event.text.unicode);
                        playerText.setString(formatName(currentText));
                    }
                }
                else if(event.text.unicode == 8 && !playerText.getString().isEmpty()){
                    currentText.pop_back();
                    playerText.setString(formatName(currentText));
                }
                else if(event.text.unicode == 13 && !playerText.getString().isEmpty()){
                    std::cout << playerText.getString().toAnsiString() << std::endl;
                    launchWindow = true;
                    welcomeWindow.close();
                }
                sf::FloatRect textRect = playerText.getLocalBounds();
                playerText.setOrigin(textRect.width / 2, textRect.height / 2);
                cursor.setPosition(playerText.getPosition().x + textRect.width / 2 + 5, playerText.getPosition().y);
            }
        }
        welcomeWindow.clear();
        welcomeWindow.draw(background);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(queryText);
        welcomeWindow.draw(playerText);
        welcomeWindow.draw(cursor);
        welcomeWindow.display();
    }


    if(launchWindow) {

        auto startTime = std::chrono::high_resolution_clock::now();
        bool leaderClicked = false;
        bool isPaused = false;
        std::chrono::high_resolution_clock::time_point  pauseTime;
        int totalSeconds = 0;

        sf::RenderWindow gameWindow(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
        sf::RectangleShape gameBackground(sf::Vector2f(windowWidth, windowHeight));
        gameBackground.setFillColor(sf::Color::White);


        Board gameBoard(configNums[0], configNums[1]);
        gameBoard.initialize(mineCount);


        textureManager::LoadTexture("pause");
        textureManager::LoadTexture("play");


        textureManager::LoadTexture("face_happy");
        textureManager::LoadTexture("debug");
        textureManager::LoadTexture("pause");
        textureManager::LoadTexture("leaderboard");
        textureManager::LoadTexture("face_win");
        textureManager::LoadTexture("face_lose");

        textureManager::LoadTexture("digits");


        sf::Sprite happyFaceButton(textureManager::getTexture("face_happy"));
        happyFaceButton.setPosition(((configNums[0] / 2.0) * 32) - 32, 32 * (configNums[1] + 0.5f));


        sf::Sprite debugButton(textureManager::getTexture("debug"));
        debugButton.setPosition((configNums[0] * 32) - 304, 32 * (configNums[1] + 0.5f));


        sf::Sprite pauseButton(textureManager::getTexture("pause"));
        pauseButton.setPosition((configNums[0] * 32) - 240, 32 * (configNums[1] + 0.5f));


        sf::Sprite leaderBoardButton(textureManager::getTexture("leaderboard"));
        leaderBoardButton.setPosition((configNums[0] * 32) - 176, 32 * (configNums[1] + 0.5f));


        sf::Texture& digitsTexture = textureManager::getTexture("digits");

        std::cout << "Happy Face Button Position: " << happyFaceButton.getPosition().x << ", " << happyFaceButton.getPosition().y << std::endl;
        std::cout << "Debug Position: " << debugButton.getPosition().x << ", " << happyFaceButton.getPosition().y << std::endl;
        std::cout << "Pause Position: " << pauseButton.getPosition().x << ", " << happyFaceButton.getPosition().y << std::endl;
        std::cout << "LeaderBoard Position: " << leaderBoardButton.getPosition().x << ", " << happyFaceButton.getPosition().y << std::endl;


        while (gameWindow.isOpen()) {

            sf::Event gameEvent;

            int minutes = totalSeconds / 60;
            int seconds = totalSeconds % 60;
            // Use helpers::digitizer to get digits for minutes and seconds
            auto minuteDigits = helpers::digitizer(minutes);
            auto secondDigits = helpers::digitizer(seconds);

            float minuteX = (configNums[0] * 32) - 97;
            float secondX = (configNums[0] * 32) - 54;
            float digitsY = 32 * (configNums[1] + 0.5f) + 16;


            while (gameWindow.pollEvent(gameEvent)) {

                if (gameEvent.type == sf::Event::Closed) {
                    gameWindow.close();
                }
                if (gameEvent.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow); // Get mouse position relative to the window

                    int tileWidth = 32; // Assuming each tile is 32x32 pixels
                    int tileX = mousePos.x / tileWidth;
                    int tileY = mousePos.y / tileWidth;


                    if(!leaderClicked && !isPaused) {
                        // Check if the click is within the bounds of the board
                        if (tileX < gameBoard.getWidth() && tileY < gameBoard.getHeight()) {
                            int tileIndex = tileY * gameBoard.getWidth() + tileX;
                            tile &clickedTile = gameBoard.getTile(tileIndex);

                            // Left click: reveal the tile
                            if (gameEvent.mouseButton.button == sf::Mouse::Left) {
                                // Implement the logic to reveal the tile
                                // This should handle the case where a mine is clicked (game over)
                                // and revealing adjacent tiles if the clicked tile has no adjacent mines
                                gameBoard.revealTile(&clickedTile);
                            }
                                // Right click: toggle a flag on the tile
                            else if (gameEvent.mouseButton.button == sf::Mouse::Right) {
                                // Implement the logic to toggle a flag
                                gameBoard.toggleFlag(&clickedTile);

                            }
                        }
                        if (debugButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            gameBoard.toggleDebug();
                            gameWindow.clear();
                            gameWindow.display();
                        }
                        if (happyFaceButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            gameBoard.initialize(mineCount);
                            gameBoard.resetGameState();
                            startTime = std::chrono::high_resolution_clock::now();
                            happyFaceButton.setTexture(textureManager::getTexture("face_happy"));
                        }
                    }
                    if (leaderBoardButton.getGlobalBounds().contains(mousePos.x, mousePos.y) || gameBoard.getVictory()){
                        //what happens when clicking on the leaderBoardButton?
                        if(!leaderClicked){
                            leaderClicked = true;
                        }
                        else{
                            leaderClicked = false;
                        }
                        vector<std::string> leaderboard = readLeaderboard();
                        if(gameBoard.getVictory()){
                            // use updateLeaderboard method
                            updateLeaderboard(leaderboard, playerInput.toAnsiString(), minutes, seconds);
                        }
                        displayLeaderboard(leaderboard, (configNums[0] * 16) + 50, configNums[1] * 16, leaderClicked);
                    }

                    // pause/play button
                    if (!gameBoard.isGameOver()) {
                        if (pauseButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            if (!isPaused) {
                                isPaused = true;
                                pauseTime = std::chrono::high_resolution_clock::now();
                                pauseButton.setTexture(textureManager::getTexture("play"));
                            } else {
                                isPaused = false;
                                auto currentTime = std::chrono::high_resolution_clock::now();
                                auto pauseDuration = currentTime - pauseTime;
                                startTime += pauseDuration;
                                pauseButton.setTexture(textureManager::getTexture("pause"));
                            }
                        }
                    }
                    else if(gameBoard.isGameOver() && !gameBoard.getVictory()){
                        happyFaceButton.setTexture(textureManager::getTexture("face_lose"));
                    }
                    else if(gameBoard.isGameOver() && gameBoard.getVictory()){
                        happyFaceButton.setTexture(textureManager::getTexture("face_win"));
                    }


                }
            }
            gameWindow.clear();
            gameWindow.draw(gameBackground);

            if(!isPaused || !leaderClicked){
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
                totalSeconds = static_cast<int>(elapsedTime);
            }




// Draw the minute digits
            for (int i = 0; i < 2; ++i) {
                sf::Sprite digitSprite(textureManager::getTexture("digits"));
                digitSprite.setTextureRect(sf::IntRect(minuteDigits[i] * 21, 0, 21, 32));
                digitSprite.setPosition(minuteX + (i * 21), digitsY);
                gameWindow.draw(digitSprite);
            }

// Draw the second digits
            for (int i = 0; i < 2; ++i) {
                sf::Sprite digitSprite(textureManager::getTexture("digits"));
                digitSprite.setTextureRect(sf::IntRect(secondDigits[i] * 21, 0, 21, 32));
                digitSprite.setPosition(secondX + (i * 21), digitsY);
                gameWindow.draw(digitSprite);
            }

            for (unsigned int i = 0; i < gameBoard.getHeight(); i++) {
                for (unsigned int j = 0; j < gameBoard.getWidth(); j++) {
                    tile &currentTile = gameBoard.getTile(i * gameBoard.getWidth() + j);
                    sf::Sprite tileSprite;
                    string textureName = "tile_hidden";
                    // gameBoard.getDebug() will return true or false if debug is on
                    // Decide which texture to use based on the tile's secretState
                    if(isPaused){
                        textureName = "tile_revealed";
                    }
                    else if(gameBoard.getDebug() && currentTile.getSecretState() == tile::secretState::MINE){
                        textureName = "mine";
                    }
                    else if(currentTile.getState() == tile::State::FLAGGED){
                        textureName = "flag";
                    }
                    else if (currentTile.getState() == tile::State::REVEALED) {
                        switch (currentTile.getSecretState()) {
                            case tile::secretState::MINE:
                                textureName = "mine";
                                break;
                            case tile::secretState::ONE:
                                textureName = "number_1";
                                break;
                            case tile::secretState::TWO:
                                textureName = "number_2";
                                break;
                            case tile::secretState::THREE:
                                textureName = "number_3";
                                break;
                            case tile::secretState::FOUR:
                                textureName = "number_4";
                                break;
                            case tile::secretState::FIVE:
                                textureName = "number_5";
                                break;
                            case tile::secretState::SIX:
                                textureName = "number_6";
                                break;
                            case tile::secretState::SEVEN:
                                textureName = "number_7";
                                break;
                            case tile::secretState::EIGHT:
                                textureName = "number_8";
                                break;
                            case tile::secretState::EMPTY:
                                textureName = "tile_revealed";
                                break;
                            default:
                                textureName = "tile_revealed"; // No adjacent mines or not a mine
                        }
                    }
                    else {
                        textureName = "tile_hidden";
                    }

                    tileSprite.setTexture(textureManager::getTexture(textureName));
                    tileSprite.setPosition(j * 32, i * 32);
                    gameWindow.draw(tileSprite);
                }
            }



            int mineCounter = gameBoard.getMineCount() - gameBoard.getFlagCount();
            auto counterDigits = helpers::digitizer(std::abs(mineCounter));
            float counterX = 12;
            float counterY = 32 * (configNums[1] + 0.5f) + 16;

// If the counter is negative, draw the '-' sign
            if (mineCounter < 0) {
                sf::Sprite minusSign(textureManager::getTexture("digits"));
                minusSign.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32)); // Assuming the '-' is the 10th sprite in the digits.png
                minusSign.setPosition(12, counterY);
                gameWindow.draw(minusSign);
                counterX += 21; // Move to the right for the next digit
            }

// Draw the counter digits
            for (size_t i = 0; i < counterDigits.size(); ++i) {
                sf::Sprite digitSprite(textureManager::getTexture("digits"));
                digitSprite.setTextureRect(sf::IntRect(counterDigits[i] * 21, 0, 21, 32));
                digitSprite.setPosition(counterX + (i * 21), counterY);
                gameWindow.draw(digitSprite);
            }

            gameWindow.draw(happyFaceButton);
            gameWindow.draw(debugButton);
            gameWindow.draw(pauseButton);
            gameWindow.draw(leaderBoardButton);
            gameWindow.display();
        }
    }
    return 0;
}


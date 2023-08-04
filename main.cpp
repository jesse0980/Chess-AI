#include <SFML/Graphics.hpp>
#include <chrono>
#include "board.h"

int main()
{
    const int windowWidth = 400;
    const int windowHeight = 400;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Jesse's Chess");
    bool isMousePressed = false;
    vector<int> start;
    vector<int> currPiece;
    vector<vector<int>> highs;
    bool redTurn = true; 
    
    Board* b = new Board();

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){

                isMousePressed = true;
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                currPiece = b->clicked(window, mousePosition.x, mousePosition.y);
                if(currPiece.size() > 0){
                    start = {b->track[currPiece[0]][currPiece[1]].x, b->track[currPiece[0]][currPiece[1]].y};
                    highs = b->highlightSquares(currPiece);
                }
            }
            if(event.type == sf::Event::MouseButtonReleased){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                b->landPiece(currPiece, mousePosition.x, mousePosition.y, start, redTurn);
                if(currPiece.size() > 0){
                    b->unhighlightSquares(highs);
                }
                isMousePressed = false;
            }
        }
        if(isMousePressed){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if(currPiece.size() > 0){
                    b->setPiece(currPiece, mousePosition.x, mousePosition.y);
                }
                
        }

        window.clear();
        b->drawBoard(window, windowWidth, windowHeight);
        window.display();
        
        int over = b->isOver();
        if(over != 0){
            auto start = std::chrono::high_resolution_clock::now();
            window.clear(sf::Color::Black);

            sf::Font font;
            font.loadFromFile("Roboto-Black.ttf");
            
            string s = over == 1 ? "Black Lost" : "Red Lost";
            sf::Text text(s, font, 60);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);

            // Center the text on the screen
            float x = (window.getSize().x - text.getLocalBounds().width) / 2;
            float y = (window.getSize().y - text.getLocalBounds().height) / 2;
            text.setPosition(x, y);

            // Draw the "You Lost" text on the window
            window.draw(text);
            window.display();
            while (true) {
                auto now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = now - start;
                if (elapsed.count() >= 2.0) {
                    break; // Exit the loop after 5 seconds
                }
            }
            delete b;
            b = new Board();
            redTurn = true;
        }
    }

    return 0;
}
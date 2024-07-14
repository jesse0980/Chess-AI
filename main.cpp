#include <SFML/Graphics.hpp>
#include "board.h"
//command to build it: g++ main.cpp -o main -I"C:\SFML-2.6.0\SFML-2.6.0\include" -L"C:\SFML-2.6.0\SFML-2.6.0\lib" -lsfml-graphics -lsfml-window -lsfml-system
int main()
{
    const int windowWidth = 400;
    const int windowHeight = 475;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Jesse's Chess");
    bool isMousePressed = false;
    sf::Font font;
    font.loadFromFile("Roboto-Black.ttf");
    vector<int> start;
    vector<int> currPiece;
    vector<vector<int>> highs;
    bool redTurn = true; 

    //AI Thinking Display
    sf::Text ai_thinks("AI is Thinking...", font, 34);
    ai_thinks.setFillColor(sf::Color::White);
    ai_thinks.setStyle(sf::Text::Bold);

    float x = (window.getSize().x - ai_thinks.getLocalBounds().width) / 2 + 62;
    float y = (window.getSize().y - ai_thinks.getLocalBounds().height) - 25;
    ai_thinks.setPosition(x, y);

    //AI Picture
    sf::Texture texture;
    texture.loadFromFile("images/IMG_3792.PNG");
    sf::Sprite john(texture);
    john.setScale(.07, .07);
    john.setPosition(40, 400);

    
    Board* b = new Board();

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                    window.close();
            if(!redTurn){
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
                    int check = b->landPiece(currPiece, mousePosition.x, mousePosition.y, start, redTurn);
                    if(currPiece.size() > 0){
                        b->unhighlightSquares(highs);
                    }
                    isMousePressed = false;
                    if(check == 0)
                        redTurn = true;
                }

                if(isMousePressed){
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                        if(currPiece.size() > 0){
                            b->setPiece(currPiece, mousePosition.x, mousePosition.y);
                        } 
                }
            }

        }

        window.clear();
        b->drawBoard(window, windowWidth, windowHeight);
        
        if(redTurn){
                ai_thinks.setFillColor(sf::Color::White);
                window.clear();
                window.draw(john);
                window.draw(ai_thinks);
                b->drawBoard(window, windowWidth, windowHeight);
                window.display();
                if(b->makeAiMove() == 0)
                    redTurn = false;
                ai_thinks.setFillColor(sf::Color::Transparent);
        }
        window.display();
        
        int over = b->isOver();
        if(over != 0){
            auto start = std::chrono::high_resolution_clock::now();
            window.clear(sf::Color::Black);

            
            
            string s = over == 1 ? "You Lost" : "You Beat Me!";
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
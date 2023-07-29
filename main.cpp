#include <SFML/Graphics.hpp>

#include "board.h"

int main()
{
    const int windowWidth = 400;
    const int windowHeight = 400;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chess");
    bool isMousePressed = false;
    vector<int> start;
    vector<int> currPiece;
    
    Board b;

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
                currPiece = b.clicked(window, mousePosition.x, mousePosition.y);
                if(currPiece.size() > 0){
                    start = {b.track[currPiece[0]][currPiece[1]].x, b.track[currPiece[0]][currPiece[1]].y};
                }
            }
            if(event.type == sf::Event::MouseButtonReleased){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                b.landPiece(currPiece, mousePosition.x, mousePosition.y, start);
                isMousePressed = false;
            }
        }
        if(isMousePressed){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if(currPiece.size() > 0){
                    b.setPiece(currPiece, mousePosition.x, mousePosition.y);
                }
                
        }

        window.clear();
        b.drawBoard(window, windowWidth, windowHeight);
        window.display();
    }

    return 0;
}
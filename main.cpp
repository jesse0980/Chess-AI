#include <iostream>
#include <SFML/Graphics.hpp>

const int windowWidth = 400;
const int windowHeight = 400;
const int boardSize = 8;
const int squareSize = windowWidth / boardSize;

// Define a two-dimensional array to represent the chessboard
char chessboard[boardSize][boardSize] = {
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
};

// Function to draw the pieces on the chessboard
void drawChessboard(sf::RenderWindow& window)
{
    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
    sf::Font font;
    font.loadFromFile("Roboto-Black.ttf"); // Replace with the path to your preferred font file

    for (int y = 0; y < boardSize; y++)
    {
        for (int x = 0; x < boardSize; x++)
        {
            square.setPosition(x * squareSize, y * squareSize);
            square.setFillColor((x + y) % 2 == 0 ? sf::Color::White : sf::Color::Blue);
            window.draw(square);

            if (chessboard[y][x] != ' ')
            {
                sf::Text text;
                text.setFont(font);
                text.setString(chessboard[y][x]);
                text.setCharacterSize(30);
                text.setPosition(x * squareSize + 10, y * squareSize + 5);
                text.setFillColor(sf::Color::Black);
                window.draw(text);
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chessboard");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw the chessboard with pieces
        drawChessboard(window);

        window.display();
    }

    return 0;
}
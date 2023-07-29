#include <iostream>
#include <string.h>
using namespace std;
#include <vector>

#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
class Tile{
    public:
        bool filled = false;
        int x = -1;
        int y = -1;
        string color = "White";
};
class Piece{
    public:
        char team = 'W';
        bool taken = false;
        int x = -1;
        int y = -1;
        char type = '0';
        bool start = true;  
};


class Board{
    public:
    Tile tracker[8][8];
    Piece track[2][8];
    sf::Font font;
    const int boardSize = 8;
    Board(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; ++j){
                Tile tmp;
                if(j == 6 || j == 7){
                    tmp.filled = true;
                }
                tracker[i][j] = tmp;

                
                
            }
        }

        for(int i = 0; i < 8; i++){
            Piece tmp; 
            tmp.type = 'p';
            

            sf::RectangleShape rect(sf::Vector2f(50, 50));
            rect.setPosition(i * 50, 300);

            sf::Text text("Centered Text", font, 30);
            text.setString(tmp.type);

            vector<float> c = centerSquare(text, rect);

            tmp.x = c[0];
            tmp.y = c[1];

            track[0][i] = tmp;
        }

        string pieces = "rkbqKbkr";
        for(int i = 0; i < pieces.length(); i++){
            Piece tmp; 
            tmp.type = pieces[i];
            

            sf::RectangleShape rect(sf::Vector2f(50, 50));
            rect.setPosition(i * 50, 350);

            sf::Text text("Centered Text", font, 30);
            text.setString(tmp.type);

            vector<float> c = centerSquare(text, rect);

            tmp.x = c[0];
            tmp.y = c[1];

            track[1][i] = tmp;
        }

    }

    vector<int> getSquare(int x, int y){
        vector<int> coord;
        for(int i = 0; i < boardSize; i++){
                for(int j = 0; j < boardSize; j++){
                    sf::RectangleShape rect(sf::Vector2f(50, 50));
                    rect.setPosition(tracker[i][j].x, tracker[i][j].y);
                     if (rect.getGlobalBounds().contains(x, y)) {
                        coord.push_back(i);
                        coord.push_back(j);
                        return coord;
                    }
            }
        }
        return coord;
    }

    vector<float> centerSquare( sf::Text text,  sf::RectangleShape rect){
            
            float textX = (rect.getPosition().x + (rect.getSize().x - 0) / 2) - 7;
            float textY = (rect.getPosition().y + (rect.getSize().y - 0) / 2) - 19;

            vector<float> ans;
            ans.push_back(textX);
            ans.push_back(textY);
            return ans;

    }

    void drawSquares(sf::RenderWindow& window, int width, int height){
            int squareSize = width / boardSize;

            for(int i = 0; i < boardSize; i++){
                for(int j = 0; j < boardSize; j++){
                    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                    int x = i * squareSize;
                    int y = j * squareSize;

                    tracker[i][j].x = x;
                    tracker[i][j].y = y;

                    //Draw the Squares
                    square.setPosition(x, y);
                    if(i % 2 == 0 || x == 0){
                        if(j % 2 == 0 || j == 0){
                            square.setFillColor(sf::Color::White);
                        }
                        else{
                            square.setFillColor(sf::Color::Blue);
                        }
                    }
                    else{
                        if(j % 2 == 0 || j == 0){
                            square.setFillColor(sf::Color::Blue);
                        }
                        else{
                            square.setFillColor(sf::Color::White);
                        }
                    }

                    window.draw(square);
                }
            }
    }
    void drawPieces(sf::RenderWindow& window, int width, int height, sf::Font font){
         for(int i = 0; i < 2; i++){
                for(int j = 0; j < 8; j++){
                    if (track[i][j].x == -1){
                        continue;
                    }
                    sf::Text text;
                    text.setFont(font);
                    text.setString(track[i][j].type);
                    text.setPosition(track[i][j].x, track[i][j].y);
                    text.setFillColor(sf::Color::Black);
                    window.draw(text);
                }
            }

    }
    void drawBoard(sf::RenderWindow& window, int width, int height){
            
            font.loadFromFile("Roboto-Black.ttf");

            this->drawSquares(window, width, height);
            
            this->drawPieces(window, width, height, font);


    } 
    vector<int> clicked(sf::RenderWindow& window, int x, int y){
        vector<int> coord;
        for(int i = 0; i < 2; i++){
                for(int j = 0; j < 8; j++){
                    if (track[i][j].x == -1){
                        continue;
                    }
                    sf::Text text;
                    text.setFont(font);
                    text.setString(track[i][j].type);
                    text.setPosition(track[i][j].x, track[i][j].y);
                     if (text.getGlobalBounds().contains(x, y)) {
                        coord.push_back(i);
                        coord.push_back(j);
                        return coord;
                    }
                }
        }
        return coord;
    }

    void setPiece(vector<int> c, int x, int y){
        track[c[0]][c[1]].x = x;
        track[c[0]][c[1]].y = y;

    }

    void landPiece(vector<int> c, int x, int y, vector<int> start){
        cout << "yes" << endl;

        vector<int> sq = getSquare(x, y);
        if(c.size() == 0){
            return;
        }
        if(sq.size() == 0){
            track[c[0]][c[1]].x = start[0];
            track[c[0]][c[1]].y = start[1];
            cout << "badPlace" << endl;
            return;
        }

        if(!isValidMove(c, sq, start)){
            track[c[0]][c[1]].x = start[0];
            track[c[0]][c[1]].y = start[1];
            return;
        }
        
        sf::RectangleShape rect(sf::Vector2f(50, 50));
        rect.setPosition(tracker[sq[0]][sq[1]].x,tracker[sq[0]][sq[1]].y);
        
        sf::Text text("Centered Text", font, 30);
        text.setString(track[c[0]][c[1]].type);
        cout << "reached" << endl;

        vector<float> loc = centerSquare(text, rect);
        
        track[c[0]][c[1]].x = loc[0];
        track[c[0]][c[1]].y = loc[1];
    }

    bool checkPawn(vector<int> piece, vector<int> sq, vector<int>start){
        vector<int> startSQ = getSquare(start[0], start[1]);
        if(tracker[sq[0]][sq[1]].filled){
            cout << "filled" << endl;
        }
        
        if(sq[1] >= 0 && sq[1] + 1 == startSQ[1] && sq[0] == startSQ[0]){
            track[piece[0]][piece[1]].start = false;
            return true;
        }
        else if(sq[1] + 2 == startSQ[1] && sq[0] == startSQ[0] && track[piece[0]][piece[1]].start == true){
            track[piece[0]][piece[1]].start = false;
            return true;
        }
        //cout << startSQ[0] << " " << startSQ[1] << " END: " << sq[0] << " " << sq[1] << endl;
        return false;
    }
    bool checkKing(vector<int> piece, vector<int> sq, vector<int>start){
        vector<int> startSQ = getSquare(start[0], start[1]);
        if(tracker[sq[0]][sq[1]].filled){
            cout << "filled" << endl;
        }
        if(sq[1] >= 0 && sq[1] + 1 == startSQ[1] && sq[0] == startSQ[0]){
            return true;
        }
        if(sq[1] < 8 && sq[1] - 1 == startSQ[1] && sq[0] == startSQ[0]){
            return true;
        }
        if(sq[0] < 8 && sq[0] - 1 == startSQ[0] && sq[1] == startSQ[1]){
            return true;
        }
        if(sq[0] >= 0 && sq[0] + 1 == startSQ[0] && sq[1] == startSQ[1]){
            return true;
        }
        if(sq[0] >= 0 && sq[0] + 1 == startSQ[0] && sq[1] >= 0 && sq[1] + 1 == startSQ[1]){
            return true;
        }
        if(sq[0] < 8 && sq[0] - 1 == startSQ[0] && sq[1] < 8 && sq[1] - 1 == startSQ[1]){
            return true;
        }
        if(sq[0] < 8 && sq[0] - 1 == startSQ[0] && sq[1] >= 0 && sq[1] + 1 == startSQ[1]){
            return true;
        }
        if(sq[0] >= 0 && sq[0] + 1 == startSQ[0] && sq[1] < 8 && sq[1] - 1 == startSQ[1]){
            return true;
        }
        return false;


    }
    bool checkDiag(vector<int> piece, vector<int> sq, vector<int>start){
        vector<int> startSQ = getSquare(start[0], start[1]);
        if(tracker[sq[0]][sq[1]].filled){
            cout << "filled" << endl;
        }
        for(int i = 0; i < 8; ++i){
            if(sq[0] >= 0 && sq[0] + i == startSQ[0] && sq[1] >= 0 && sq[1] + i == startSQ[1]){
                return true;
            }
            if(sq[0] < 8 && sq[0] - i == startSQ[0] && sq[1] < 8 && sq[1] - i == startSQ[1]){
                return true;
            }
            if(sq[0] < 8 && sq[0] - i == startSQ[0] && sq[1] >= 0 && sq[1] + i == startSQ[1]){
                return true;
            }
            if(sq[0] >= 0 && sq[0] + i == startSQ[0] && sq[1] < 8 && sq[1] - i == startSQ[1]){
                return true;
            }
        }
        return false;
    }
    bool checkRows(vector<int> piece, vector<int> sq, vector<int>start){
        vector<int> startSQ = getSquare(start[0], start[1]);
        if(tracker[sq[0]][sq[1]].filled){
            cout << "filled" << endl;
        }
        for(int i = 0; i < 8; ++i){
            if(sq[1] >= 0 && sq[1] + i == startSQ[1] && sq[0] == startSQ[0]){
                return true;
            }
            if(sq[1] < 8 && sq[1] - i == startSQ[1] && sq[0] == startSQ[0]){
                return true;
            }
            if(sq[0] < 8 && sq[0] - i == startSQ[0] && sq[1] == startSQ[1]){
                return true;
            }
            if(sq[0] >= 0 && sq[0] + i == startSQ[0] && sq[1] == startSQ[1]){
                return true;
            }
        }
        return false;
    }
    bool checkKnight(vector<int> piece, vector<int> sq, vector<int>start){
        vector<int> startSQ = getSquare(start[0], start[1]);
        if(tracker[sq[0]][sq[1]].filled){
            cout << "filled" << endl;
        }
        
        if(sq[1] >= 0 && sq[1] + 2 == startSQ[1] && sq[0] >= 0 && sq[0] + 1 == startSQ[0]){
            return true;
        }
        if(sq[1] >= 0 && sq[1] + 2 == startSQ[1] && sq[0] < 8 && sq[0] - 1 == startSQ[0]){
            return true;
        }
        if(sq[1] < 8 && sq[1] - 2 == startSQ[1] && sq[0] < 8 && sq[0] - 1 == startSQ[0]){
            return true;
        }
        if(sq[1] < 8 && sq[1] - 2 == startSQ[1] && sq[0] >= 0 && sq[0] + 1 == startSQ[0]){
            return true;
        }
        if(sq[1] >= 0 && sq[1] + 1 == startSQ[1] && sq[0] < 8 && sq[0] - 2 == startSQ[0]){
            return true;
        }
        if(sq[1] >= 0 && sq[1] + 1 == startSQ[1] && sq[0] >= 0 && sq[0] + 2 == startSQ[0]){
            return true;
        }
        if(sq[1] >= 0 && sq[1] - 1 == startSQ[1] && sq[0] < 8 && sq[0] - 2 == startSQ[0]){
            return true;
        }
        if(sq[1] >= 0 && sq[1] - 1 == startSQ[1] && sq[0] >= 0 && sq[0] + 2 == startSQ[0]){
            return true;
        }
        return false;
    }
    bool isValidMove(vector<int> piece, vector<int> sq, vector<int>start){
        if(track[piece[0]][piece[1]].type == 'p'){
            cout << "is a paWN" << endl;
            return checkPawn(piece, sq, start);
        }
        if(track[piece[0]][piece[1]].type == 'K'){
            cout << "its the king" << endl;
            return checkKing(piece, sq, start);
        }
        if(track[piece[0]][piece[1]].type == 'b'){
            cout << "its the bishop" << endl;
            return checkDiag(piece, sq, start);
        }
        if(track[piece[0]][piece[1]].type == 'r'){
            cout << "It's the rook" << endl;
            return checkRows(piece, sq, start);
        }
        if(track[piece[0]][piece[1]].type == 'q'){
            cout << "It's the Queen!" << endl;
            return checkRows(piece, sq, start) || checkDiag(piece, sq, start);
        }
        if(track[piece[0]][piece[1]].type == 'k'){
            cout << "It's the knight" << endl;
            return checkKnight(piece, sq, start);
        }
        return false;
    }

};
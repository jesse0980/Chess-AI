#include <iostream>
#include <string.h>
using namespace std;
#include <vector>

#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Piece.h"

class AI{
    public:
    Tile tracker[8][8];
    Piece track[4][8];
    const int boardSize = 8;
    AI(Piece input_track[4][8], Tile input_tracker[8][8]){
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                tracker[i][j] = input_tracker[i][j];
            }
        }
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                track[i][j] = input_track[i][j];
            }
        }
    }
    bool evaluate(Piece arr[4][8]){
        int black = 0;
        int white = 0;
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 8; j++){
                int val = 0;
                if(arr[i][j].taken){
                    continue;
                }
                if(arr[i][j].type == 'p'){
                    val = 1;
                }
                else if(arr[i][j].type == 'k'){
                    val = 3;
                }
                else if(arr[i][j].type == 'b'){
                    val = 3;
                }
                else if(arr[i][j].type == 'q'){
                    val = 9;
                }
                else if(arr[i][j].type == 'r'){
                    val = 5;
                }
                else{
                    val = 100;
                }
                if(arr[i][j].team == 'B'){
                    black += val;
                }
                else{
                    white += val;
                }
            }
        }
        cout << "Black: " << black << " White: " << white << endl;
        return false;
    }
    
    vector<int> getSquare(Tile tile_arr[8][8], int x, int y){
        vector<int> coord;
        for(int i = 0; i < boardSize; i++){
                for(int j = 0; j < boardSize; j++){
                    sf::RectangleShape rect(sf::Vector2f(50, 50));
                    rect.setPosition(tile_arr[i][j].x, tile_arr[i][j].y);
                     if (rect.getGlobalBounds().contains(x, y)) {
                        coord.push_back(i);
                        coord.push_back(j);
                        return coord;
                    }
            }
        }
        return coord;
    }
    vector<int> getFilledPiece(Tile tile_arr[8][8], vector<int> sq, Piece arr[4][8]){

        sf::RectangleShape rect(sf::Vector2f(50, 50));
        rect.setPosition(tile_arr[sq[0]][sq[1]].x,tile_arr[sq[0]][sq[1]].y);
        vector<int> ans;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 8; j++){
                if(arr[i][j].taken){
                    continue;
                }
                if(rect.getGlobalBounds().contains(arr[i][j].x, arr[i][j].y)){
                    ans.push_back(i);
                    ans.push_back(j);
                }
            }
        }
        return ans;

    }
   
    vector<vector<int>> AI_blackPawnCheck(Tile tile_arr[8][8], Piece arr[4][8], int r, int c){
        vector<vector<int>> Moves;
        vector<int> startSQ = getSquare(tile_arr, arr[r][c].x, arr[r][c].y);

        vector<int> sq = {startSQ[0] + 1, startSQ[1] - 1};
        if(sq[0] < 8 && sq[1] >= 0 && tile_arr[sq[0]][sq[1]].filled){
            vector<int> fillP = getFilledPiece(tile_arr, sq, arr);
            if(arr[fillP[0]][fillP[1]].team != arr[r][c].team){
                Moves.push_back(sq);
            }
        }

        vector<int> sq1 = {startSQ[0] - 1, startSQ[1] - 1};
        if(sq1[0] >= 0 && sq1[1] >= 0 && tile_arr[sq1[0]][sq1[1]].filled){
            vector<int> fillP = getFilledPiece(tile_arr, sq1, arr);
            if(arr[fillP[0]][fillP[1]].team != arr[r][c].team){
                Moves.push_back(sq1);
            }
        }
        if(startSQ[1] - 1 >= 0){
            vector<int> sq2 = {startSQ[0], startSQ[1] - 1};
            if(tile_arr[sq2[0]][sq2[1]].filled){
                return Moves; 
            }
            Moves.push_back(sq2);
        }
        if(startSQ[1] - 2 >= 0 && arr[r][c].start){
            vector<int> sq3 = {startSQ[0], startSQ[1] - 2};
             if(tile_arr[sq3[0]][sq3[1]].filled){
                return Moves; 
            }
            Moves.push_back(sq3);
        }
        return Moves;
    }
    vector<vector<int>> AI_redPawnCheck(Tile tile_arr[8][8], Piece arr[4][8], int r, int c){
        vector<vector<int>> Moves;
        vector<int> startSQ = getSquare(tile_arr, arr[r][c].x, arr[r][c].y);

        vector<int> sq = {startSQ[0] + 1, startSQ[1] + 1};
        if(sq[0] < 8 && sq[1] < 8 && tile_arr[sq[0]][sq[1]].filled){
            vector<int> fillP = getFilledPiece(tile_arr, sq, arr);
            if(arr[fillP[0]][fillP[1]].team != arr[r][c].team){
                Moves.push_back(sq);
            }
        }

        vector<int> sq1 = {startSQ[0] - 1, startSQ[1] + 1};
        if(sq1[0] >= 0 && sq1[1] < 8 && tile_arr[sq1[0]][sq1[1]].filled){
            vector<int> fillP = getFilledPiece(tile_arr, sq1, arr);
            if(arr[fillP[0]][fillP[1]].team != arr[r][c].team){
                Moves.push_back(sq1);
            }
        }
        if(startSQ[1] + 1 < 8){
            vector<int> sq2 = {startSQ[0], startSQ[1] + 1};
            if(tile_arr[sq2[0]][sq2[1]].filled){
                return Moves; 
            }
            Moves.push_back(sq2);
        }
        if(startSQ[1] + 2 < 8 && arr[r][c].start){
            vector<int> sq3 = {startSQ[0], startSQ[1] + 2};
             if(tile_arr[sq3[0]][sq3[1]].filled){
                return Moves; 
            }
            Moves.push_back(sq3);
        }
        return Moves;
    }
    vector<vector<int>> AI_knightCheck(Tile tile_arr[8][8], Piece arr[4][8], int r, int c){
        vector<vector<int>> Moves;
        vector<int> startSQ = getSquare(tile_arr, arr[r][c].x, arr[r][c].y);
        vector<int> sq = {startSQ[0] - 1, startSQ[1] - 2,};
        if(sq[1] >= 0 && sq[0] >= 0){
            if(tile_arr[sq[0]][sq[1]].filled){
                    vector<int> piece = getFilledPiece(tile_arr, sq, arr);
                    if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                            Moves.push_back(sq);
                    }
            }
            else{
                Moves.push_back(sq);
            }
        }
        vector<int> sq1 = { startSQ[0] + 1, startSQ[1] - 2};
        if(sq1[1] >= 0 && sq1[0] < 8){
            if(tile_arr[sq1[0]][sq1[1]].filled){
                    vector<int> piece = getFilledPiece(tile_arr, sq1, arr);
                    if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                            Moves.push_back(sq1);
                    }
            }
            else{
                Moves.push_back(sq1);
            }
        }
        vector<int> sq2 = {startSQ[0] + 1, startSQ[1] + 2};
        if(sq2[1] < 8 && sq2[0] < 8){
            if(tile_arr[sq2[0]][sq2[1]].filled){
                    cout << "accessed" << endl;
                    vector<int> piece = getFilledPiece(tile_arr, sq2, arr);
                    if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                            Moves.push_back(sq2);
                    }
            }
            else{
                Moves.push_back(sq2);
            }
        }
        vector<int> sq3 = {startSQ[0] - 1, startSQ[1] + 2};
        if(sq3[1] < 8 && sq3[0] >= 0){
            if(tile_arr[sq3[0]][sq3[1]].filled){
                    vector<int> piece = getFilledPiece(tile_arr, sq3, arr);
                    if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                            Moves.push_back(sq3);
                    }
            }
            else{
                Moves.push_back(sq3);
            }
        }
        vector<int> sq4 = {startSQ[0] + 2, startSQ[1] - 1};
        if(sq4[1] >= 0 && sq4[0] < 8){
            if(tile_arr[sq4[0]][sq4[1]].filled){
                    vector<int> piece = getFilledPiece(tile_arr, sq4, arr);
                    if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                            Moves.push_back(sq4);
                    }
            }
            else{
                Moves.push_back(sq4);
            }
        }
        vector<int> sq5 = {startSQ[0] - 2, startSQ[1] - 1};
        if(sq5[1] >= 0 && sq5[0] >= 0){
            if(tile_arr[sq5[0]][sq5[1]].filled){
                    vector<int> piece = getFilledPiece(tile_arr, sq5, arr);
                    if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                            Moves.push_back(sq5);
                    }
            }
            else{
                Moves.push_back(sq5);
            }
        }
        vector<int> sq6 = {startSQ[0] + 2, startSQ[1] + 1};
        if(sq6[1] < 8 && sq6[0] < 8){
            if(tile_arr[sq6[0]][sq6[1]].filled){
                    vector<int> piece = getFilledPiece(tile_arr, sq6, arr);
                    if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                            Moves.push_back(sq6);
                    }
            }
            else{
                Moves.push_back(sq6);
            }
        }
        vector<int> sq7 = {startSQ[0] - 2, startSQ[1] + 1};
        if(sq7[1] < 8 && sq7[0] >= 0){
            if(tile_arr[sq7[0]][sq7[1]].filled){
                    vector<int> piece = getFilledPiece(tile_arr, sq7, arr);
                    if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                            Moves.push_back(sq7);
                    }
            }
            else{
                Moves.push_back(sq7);
            }
        }
        return Moves;
}
    
    vector<vector<int>> AI_bishopCheck(Tile tile_arr[8][8], Piece arr[4][8], int r, int c){
        vector<vector<int>> Moves;
        vector<int> startSQ = getSquare(tile_arr, arr[r][c].x, arr[r][c].y);
        //right and down
        for(int i = 1; i < 8; ++i){
            if(startSQ[0] + i > 7 || startSQ[1] + i > 7){
                break;
            }
            else if(tile_arr[startSQ[0] + i][startSQ[1] + i].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] + i, startSQ[1] + i} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] + i, startSQ[1] + i});
                    break;
                }
                else{
                    break;
                }
            }
            else{
                Moves.push_back({startSQ[0] + i, startSQ[1] + i});
            }
        }
        //left and up
        for(int i = 1; i < 8; ++i){
            if(startSQ[0] - i < 0 || startSQ[1] - i < 0){
                break;
            }
            else if(tile_arr[startSQ[0] - i][startSQ[1] - i].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] - i, startSQ[1] - i} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] - i, startSQ[1] - i});
                    break;
                }
                else{
                    break;
                }
            }
            else{
                Moves.push_back({startSQ[0] - i, startSQ[1] - i});
            }
        }
        //Up and right 
        for(int i = 1; i < 8; ++i){
            if(startSQ[0] + i > 7 || startSQ[1] - i < 0){
                break;
            }
            else if(tile_arr[startSQ[0] + i][startSQ[1] - i].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] + i, startSQ[1] - i} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] + i, startSQ[1] - i});
                    break;
                }
                else{
                    break;
                }
            }
            else{
                Moves.push_back({startSQ[0] + i, startSQ[1] - i});
            }
        }
        //Up and left
        for(int i = 1; i < 8; ++i){
            if(startSQ[0] - i < 0 || startSQ[1] + i > 7){
                break;
            }
            else if(tile_arr[startSQ[0] - i][startSQ[1] + i].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] - i, startSQ[1] + i} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] - i, startSQ[1] + i});
                    break;
                }
                else{
                    break;
                }
            }
            else{
                Moves.push_back({startSQ[0] - i, startSQ[1] + i});
            }
        }

        return Moves;
    }
    
    vector<vector<int>> AI_kingCheck(Tile tile_arr[8][8], Piece arr[4][8], int r, int c){
        vector<vector<int>> Moves;
        vector<int> startSQ = getSquare(tile_arr, arr[r][c].x, arr[r][c].y);
        cout << "King Started: " << startSQ[0] << " " << startSQ[1] << endl;

        if(startSQ[0] + 1 < 8 and startSQ[1] + 1 < 8){
            if(tile_arr[startSQ[0] + 1][startSQ[1] + 1].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] + 1, startSQ[1] + 1} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] + 1, startSQ[1] + 1});
                }
            }
            else{
                 Moves.push_back({startSQ[0] + 1, startSQ[1] + 1});
            }
        }
        if(startSQ[0] + 1 < 8 and startSQ[1] - 1 >= 0){
            if(tile_arr[startSQ[0] + 1][startSQ[1] - 1].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] + 1, startSQ[1] - 1} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] + 1, startSQ[1] - 1});
                }
            }
            else{
                 Moves.push_back({startSQ[0] + 1, startSQ[1] - 1});
            }
        }
        if(startSQ[0] + 1 < 8){
            if(tile_arr[startSQ[0] + 1][startSQ[1]].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] + 1, startSQ[1]} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] + 1, startSQ[1]});
                }
            }
            else{
                 Moves.push_back({startSQ[0] + 1, startSQ[1]});
            }
        }
        if(startSQ[0] - 1 < 8){
            if(tile_arr[startSQ[0] - 1][startSQ[1]].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] - 1, startSQ[1]} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] - 1, startSQ[1]});
                }
            }
            else{
                 Moves.push_back({startSQ[0] - 1, startSQ[1]});
            }
        }
        if(startSQ[1] + 1 < 8){
            if(tile_arr[startSQ[0]][startSQ[1] + 1].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0], startSQ[1] + 1} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0], startSQ[1] + 1});
                }
            }
            else{
                 Moves.push_back({startSQ[0], startSQ[1] + 1});
            }
        }
        if(startSQ[1] - 1 >= 0){
            if(tile_arr[startSQ[0]][startSQ[1] - 1].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0], startSQ[1] - 1} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0], startSQ[1] - 1});
                }
            }
            else{
                 Moves.push_back({startSQ[0], startSQ[1] - 1});
            }
        }
        if(startSQ[0] - 1 >= 0 && startSQ[1] - 1 >= 0){
            if(tile_arr[startSQ[0] - 1][startSQ[1] - 1].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] - 1, startSQ[1] - 1} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] - 1, startSQ[1] - 1});
                }
            }
            else{
                 Moves.push_back({startSQ[0] - 1, startSQ[1] - 1});
            }
        }
        if(startSQ[0] - 1 >= 0 && startSQ[1] + 1 < 8){
            if(tile_arr[startSQ[0] - 1][startSQ[1] + 1].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] - 1, startSQ[1] + 1} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] - 1, startSQ[1] + 1});
                }
            }
            else{
                 Moves.push_back({startSQ[0] - 1, startSQ[1] + 1});
            }
        }
        return Moves;
    }

    vector<vector<int>> AI_rookCheck(Tile tile_arr[8][8], Piece arr[4][8], int r, int c){
        vector<vector<int>> Moves;
        vector<int> startSQ = getSquare(tile_arr, arr[r][c].x, arr[r][c].y);
        
        for(int i = 1; i < 8; ++i){
            if(startSQ[0] + i > 7){
                break;
            }
            else if(tile_arr[startSQ[0] + i][startSQ[1]].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] + i, startSQ[1]} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] + i, startSQ[1]});
                    break;
                }
                else{
                    break;
                }
            }
            else{
                Moves.push_back({startSQ[0] + i, startSQ[1]});
            }
        }
        for(int i = 1; i < 8; ++i){
            if(startSQ[0] - i < 0){
                break;
            }
            else if(tile_arr[startSQ[0] - i][startSQ[1]].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0] - i, startSQ[1]} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0] - i, startSQ[1]});
                    break;
                }
                else{
                    break;
                }
            }
            else{
                Moves.push_back({startSQ[0] - i, startSQ[1]});
            }
        }
        for(int i = 1; i < 8; ++i){
            if(startSQ[1] + i > 7){
                break;
            }
            else if(tile_arr[startSQ[0]][startSQ[1] + i].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0], startSQ[1] + i} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0], startSQ[1] + i});
                    break;
                }
                else{
                    break;
                }
            }
            else{
                Moves.push_back({startSQ[0], startSQ[1] + i});
            }
        }
        for(int i = 1; i < 8; ++i){
            if(startSQ[1] - i < 0){
                break;
            }
            else if(tile_arr[startSQ[0]][startSQ[1] - i].filled){
                vector<int> piece = getFilledPiece(tile_arr,{startSQ[0], startSQ[1] - i} , arr);
                if(arr[piece[0]][piece[1]].team != arr[r][c].team){
                    Moves.push_back({startSQ[0], startSQ[1] - i});
                    break;
                }
                else{
                    break;
                }
            }
            else{
                Moves.push_back({startSQ[0], startSQ[1] - i});
            }
        }
        return Moves;
    }
    
    vector<vector<int>> getValidMoves(Piece arr[4][8], char t, Tile tile_arr[8][8], int r = -1, int c = -1){
        vector<vector<int>> moves;
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 8; j++){
                    if(arr[i][j].team != t || arr[i][j].taken || (i != r && r != -1) || (j != c && c != -1)){
                        continue;
                    }
                    if(arr[i][j].type == 'p'){

                        vector<vector<int>> Ps;
                        if(t == 'B'){
                            Ps = AI_blackPawnCheck(tile_arr, arr, i, j);
                        }
                        else{
                            Ps = AI_redPawnCheck(tile_arr, arr, i, j);
                        }
                        for(int k = 0; k < Ps.size(); ++k){
                            moves.push_back(Ps[k]);
                        }
                    }
                    else if(arr[i][j].type == 'k'){
                        vector<vector<int>> kM = AI_knightCheck(tile_arr, arr, i, j);
                        for(int k = 0; k < kM.size(); ++k){
                            moves.push_back(kM[k]);
                        } 
                    }
                    else if(arr[i][j].type == 'b'){
                        
                        vector<vector<int>> Bs = AI_bishopCheck(tile_arr, arr, i, j);
                        for(int k = 0; k < Bs.size(); ++k){
                            moves.push_back(Bs[k]);
                        } 
                    }
                    else if(arr[i][j].type == 'K'){
                        
                        vector<vector<int>> Bs = AI_kingCheck(tile_arr, arr, i, j);
                        for(int k = 0; k < Bs.size(); ++k){
                            moves.push_back(Bs[k]);
                        } 
                    }
                    else if(arr[i][j].type == 'q'){
                        vector<vector<int>> Bs = AI_rookCheck(tile_arr, arr, i, j);
                        for(int k = 0; k < Bs.size(); ++k){
                            moves.push_back(Bs[k]);
                        }
                        Bs = AI_bishopCheck(tile_arr, arr, i, j);
                        for(int k = 0; k < Bs.size(); ++k){
                            moves.push_back(Bs[k]);
                        }  
                    }
                    else if(arr[i][j].type == 'r'){
                        vector<vector<int>> Bs = AI_rookCheck(tile_arr, arr, i, j);
                        for(int k = 0; k < Bs.size(); ++k){
                            moves.push_back(Bs[k]);
                        } 
                    }
                }
            }
        return moves;
    }

};
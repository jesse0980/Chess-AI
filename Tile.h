#include <string>
#include <iostream> 
using namespace std; 
class Tile{
    public:
        bool filled = false;
        bool high = false;
        int fillR = 0;
        int fillC = 0;
        int x = -1;
        int y = -1;
        string color = "White";
        Tile() = default;
        Tile(const Tile& other) {
            filled = other.filled;
            high = other.high;
            fillR = other.fillR;
            fillC = other.fillC;
            x = other.x;
            y = other.y;
            color = other.color;
        }
};
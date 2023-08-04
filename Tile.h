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
};
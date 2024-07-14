class Piece{
    public:
        char team = 'W';
        bool taken = false;
        int x = -1;
        int y = -1;
        char type = '0';
        string imgPath = "";
        bool start = true;
        Piece() = default;
        Piece(const Piece& other) {
            // bool tmp = false;
            // if(other.taken){
            //     tmp = true;
            // }
            team = other.team;
            taken = other.taken;
            x = other.x;
            y = other.y;
            type = other.type;
            start = other.start;
        }  
};
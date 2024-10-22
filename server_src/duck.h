#pragma once
#include <string>

typedef struct {
    int x;
    int y;
} Position;

class Duck {

    private:
        int duck_id;
        Position pos;

    public:
        Duck(int duck_id, int x, int y);
        
        int get_duck_id();
        Position get_pos();

        std::string serialize() ;

        Duck deserialize(std::string& data);

        void move(int x, int y);

};

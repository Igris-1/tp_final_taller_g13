#ifndef PICKABLE_H
#define PICKABLE_H

class Pickable{

    protected:
        int air_time_x = 300;
        int air_time_y = 50;
        
        int x_direction = 0;
        bool moving = true;

        int y_direction = 0;
        bool falling = false;
    public:

        virtual void use() = 0;       

        void air_time_down_y(){
            this->air_time_y--;
            if(air_time_y == 0){
                falling = true;
            }
        }
        void air_time_down_x(){
            this->air_time_x--;
            if(air_time_x == 0){
                moving = false;
            }
        }


        bool is_falling(){
            return falling;
        }
        bool is_moving(){
            return moving;
        }
        void set_falling(bool falling){
            this->falling = falling;
        }
        void set_moving(bool moving){
            this->moving = moving;
            if(moving){
                this->air_time_x = 300;
            }
        }
        int get_air_time_y(){
            return this->air_time_y;
        }
        int get_x_direction(){
            return this->x_direction;
        }
        void set_direction(int x, int y){
            this->x_direction = x;
            this->y_direction = y;
            this->air_time_y = 50;
            this->air_time_x = 300;
        }

        ~Pickable() = default;
};






#endif
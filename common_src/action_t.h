#ifndef ACTION_T_H
#define ACTION_T_H

typedef struct action { //comento lo q no se usa todavia
    int player_id = 0;
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool stop_right = false;
    bool stop_left = false;
    bool jump = false;
    bool stop_jump = false;
    bool press_action_button = false; 
    bool unpress_action_button = false;
    //bool create_duck = false;
    //representar con un solo byte 
    
} action_t;

#endif  // ACTION_T_H
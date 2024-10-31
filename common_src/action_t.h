#ifndef ACTION_T_H
#define ACTION_T_H

typedef struct action { //comento lo q no se usa todavia
    //int player_id = 0; 
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool stop_right = false;
    bool stop_left = false;
    //bool create_duck = false;
    //representar con un solo byte 
    //int press_action_button = 0; // capaz estos 2 se puedan...
    //int unpress_action_button = 0;//...cambiar por uno solo q haga toggle
    //int jump = 0;

} action_t;


#endif  // ACTION_T_H
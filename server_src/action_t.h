#ifndef ACTION_T_H
#define ACTION_T_H

typedef struct action { //comento lo q no se usa todavia
    //int player_id = 0; 
    bool left;
    bool right; 
    bool up;
    bool down;
    //int press_action_button = 0; // capaz estos 2 se puedan...
    //int unpress_action_button = 0;//...cambiar por uno solo q haga toggle
    //int jump = 0;

} action_t;


#endif  // ACTION_T_H
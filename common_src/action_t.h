#ifndef ACTION_T_H
#define ACTION_T_H
#include <cstdint>
typedef struct {
    uint8_t player_id = 0;
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
    bool press_pick_up_button = false;
    bool press_throw_button = false;
    bool press_crouch_button = false;
    bool unpress_crouch_button = false;
    bool press_look_up_button = false;
    bool unpress_look_up_button = false;

} action_t;

#endif  // ACTION_T_H
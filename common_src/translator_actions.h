#ifndef TRANSLATOR_ACTIONS_H
#define TRANSLATOR_ACTIONS_H

#include <cstdint>
enum {
    LEFT = 1 << 0,                   // 0b0000000000000001
    RIGHT = 1 << 1,                  // 0b0000000000000010
    UP = 1 << 2,                     // 0b0000000000000100
    DOWN = 1 << 3,                   // 0b0000000000001000
    STOP_RIGHT = 1 << 4,             // 0b0000000000010000
    STOP_LEFT = 1 << 5,              // 0b0000000000100000
    JUMP = 1 << 6,                   // 0b0000000001000000
    STOP_JUMP = 1 << 7,              // 0b0000000010000000
    PRESS_ACTION_BUTTON = 1 << 8,    // 0b0000000100000000
    UNPRESS_ACTION_BUTTON = 1 << 9,  // 0b0000001000000000
    PRESS_PICKUP_BUTTON = 1 << 10,   // 0b0000010000000000
    PRESS_THROW_BUTTON = 1 << 11,    // 0b0000100000000000

    PRESS_CROUCH_BUTTON = 1 << 12,    // 0b0001000000000000
    UNPRESS_CROUCH_BUTTON = 1 << 13,  // 0b0010000000000000
    PRESS_LOOK_UP_BUTTON = 1 << 14,   // 0b0100000000000000
    UNPRESS_LOOK_UP_BUTTON = 1 << 15  // 0b1000000000000000
};

class TranslatorActions {
private:
public:
    uint16_t create_flag(bool left, bool right, bool up, bool down, bool stop_right, bool stop_left,
                         bool jump, bool stop_jump, bool press_action_button,
                         bool unpress_action_button, bool press_pick_up_button,
                         bool press_throw_button, bool press_crouch_button,
                         bool unpress_crouch_button, bool press_look_up_button,
                         bool unpress_look_up_button) {
        uint16_t flags = 0;
        flags |= (left ? LEFT : 0);
        flags |= (right ? RIGHT : 0);
        flags |= (up ? UP : 0);
        flags |= (down ? DOWN : 0);
        flags |= (stop_right ? STOP_RIGHT : 0);
        flags |= (stop_left ? STOP_LEFT : 0);
        flags |= (jump ? JUMP : 0);
        flags |= (stop_jump ? STOP_JUMP : 0);
        flags |= (press_action_button ? PRESS_ACTION_BUTTON : 0);
        flags |= (unpress_action_button ? UNPRESS_ACTION_BUTTON : 0);
        flags |= (press_pick_up_button ? PRESS_PICKUP_BUTTON : 0);
        flags |= (press_throw_button ? PRESS_THROW_BUTTON : 0);
        flags |= (press_crouch_button ? PRESS_CROUCH_BUTTON : 0);
        flags |= (unpress_crouch_button ? UNPRESS_CROUCH_BUTTON : 0);
        flags |= (press_look_up_button ? PRESS_LOOK_UP_BUTTON : 0);
        flags |= (unpress_look_up_button ? UNPRESS_LOOK_UP_BUTTON : 0);

        return flags;
    };
    void translate_flags(const uint16_t action, bool& left, bool& right, bool& up, bool& down,
                         bool& stop_right, bool& stop_left, bool& jump, bool& stop_jump,
                         bool& press_action_button, bool& unpress_action_button,
                         bool& press_pick_up_button, bool& press_throw_button,
                         bool& press_crouch_button, bool& unpress_crouch_button,
                         bool& press_look_up_button, bool& unpress_look_up_button) {
        left = action & LEFT;
        right = action & RIGHT;
        up = action & UP;
        down = action & DOWN;
        stop_right = action & STOP_RIGHT;
        stop_left = action & STOP_LEFT;
        jump = action & JUMP;
        stop_jump = action & STOP_JUMP;
        press_action_button = action & PRESS_ACTION_BUTTON;
        unpress_action_button = action & UNPRESS_ACTION_BUTTON;
        press_pick_up_button = action & PRESS_PICKUP_BUTTON;
        press_throw_button = action & PRESS_THROW_BUTTON;

        press_crouch_button = action & PRESS_CROUCH_BUTTON;
        unpress_crouch_button = action & UNPRESS_CROUCH_BUTTON;
        press_look_up_button = action & PRESS_LOOK_UP_BUTTON;
        unpress_look_up_button = action & UNPRESS_LOOK_UP_BUTTON;
        // player_id = action & PLAYER_ID;
    };
};

#endif

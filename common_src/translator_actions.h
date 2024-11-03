#ifndef TRANSLATOR_ACTIONS_H
#define TRANSLATOR_ACTIONS_H

enum{
    LEFT        = 1 << 0,  // 0b0000000000000001
    RIGHT       = 1 << 1,  // 0b0000000000000010
    UP          = 1 << 2,  // 0b0000000000000100
    DOWN        = 1 << 3,  // 0b0000000000001000
    STOP_RIGHT  = 1 << 4,  // 0b0000000000010000
    STOP_LEFT   = 1 << 5,  // 0b0000000000100000
    JUMP        = 1 << 6,  // 0b0000000001000000
    STOP_JUMP   = 1 << 7,  // 0b0000000010000000

};

class TranslatorActions{
    private:

    public:
    uint16_t create_flag(bool left, bool right, bool up, bool down, bool stop_right, bool stop_left, bool jump, bool stop_jump){
    
        uint16_t flags = 0; 
        flags |= (left ? LEFT : 0);
        flags |= (right ? RIGHT : 0);
        flags |= (up ? UP : 0);
        flags |= (down ? DOWN : 0);
        flags |= (stop_right ? STOP_RIGHT : 0);
        flags |= (stop_left ? STOP_LEFT : 0);
        flags |= (jump ? JUMP : 0);
        flags |= (stop_jump ? STOP_JUMP : 0);
        return flags;
    };
    void translate_flags(const uint16_t action, bool& left, bool& right, bool& up, bool& down,
                    bool& stop_right, bool& stop_left, bool& jump, bool& stop_jump) {
        left        = action & LEFT;
        right       = action & RIGHT;
        up          = action & UP;
        down        = action & DOWN;
        stop_right  = action & STOP_RIGHT;
        stop_left   = action & STOP_LEFT;
        jump        = action & JUMP;
        stop_jump   = action & STOP_JUMP;
    };
};

#endif

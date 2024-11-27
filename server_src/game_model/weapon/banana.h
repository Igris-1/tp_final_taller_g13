#ifndef BANANA_H
#define BANANA_H

#include "../pickable.h"
#include <vector>


class Banana: public Pickable{

    private:
        bool active = false;
    
    public:

        Banana(int width, int height);
        void use(MapGame& map);
        int get_id() override;
        bool is_active() override;
        bool is_explosive() override;
        weapon_DTO to_DTO() override;
        ~Banana();

};




#endif  // BANANA_H
#ifndef WEAPON_INTERFACE_H
#define WEAPON_INTERFACE_H

#include "../bullets_strategy/bullet_interface.h"
#include "../../position.h"
#include "../../positionable.h"
#include <vector>

/*
    todas las armas deben tener dispersion, retroceso y tiempo de recarga, 
    PERO no todas las armas son afectadas por estos o de la misma forma.
    todas las armas devuelven una lista de balas que se disparan con una direccion y distancia establecida.
*/

class WeaponInterface {
    public:
        virtual std::vector<BulletInterface> fire(int x_position, int y_position, int x_direction, int y_direction, int dispersion) = 0;
        bool is_real(){
            return true;
        }
        virtual ~WeaponInterface(){}
}; 

#endif

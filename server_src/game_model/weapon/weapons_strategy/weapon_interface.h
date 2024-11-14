#ifndef WEAPON_INTERFACE_H
#define WEAPON_INTERFACE_H

#include "../bullets_strategy/bullet_interface.h"
#include "../../position.h"
#include "../../positionable.h"
#include <vector>
#include <memory>

/*
    todas las armas deben tener dispersion, retroceso y tiempo de recarga, 
    PERO no todas las armas son afectadas por estos o de la misma forma.
    todas las armas devuelven una lista de balas que se disparan con una direccion y distancia establecida.
*/

typedef enum{
    COWBOY_PISTOL_ID = 1,
    LASER_RIFLE_ID,
    GRENADE_ID,
}WEAPON_ID;

typedef enum {
    COWBOY_PISTOL_RECOIL = 0,
    LASER_RIFLE_RECOIL = 0,
    GRENADE_RECOIL = 0,
} RECOIL;

typedef enum {
    FIRE_RATE_COWBOY_PISTOL = 20,
    FIRE_RATE_LASER_RIFLE = 5,
    FIRE_RATE_GRENADE = 1000,
} FIRE_RATE;

class Duck;

class WeaponInterface {
    protected:
    int fire_rate = 0;
    public:
        virtual std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger, int x_position, int y_position, int x_direction, int y_direction) = 0;
        virtual void fire_rate_down();
        virtual int recoil_produced() = 0;
        virtual int get_id() = 0;
        // logico solo para explosivos
        virtual bool is_explosive();
        virtual bool is_active();
        virtual void activation();
        virtual bool exploted();
        // ---------------------------
        virtual ~WeaponInterface(){}

}; 

#endif

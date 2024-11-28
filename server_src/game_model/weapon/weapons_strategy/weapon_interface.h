#ifndef WEAPON_INTERFACE_H
#define WEAPON_INTERFACE_H

#include <memory>
#include <vector>

#include "../bullets_strategy/bullet_interface.h"

/*
    todas las armas deben tener dispersion, retroceso y tiempo de recarga,
    PERO no todas las armas son afectadas por estos o de la misma forma.
    todas las armas devuelven una lista de balas que se disparan con una direccion y distancia
   establecida.
*/

typedef enum {
    COWBOY_PISTOL_RECOIL = 0,
    LASER_RIFLE_RECOIL = 0,
    GRENADE_RECOIL = 0,
    AK47_RECOIL = 10,
    SHOTGUN_RECOIL = 15,
} RECOIL;

typedef enum {
    FIRE_RATE_COWBOY_PISTOL = 20,
    FIRE_RATE_LASER_RIFLE = 5,
    FIRE_RATE_AK47 = 2,
    FIRE_RATE_SHOTGUN = 35,
    FIRE_RATE_PEW_PEW = 10,
    
} FIRE_RATE;

typedef enum {
    TRAVEL_DISTANCE_COWBOY_PISTOL = 256,
    TRAVEL_DISTANCE_LASER_RIFLE = 1000,
    TRAVEL_DISTANCE_AK47 = 700,
    TRAVEL_DISTANCE_SHOTGUN = 400,
    TRAVEL_DISTANCE_PEW_PEW = 500,
} TRAVEL_DISTANCE;

class Duck;

class WeaponInterface {
protected:
    int fire_rate = 0;

public:
    virtual std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                               int x_position, int y_position,
                                                               int x_direction, int y_direction,
                                                               bool is_holding_button) = 0;
    virtual void fire_rate_down();
    virtual int recoil_produced() = 0;
    virtual int get_id() = 0;
    virtual ~WeaponInterface() {}
};

#endif

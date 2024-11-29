#ifndef WEAPON_INTERFACE_H
#define WEAPON_INTERFACE_H

#include <memory>
#include <vector>

#include "../bullets_strategy/bullet_interface.h"

#define TILE_SIZE 16

#define NO_SOUND 0
/*
    todas las armas deben tener dispersion, retroceso y tiempo de recarga,
    PERO no todas las armas son afectadas por estos o de la misma forma.
    todas las armas devuelven una lista de balas que se disparan con una direccion y distancia
   establecida.
*/
class Duck;

class WeaponInterface {
protected:
    int fire_rate = 0;

    // yaml read
    int shot;
    int damage;
    int recoil;
    int scope;
    int reload_time;

public:
    WeaponInterface(int shot, int damage, int recoil, int scope, int reload_time);
    virtual std::vector<std::shared_ptr<BulletInterface>> fire(std::shared_ptr<Duck> duck_trigger,
                                                               int x_position, int y_position,
                                                               int x_direction, int y_direction,
                                                               bool is_holding_button) = 0;
    virtual void fire_rate_down();
    virtual int recoil_produced() = 0;
    virtual int get_id() = 0;
    virtual int get_sound();
    virtual ~WeaponInterface() {}
};

#endif

#ifndef DUCK_H
#define DUCK_H

#include <memory>
#include <vector>

#include "../../common_src/duck_DTO.h"
#include "weapon/bullets_strategy/bullet_interface.h"
#include "weapon/weapons_strategy/weapon.h"
#include "weapon/weapons_strategy/weapon_factory.h"

#include "armor.h"
#include "helmet.h"
#include "positionable.h"

#define DUCK_WIDTH 32
#define DUCK_HEIGHT 48

class Duck: public Positionable, public std::enable_shared_from_this<Duck> {
private:
    // cppcheck-suppress unusedStructMember
    int duck_id;
    int health;
    int respawn_time = 100;
    std::shared_ptr<Armor> armor;
    std::shared_ptr<Helmet> helmet;
    std::shared_ptr<Weapon> weapon;
    // std::shared_ptr<Pickable> pickable;

public:
    // por defecto empieza en la posicion -1,-1 (fuera del mapa), con una armadura, casco y arma
    // nula (osea posicion -1,-1)
    explicit Duck(int health, int id);

    // devuelve la posicion actual y setea la nueva posicion (tambien mueve la armadura, casco y
    // arma)
    std::shared_ptr<Weapon> throw_weapon();
    std::shared_ptr<Weapon> take_weapon(std::shared_ptr<Weapon> weapon);
    std::shared_ptr<Armor> take_armor(std::shared_ptr<Armor> armor);
    std::shared_ptr<Helmet> take_helmet(std::shared_ptr<Helmet> helmet);

    // Weapon& get_weapon();
    // Armor& get_armor();
    // Helmet& get_helmet();
    int get_health();
    int get_id();

    void tick_respawn_time();
    int get_respawn_time();
    void set_health(int health);

    std::vector<std::shared_ptr<BulletInterface>> fire_weapon(int x_direction, int y_direction,
                                                              MapGame& map);
    void use_item(int x_direction, int y_direction, MapGame& map);
    bool is_alive();
    bool is_this_duck(int id);
    void receive_damage(int damage);
    Hitbox get_hitbox();
    void continue_fire_rate();
    bool has_weapon();
    // para granadas y bananas
    bool has_explosive_weapon();
    bool has_active_explosive_weapon();
    void activation_explosive_weapon();
    bool already_exploted();

    /*  devuelve los estados internos del duck en un dto (vida, id, posicion).
        no sabe nada de estados de jumping, running, ni nada*/
    duck_DTO to_DTO();
    ~Duck() {}
};

#endif

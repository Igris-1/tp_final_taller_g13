#ifndef DUCK_H
#define DUCK_H

#include <memory>
#include <vector>

#include "../../common_src/duck_DTO.h"
#include "weapon/bullets_strategy/bullet_interface.h"
#include "weapon/weapons_strategy/weapon_factory.h"

#include "armor.h"
#include "helmet.h"
#include "positionable.h"


class Pickable;
class Weapon;

#define DUCK_WIDTH 32
#define DUCK_HEIGHT 48

class Duck: public Positionable, public std::enable_shared_from_this<Duck> {
private:
    // cppcheck-suppress unusedStructMember
    int duck_id;
    int health;
    int begin_health;
    int respawn_time = 100;
    //std::shared_ptr<Weapon> items_in_hands;
    bool has_armor = false;
    bool has_helmet = false;
    int id_weapon;
    std::shared_ptr<Pickable> item_in_hands;

public:
    // por defecto empieza en la posicion -1,-1 (fuera del mapa), con una armadura, casco y arma
    // nula (osea posicion -1,-1)
    explicit Duck(int health, int id);

    // devuelve la posicion actual y setea la nueva posicion (tambien mueve la armadura, casco y
    // arma)
    std::shared_ptr<Pickable> throw_weapon();
    std::shared_ptr<Pickable> take_weapon(std::shared_ptr<Pickable> item);

    void add_armor();
    void add_helmet();
    // Weapon& get_weapon();
    // Armor& get_armor();
    // Helmet& get_helmet();
    int get_health();
    int get_id();

    void reset();
    void tick_respawn_time();
    int get_respawn_time();
    void set_health(int health);

    void use_item(int x_direction, int y_direction, MapGame& map, bool is_holding);
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

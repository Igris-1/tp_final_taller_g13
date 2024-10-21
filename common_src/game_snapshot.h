#include <vector>
#include <cstdint>
#include <tuple>


// typedef enum{
//     Explosive = 0,
//     Automatic,
//     SemiAutomatic,

// }GunType_t;

// Posicion del pato
typedef struct {
    float x;
    float y;
} Position;

// Estado del pato
typedef struct{
    uint8_t duck_id; // id del color del pato?
    Position pos;
    /*uint8_t duck_hp;
    bool shooting;
    bool running;
    bool jumping;
    bool weapon_equipped;
    bool helmet_equipped;
    bool armor_equipped;
    
    int id_arma;*/ // 1 = pistola / 2 = escopeta
}Duck;

// Objetos en el suelo
typedef struct{
    int id; // id, ejemplo: 1, es cacsco, 2 es escopeta, 3 caja....
    Position pos;
}Item;


// Estado de las balas
typedef struct{
    int bullet_type;
    Position pos;
    std::tuple<int, int> direction;
    // (0, -1) arriba 
    // (0, 1)  abajo
    // (1, 0)  derecha
    // (-1, 0) izq
}Bullet;

typedef struct{
    std::vector <Duck> ducks;
    //std::vector <Bullet> bullets;
    //std::vector <Item> map_items;
} snapshot;



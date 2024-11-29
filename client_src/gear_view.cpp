#include "gear_view.h"

GearView::GearView(Renderer& renderer, std::vector<Texture>& gear_textures,
                   std::vector<Texture>& accessories_textures):
        renderer(renderer),
        gear_textures(gear_textures),
        accessories_textures(accessories_textures) {
    push_gear_frame();
    push_gear_vertical_frame();
}

void GearView::push_gear_frame() {
    // cowboyPistol frames
    gear_frames.push_back(12);
    gear_frames.push_back(-26);
    gear_frames.push_back(0);
    // laserRifle frames
    gear_frames.push_back(-2);
    gear_frames.push_back(-17);
    gear_frames.push_back(-3);
    // ak47 frames
    gear_frames.push_back(1);
    gear_frames.push_back(-19);
    gear_frames.push_back(-1);
    // grenade frames
    gear_frames.push_back(5);
    gear_frames.push_back(-3);
    gear_frames.push_back(0);
    // active grenade frames
    gear_frames.push_back(5);
    gear_frames.push_back(-3);
    gear_frames.push_back(0);
    // magnum frames
    gear_frames.push_back(4);
    gear_frames.push_back(-23);
    gear_frames.push_back(0);
    // oldPistol frames
    gear_frames.push_back(5);
    gear_frames.push_back(-26);
    gear_frames.push_back(-5);
    // pewpewLaser frames
    gear_frames.push_back(0);
    gear_frames.push_back(-15);
    gear_frames.push_back(-3);
    // shotgun frames
    gear_frames.push_back(3);
    gear_frames.push_back(-24);
    gear_frames.push_back(-2);
    // sniper frames
    gear_frames.push_back(5);
    gear_frames.push_back(-16);
    gear_frames.push_back(0);
    // banana frames
    gear_frames.push_back(3);
    gear_frames.push_back(-3);
    gear_frames.push_back(-3);
    // active banana frames
    gear_frames.push_back(-2);
    gear_frames.push_back(-7);
    gear_frames.push_back(-3);
    // helmet frames
    gear_frames.push_back(6);
    gear_frames.push_back(-6);
    gear_frames.push_back(-9);
    // armor frames
    gear_frames.push_back(8);
    gear_frames.push_back(-8);
    gear_frames.push_back(1);
    // helmet accessory frames
    accessories_frames.push_back(1);
    accessories_frames.push_back(-1);
    accessories_frames.push_back(-19);
    // armor accessory frames
    accessories_frames.push_back(11);
    accessories_frames.push_back(-14);
    accessories_frames.push_back(4);
}

void GearView::push_gear_vertical_frame() {
    // cowboyPistol frames
    gear_vertical_frames.push_back(-9);
    gear_vertical_frames.push_back(12);
    gear_vertical_frames.push_back(-5);
    // laserRifle frames
    gear_vertical_frames.push_back(-15);
    gear_vertical_frames.push_back(13);
    gear_vertical_frames.push_back(-9);
    // ak47 frames
    gear_vertical_frames.push_back(-12);
    gear_vertical_frames.push_back(10);
    gear_vertical_frames.push_back(-7);
    // grenade frames
    gear_vertical_frames.push_back(-2);
    gear_vertical_frames.push_back(13);
    gear_vertical_frames.push_back(-4);
    // active grenade frames
    gear_vertical_frames.push_back(-2);
    gear_vertical_frames.push_back(13);
    gear_vertical_frames.push_back(-4);
    // magnum frames
    gear_vertical_frames.push_back(-10);
    gear_vertical_frames.push_back(6);
    gear_vertical_frames.push_back(-10);
    // oldPistol frames
    gear_vertical_frames.push_back(-16);
    gear_vertical_frames.push_back(17);
    gear_vertical_frames.push_back(-13);
    // pewpewLaser frames
    gear_vertical_frames.push_back(-15);
    gear_vertical_frames.push_back(11);
    gear_vertical_frames.push_back(-10);
    // shotgun frames
    gear_vertical_frames.push_back(-12);
    gear_vertical_frames.push_back(8);
    gear_vertical_frames.push_back(-8);
    // sniper frames
    gear_vertical_frames.push_back(-7);
    gear_vertical_frames.push_back(9);
    gear_vertical_frames.push_back(0);
    // banana frames
    gear_vertical_frames.push_back(-4);
    gear_vertical_frames.push_back(15);
    gear_vertical_frames.push_back(-7);
    // active banana frames
    gear_vertical_frames.push_back(-4);
    gear_vertical_frames.push_back(15);
    gear_vertical_frames.push_back(-7);
    // helmet frames
    gear_vertical_frames.push_back(-2);
    gear_vertical_frames.push_back(24);
    gear_vertical_frames.push_back(0);
    // armor frames
    gear_vertical_frames.push_back(0);
    gear_vertical_frames.push_back(12);
    gear_vertical_frames.push_back(0);
    // helmet accessory frames
    accessories_vertical_frames.push_back(4);
    accessories_vertical_frames.push_back(-4);
    accessories_vertical_frames.push_back(-20);
    // armor accessory frames
    accessories_vertical_frames.push_back(11);
    accessories_vertical_frames.push_back(-14);
    accessories_vertical_frames.push_back(4);
}

// dibujar gear en el mapa
void GearView::draw_gear(weapon_DTO& weapon) {
    int gear = weapon.weapon_id - 1;
    int x = weapon.x;
    int y = weapon.y;
    int width = weapon.width;
    int height = weapon.height;
    switch (gear) {
        case 0:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
            break;
        case 3:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
            break;
        case 4:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
            break;
        case 9:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 33, 9}, SDL_Rect{x, y, 36, 18}, 0,
                          NullOpt, 0);
            break;
        case 10:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
            break;
        case 11:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
            break;
        case 12:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
            break;
        case 13:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
            break;
        default:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 8, 32, 16},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
            break;
    }
}
// dibujar gear en las manos del pato
void GearView::draw_gear_in_hands(int x, int y, int gear, int inclination, int facing_direction) {
    switch (gear) {
        case 0:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 22, 11}, SDL_Rect{x, y, 36, 18},
                          inclination, NullOpt, facing_direction);
            break;
        case 3:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16}, SDL_Rect{x, y, 24, 24},
                          inclination, NullOpt, facing_direction);
            break;
        case 4:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16}, SDL_Rect{x, y, 24, 24},
                          inclination, NullOpt, facing_direction);
            break;
        case 9:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 33, 9}, SDL_Rect{x, y, 36, 18},
                          inclination, NullOpt, facing_direction);
            break;
        case 10:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16}, SDL_Rect{x, y, 24, 24},
                          inclination, NullOpt, facing_direction);
            break;
        case 11:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16}, SDL_Rect{x, y, 24, 24},
                          inclination, NullOpt, facing_direction);
            break;
        case 12:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16}, SDL_Rect{x, y, 24, 24},
                          inclination, NullOpt, facing_direction);
            break;
        case 13:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16}, SDL_Rect{x, y, 24, 24},
                          inclination, NullOpt, facing_direction);
            break;
        default:
            renderer.Copy(gear_textures[gear], SDL_Rect{0, 8, 32, 16}, SDL_Rect{x, y, 48, 24},
                          inclination, NullOpt, facing_direction);
            break;
    }
}

void GearView::draw_accessories(duck_DTO duck, bool facing_direction, int inclination, int x, int y,
                                std::vector<int>* a_f) {

    int x_sum_value;
    int x_mult_value;
    int y_sum_value;

    if (duck.helmet_equipped) {
        x_sum_value = (*a_f)[0];
        x_mult_value = (*a_f)[1];
        y_sum_value = (*a_f)[2];
        if (duck.crouching) {
            x_sum_value = accessories_vertical_frames[0];
            x_mult_value = accessories_vertical_frames[1];
            y_sum_value = accessories_vertical_frames[2];
            renderer.Copy(accessories_textures[0], SDL_Rect{8, 10, 16, 16},
                          SDL_Rect{x + x_sum_value + facing_direction * x_mult_value,
                                   y + y_sum_value, 28, 28},
                          0, NullOpt, facing_direction);
        } else if (inclination != 0) {
            renderer.Copy(accessories_textures[0], SDL_Rect{8, 10, 16, 16},
                          SDL_Rect{x + x_sum_value + facing_direction * x_mult_value,
                                   y + y_sum_value, 28, 28},
                          0, NullOpt, facing_direction);
        } else {
            renderer.Copy(accessories_textures[0], SDL_Rect{8, 10, 16, 16},
                          SDL_Rect{x + x_sum_value + facing_direction * x_mult_value,
                                   y + y_sum_value, 32, 32},
                          0, NullOpt, facing_direction);
        }
    }
    if (duck.armor_equipped) {
        x_sum_value = (*a_f)[3];
        x_mult_value = (*a_f)[4];
        y_sum_value = (*a_f)[5];
        renderer.Copy(accessories_textures[1], SDL_Rect{8, 8, 16, 16},
                      SDL_Rect{x + x_sum_value + facing_direction * x_mult_value, y + y_sum_value,
                               24, 24},
                      0, NullOpt, facing_direction);
    }
}

// dibujar gear que tiene un pato
void GearView::draw_held_gear(bool& facing_direction, duck_DTO& duck, int inclination,
                              int x_sum_value, int y_sum_value) {
    int gear = duck.weapon_id - 1;
    int x = duck.x;
    int y = duck.y;
    int x_s;
    int x_m;
    int y_s;
    std::vector<int>* g_f = NULL;
    std::vector<int>* a_f = NULL;

    if (inclination == 0) {
        g_f = &gear_frames;
        a_f = &accessories_frames;
    } else {
        g_f = &gear_vertical_frames;
        a_f = &accessories_vertical_frames;
    }

    draw_accessories(duck, facing_direction, inclination, x + x_sum_value, y + y_sum_value, a_f);

    if (gear >= 0) {
        int x_s = (*g_f)[gear * 3];
        int x_m = (*g_f)[gear * 3 + 1];
        int y_s = (*g_f)[gear * 3 + 2];
        draw_gear_in_hands(x + x_sum_value + x_s + facing_direction * x_m, y + y_sum_value + y_s,
                           gear, inclination, facing_direction);
    }
}

GearView::~GearView() {}
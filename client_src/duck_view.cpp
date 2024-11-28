#include "duck_view.h"

DuckView::DuckView(Renderer& renderer, Texture& duck_sprites, Texture& duck_looking_up_texture, Texture& duck_dead_texture, Texture& wing_sprites, GearView& gear_view):
        renderer(renderer),
        duck_texture(duck_sprites),
        wing_texture(wing_sprites),
        gear_view(gear_view),
        duck_dead_texture(duck_dead_texture),
        duck_looking_up_texture(duck_looking_up_texture),
        facing_direction(false) {

    walk_frames[0] = {32, 0};
    walk_frames[1] = {64, 0};
    walk_frames[2] = {96, 0};
    walk_frames[3] = {128, 0};
    walk_frames[4] = {160, 0};
    walk_frames[5] = {0, 32};

    flying_frames[0] = {32, 32};
    flying_frames[1] = {48, 32};
    flying_frames[2] = {64, 32};
    flying_frames[3] = {80, 32};
    flying_frames[4] = {64, 32};
    flying_frames[5] = {48, 32};


    walk_frame = 0;
    flying_frame = 0;
}

void DuckView::draw_duck(duck_DTO& duck) {
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;

    Texture* current_duck_texture = &duck_texture;

    if (duck.looking_up){
        current_duck_texture = &duck_looking_up_texture;
    }

    if (duck.is_moving_right) {
        facing_direction = false;
    } else if (duck.is_moving_left) {
        facing_direction = true;
    }  // esto despues hay que cambiarlo por un is_moving y facing_direction
    if (!duck.is_alive) {
        draw_dead_duck(duck);
    } else if (duck.jumping) {
        draw_jumping_duck(duck, current_duck_texture);

    } else if (duck.falling) {
        draw_falling_duck(duck, current_duck_texture);

    } else if (duck.is_moving_right ^ duck.is_moving_left) {

        draw_moving_duck(duck, current_duck_texture);

    } else if(duck.crouching){
        draw_crouching_duck(duck, current_duck_texture);
    } else {
        draw_idle_duck(duck, current_duck_texture);
    }
    flying_frame = (flying_frame < 5) ? (flying_frame + 1) : 0;

    walk_frame = (walk_frame < 20) ? (walk_frame + 1) : 0;
}

SDL_Rect DuckView::createDuckRect(int x, int y, int w, int h) {
    return SDL_Rect{x - 16, y - 16, w+32, h+16};
}

void DuckView::draw_dead_duck(duck_DTO& duck) {
    renderer.Copy(duck_dead_texture, SDL_Rect{0, 0, 16, 16},
                  SDL_Rect{duck.x - 16, duck.y - 16, 32, 32}, 0, NullOpt,
                  facing_direction);
}

void DuckView::draw_jumping_duck(duck_DTO& duck, Texture* current_duck_texture) {
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;

    int inclination = 0;

    if(duck.looking_up){
        inclination = -90+ facing_direction * 180;
    }

    renderer.Copy(*current_duck_texture, SDL_Rect{1 * 32, 32, 32, 32},
                  createDuckRect(duck.x, duck.y, duck.width, duck.height), 0, NullOpt,
                  facing_direction);
    gear_view.draw_held_gear(facing_direction, duck);
    if (weapon_id > 0) {
        renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x -6 + facing_direction * 12, duck.y+7, 32, 32}, inclination,    
                      NullOpt, facing_direction);
    } else {
        renderer.Copy(wing_texture, SDL_Rect{16, 16, 16, 16},
                      SDL_Rect{duck.x -6 + facing_direction * 12, duck.y+4, 32, 32}, 0,
                      NullOpt, facing_direction);
    }
}

void DuckView::draw_falling_duck(duck_DTO& duck, Texture* current_duck_texture) {
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;

    renderer.Copy(*current_duck_texture, SDL_Rect{3 * 32, 32, 32, 32},
                  createDuckRect(duck.x, duck.y, duck.width, duck.height), 0, NullOpt,
                  facing_direction);
    gear_view.draw_held_gear(facing_direction, duck);
    if (weapon_id > 0) {
        renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x -6 + facing_direction * 12, duck.y+2, 32, 32},
                      -90 + facing_direction * 180, NullOpt, facing_direction);
    } else {
        renderer.Copy(
                wing_texture,
                SDL_Rect{flying_frames[flying_frame].x, flying_frames[flying_frame].y, 16, 16},
                SDL_Rect{duck.x -4 + facing_direction * 12, duck.y+2, 32, 32}, 0, NullOpt,
                facing_direction);
    }
    renderer.Copy(wing_texture,
                  SDL_Rect{flying_frames[flying_frame].x, flying_frames[flying_frame].y, 16, 16},
                  SDL_Rect{duck.x +6 - facing_direction * 12, duck.y+2, 32, 32}, 0,
                  NullOpt, !facing_direction);
}

void DuckView::draw_moving_duck(duck_DTO& duck, Texture* current_duck_texture) {
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;
    int armor = duck.armor_equipped;
    int helmet = duck.helmet_equipped;
    int inclination = 0;

    if(duck.looking_up){
        inclination = -90+ facing_direction * 180;
    }

    renderer.Copy(*current_duck_texture,
                  SDL_Rect{walk_frames[walk_frame / 4].x, walk_frames[walk_frame / 4].y, 32, 32},
                  createDuckRect(duck.x, duck.y, duck.width, duck.height), 0, NullOpt,
                  facing_direction);
    gear_view.draw_held_gear(facing_direction, duck);
    if (weapon_id > 0) {
        renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x -6 + facing_direction * 12, duck.y+11, 32, 32}, inclination,
                      NullOpt, facing_direction);
    } else {
        renderer.Copy(
                wing_texture,
                SDL_Rect{walk_frames[walk_frame / 4].x, walk_frames[walk_frame / 4].y, 16, 16},
                SDL_Rect{duck.x -6 + facing_direction * 12, duck.y+9, 32, 32}, 0, NullOpt,
                facing_direction);
    } /*if (helmet){
        renderer.Copy(accessories_sprites[0], SDL_Rect{8, 10, 16, 16},
                      SDL_Rect{duck.x - 16 + 12 + facing_direction*10, duck.y-16+7, 32, 32}, 0, NullOpt,
                      facing_direction);
    }*/
}

void DuckView::draw_idle_duck(duck_DTO& duck, Texture* current_duck_texture) {
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;
    int armor = duck.armor_equipped;
    int helmet = duck.helmet_equipped;
    int inclination = 0;

    if(duck.looking_up){
        inclination = -90+ facing_direction * 180;
    }

    renderer.Copy(*current_duck_texture, SDL_Rect{0, 0, 32, 32},
                  createDuckRect(duck.x, duck.y, duck.width, duck.height), 0, NullOpt,
                  facing_direction);
    gear_view.draw_held_gear(facing_direction, duck);
    if (weapon_id > 0) {
        renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x -6 + facing_direction * 12, duck.y+11, 32, 32}, inclination,
                      NullOpt, facing_direction);
        
    } else {
        renderer.Copy(wing_texture, SDL_Rect{0, 0, 16, 16},
                      SDL_Rect{duck.x -6 + facing_direction * 12, duck.y+9, 32, 32}, 0,
                      NullOpt, facing_direction);
    } 
    
}

void DuckView::draw_crouching_duck(duck_DTO& duck, Texture* current_duck_texture){
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;
    int armor = duck.armor_equipped;
    int helmet = duck.helmet_equipped;
    int inclination = 0;

    if(duck.looking_up){
        inclination = -90+ facing_direction * 180;
    }

    renderer.Copy(*current_duck_texture, SDL_Rect{5*32, 32, 32, 32},
                  createDuckRect(duck.x, duck.y-12, 32, 48), 0, NullOpt,
                  facing_direction);
    gear_view.draw_held_gear(facing_direction, duck);
    if (weapon_id > 0) {
        renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x -6 + facing_direction * 12, duck.y+11, 32, 32}, inclination,
                      NullOpt, facing_direction);
    } else {
        renderer.Copy(wing_texture, SDL_Rect{0, 0, 16, 16},
                      SDL_Rect{duck.x -6 + facing_direction * 12, duck.y+9, 32, 32}, 0,
                      NullOpt, facing_direction);
    }
}

DuckView::~DuckView() {}

#include "duck_view.h"

DuckView::DuckView(Renderer& renderer, Texture& duck_sprites, Texture& wing_sprites,
                   std::vector<Texture>& weapon_sprites):
        renderer(renderer),
        duck_texture(duck_sprites),
        wing_texture(wing_sprites),
        weapon_textures(weapon_sprites),
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

    Texture* weapon_texture = nullptr;

    if (weapon_id != 0) {
        weapon_texture = &weapon_textures[weapon_id - 1];
    }

    if (duck.is_moving_right) {
        facing_direction = false;
    } else if (duck.is_moving_left) {
        facing_direction = true;
    }// esto despues hay que cambiarlo por un is_moving y facing_direction 

    if (!duck.is_alive) {
        draw_dead_duck(duck);
    } else if (duck.jumping) {
        draw_jumping_duck(duck, weapon_texture);

    } else if (duck.falling) {
        draw_falling_duck(duck, weapon_texture);

    } else if (duck.is_moving_right ^ duck.is_moving_left) {

        draw_moving_duck(duck, weapon_texture);

    } else {
        draw_idle_duck(duck, weapon_texture);
    }
    flying_frame =
            (flying_frame < 5) ? (flying_frame + 1) : 0;

    walk_frame = (walk_frame < 20) ? (walk_frame + 1) : 0;
}


void DuckView::draw_dead_duck(duck_DTO& duck) {
    Texture dead_duck(renderer, "../assets/sprites/cookedDuck.png");
        renderer.Copy(dead_duck, SDL_Rect{0, 0, 16, 16},
                      SDL_Rect{duck.x, duck.y + 32, duck.width, duck.height - 16}, 0, NullOpt,
                      facing_direction);
}

void DuckView::draw_jumping_duck(duck_DTO& duck, Texture* weapon_texture) {
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;

    renderer.Copy(duck_texture, SDL_Rect{1 * 32, 40, 32, 32},
                      SDL_Rect{duck.x - 16, duck.y, duck.width + 32, duck.height + 16}, 0, NullOpt,
                      facing_direction);
        if (weapon_id == 1) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{duck.x - 16 + 22 - facing_direction*12, duck.y + 15, 36, 18}, 0, NullOpt,
                          facing_direction);
        } else if (weapon_id == 2) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 16 + 12 - facing_direction*7, duck.y, duck.width + 16, duck.width + 16},
                          0, NullOpt, facing_direction);
        } else if (weapon_id > 0) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 16 + 12 - facing_direction*7, duck.y, duck.width + 16, duck.width + 16},
                          0, NullOpt, facing_direction);
        }if (weapon_id > 0){
            renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x - 16 + 10 + facing_direction*12, duck.y + 15, 32, 32}, 0, NullOpt,
                      facing_direction);
        } else {
            renderer.Copy(wing_texture, SDL_Rect{16, 16, 16, 16}, SDL_Rect{duck.x-16+ 10 + facing_direction*12, duck.y+12, 32,
                32}, 0, NullOpt, facing_direction);
        }
}

void DuckView::draw_falling_duck(duck_DTO& duck, Texture* weapon_texture) {
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;

    renderer.Copy(duck_texture, SDL_Rect{3 * 32, 40, 32, 32},
                      SDL_Rect{duck.x - 16, duck.y, duck.width + 32, duck.height + 16}, 0, NullOpt,
                      facing_direction);
        if (weapon_id == 1) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{duck.x - 11  + facing_direction*20, duck.y, 36, 18}, -90+facing_direction*180, NullOpt,
                          facing_direction);
        } else if (weapon_id == 2) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 16  + facing_direction*20, duck.y-10, duck.width + 16, duck.width + 16},
                          -90+facing_direction*180, NullOpt, facing_direction);
        }else if (weapon_id > 0) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 16  + facing_direction*20, duck.y-10, duck.width + 16, duck.width + 16},
                          -90+facing_direction*180, NullOpt, facing_direction);
        
        }if (weapon_id > 0){
            renderer.Copy(wing_texture, 
                SDL_Rect{0, 6 * 8, 16, 16}, 
                SDL_Rect{duck.x - 16 + 10 + facing_direction * 12, duck.y + 10, 32, 32}, -90+facing_direction*180,  NullOpt, facing_direction);

        } else {
            renderer.Copy(wing_texture, SDL_Rect{flying_frames[flying_frame].x, flying_frames[flying_frame].y, 16, 16},
                      SDL_Rect{duck.x - 16 + 12 + facing_direction*12, duck.y + 10, 32, 32}, 0, NullOpt,
                      facing_direction); 
        }
        renderer.Copy(wing_texture, SDL_Rect{flying_frames[flying_frame].x, flying_frames[flying_frame].y , 16, 16},
                      SDL_Rect{duck.x - 16 + 22 - facing_direction*12, duck.y + 10, 32, 32}, 0, NullOpt,
                      !facing_direction);
}

void DuckView::draw_moving_duck(duck_DTO& duck, Texture* weapon_texture) {
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;

    renderer.Copy(duck_texture, SDL_Rect{walk_frames[walk_frame/4].x, walk_frames[walk_frame/4].y, 32, 32},
                      SDL_Rect{duck.x - 16, duck.y, duck.width + 32, duck.height + 16}, 0, NullOpt,
                      facing_direction);
        
        if (weapon_id == 1) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{duck.x - 16 + 22 - facing_direction*12, duck.y + 27, 36, 18}, 0, NullOpt,
                          facing_direction);
        } else if (weapon_id == 2) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 16 + 12 - facing_direction*7, duck.y + 10, duck.width + 16, duck.width + 16},
                          0, NullOpt, facing_direction);
        }else if (weapon_id > 0) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 16 + 12 - facing_direction*7, duck.y + 10, duck.width + 16, duck.width + 16},
                          0, NullOpt, facing_direction);
        }if (weapon_id > 0){
            renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x - 16 + 10 + facing_direction*12, duck.y + 27, 32, 32}, 0, NullOpt,
                      facing_direction);
        } else {
            renderer.Copy(wing_texture, SDL_Rect{walk_frames[walk_frame/4].x, walk_frames[walk_frame/4].y, 16, 16}, SDL_Rect{duck.x-16+ 10 + facing_direction*12, duck.y+25,
                32, 32}, 0, NullOpt, facing_direction);
        }
}

void DuckView::draw_idle_duck(duck_DTO& duck, Texture* weapon_texture){
    int weapon_id = duck.weapon_id;
    int duck_id = duck.duck_id;

    renderer.Copy(duck_texture, SDL_Rect{0, 0, 32, 32},
                SDL_Rect{duck.x - 16, duck.y, duck.width + 32, duck.height + 16}, 0, NullOpt,
                facing_direction);
    
    if (weapon_id == 1) {
        renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 22, 11},
                        SDL_Rect{duck.x - 16 + 22 - facing_direction*12, duck.y + 27, 36, 18}, 0, NullOpt,
                        facing_direction);
    } else if (weapon_id == 2) {
        renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                        SDL_Rect{duck.x - 16 + 12 - facing_direction*7, duck.y + 10, duck.width + 16, duck.width + 16},
                        0, NullOpt, facing_direction);
    }else if (weapon_id > 0) {
        renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                        SDL_Rect{duck.x - 16 + 22 - facing_direction*7, duck.y + 10, duck.width + 16, duck.width + 16},
                        0, NullOpt, facing_direction);
    }if (weapon_id > 0){
        renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                    SDL_Rect{duck.x - 16 + 10 + facing_direction*12, duck.y + 27, 32, 32}, 0, NullOpt,
                    facing_direction);
    } else {
        renderer.Copy(wing_texture, SDL_Rect{0, 0, 16, 16}, SDL_Rect{duck.x-16+ 10 + facing_direction*12, duck.y+25, 32,
            32}, 0, NullOpt, facing_direction);
    }
}

DuckView::~DuckView() {}

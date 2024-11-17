#include "duck_view.h"

DuckView::DuckView(Renderer& renderer, Texture& duck_sprites, Texture& wing_sprites,
                   std::vector<Texture>& weapon_sprites):
        renderer(renderer),
        duck_texture(duck_sprites),
        wing_texture(wing_sprites),
        weapon_textures(weapon_sprites),
        facing_direction(false) {
    walk_animation_frame = 1;
    wing_flying_animation_frame = 2;
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
    }
    if (!duck.is_alive) {
        Texture dead_duck(renderer, "../assets/sprites/cookedDuck.png");
        renderer.Copy(dead_duck, SDL_Rect{0, 0, 16, 16},
                      SDL_Rect{duck.x, duck.y + 32, duck.width, duck.height - 16}, 0, NullOpt,
                      facing_direction);
    } else if (duck.jumping) {
        int ai = 10;
        if (facing_direction) {
            ai = 22;
        }
        int ai2 = 22;
        if (facing_direction) {
            ai2 = 10;
        }

        renderer.Copy(duck_texture, SDL_Rect{1 * 32, 40, 32, 32},
                      SDL_Rect{duck.x - 16, duck.y, duck.width + 32, duck.height + 16}, 0, NullOpt,
                      facing_direction);
        if (weapon_id == 1) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{duck.x - 16 + ai2, duck.y + 15, 36, 18}, 0, NullOpt,
                          facing_direction);
        } else if (weapon_id == 2) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 8 + ai2, duck.y + 8, duck.width + 16, duck.width + 16},
                          0, NullOpt, facing_direction);
        }if (weapon_id > 0){
            renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x - 16 + ai, duck.y + 15, 32, 32}, 0, NullOpt,
                      facing_direction);
        } else {
            renderer.Copy(wing_texture, SDL_Rect{0, 0, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+25, 32,
                32}, 0, NullOpt, facing_direction);
        }

    } else if (duck.falling) {
        int ai = 10;
        if (facing_direction) {
            ai = 22;
        }
        int ai2 = 22;
        if (facing_direction) {
            ai2 = 10;
        }

        renderer.Copy(duck_texture, SDL_Rect{3 * 32, 40, 32, 32},
                      SDL_Rect{duck.x - 16, duck.y, duck.width + 32, duck.height + 16}, 0, NullOpt,
                      facing_direction);
        if (weapon_id == 1) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{duck.x - 16 + ai2, duck.y + 15, 36, 18}, 0, NullOpt,
                          facing_direction);
        } else if (weapon_id == 2) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 8 + ai2, duck.y + 8, duck.width + 16, duck.width + 16},
                          0, NullOpt, facing_direction);
        }
        renderer.Copy(wing_texture, SDL_Rect{wing_flying_animation_frame * 16, 32, 16, 16},
                      SDL_Rect{duck.x - 16 + ai, duck.y + 15, 32, 32}, 0, NullOpt,
                      facing_direction);
        if (weapon_id > 0){
            renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x - 16 + ai, duck.y + 18, 32, 32}, 0, NullOpt,
                      facing_direction);
        } else {
            renderer.Copy(wing_texture, SDL_Rect{0, 0, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+25, 32,
                32}, 0, NullOpt, facing_direction);
        }
        

    } else if (duck.is_moving_right ^ duck.is_moving_left) {
        int ai = 10;
        if (facing_direction) {
            ai = 22;
        }
        int ai2 = 22;
        if (facing_direction) {
            ai2 = 10;
        }
        renderer.Copy(duck_texture, SDL_Rect{walk_animation_frame * 32, 0, 32, 32},
                      SDL_Rect{duck.x - 16, duck.y, duck.width + 32, duck.height + 16}, 0, NullOpt,
                      facing_direction);
        
        if (weapon_id == 1) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{duck.x - 16 + ai2, duck.y + 27, 36, 18}, 0, NullOpt,
                          2);
        } else if (weapon_id == 2) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 8 + ai2, duck.y + 16, duck.width + 16, duck.width + 16},
                          0, NullOpt, facing_direction);
        }
        if (weapon_id > 0){
            renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x - 16 + ai, duck.y + 27, 32, 32}, 0, NullOpt,
                      facing_direction);
        } else {
            renderer.Copy(wing_texture, SDL_Rect{10, 6*8, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+25,
                32, 32}, 0, NullOpt, facing_direction);
        }

    } else {
        renderer.Copy(duck_texture, SDL_Rect{0, 0, 32, 32},
                      SDL_Rect{duck.x - 16, duck.y, duck.width + 32, duck.height + 16}, 0, NullOpt,
                      facing_direction);
        int ai = 10;
        if (facing_direction) {
            ai = 22;
        }
        int ai2 = 22;
        if (facing_direction) {
            ai2 = 10;
        }
        SDL_Rect rect = SDL_Rect{0, 0, 16, 16};
        SDL_Rect duckRect = SDL_Rect{duck.x - 16, duck.y, duck.width + 32, duck.height + 16};
        
        if (weapon_id == 1) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{duck.x - 16 + ai2, duck.y + 27, 36, 18}, 0, NullOpt,
                          facing_direction);
        } else if (weapon_id == 2) {
            renderer.Copy(*weapon_texture, SDL_Rect{0, 0, 32, 32},
                          SDL_Rect{duck.x - 8 + ai2, duck.y + 16, duck.width + 16, duck.width + 16},
                          0, NullOpt, facing_direction);
        }
        if (weapon_id > 0){
            renderer.Copy(wing_texture, SDL_Rect{0, 6 * 8, 16, 16},
                      SDL_Rect{duck.x - 16 + ai, duck.y + 27, 32, 32}, 0, NullOpt,
                      facing_direction);
        } else {
            renderer.Copy(wing_texture, SDL_Rect{0, 0, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+25, 32,
                32}, 0, NullOpt, facing_direction);
        }
        
    }
    wing_flying_animation_frame =
            (wing_flying_animation_frame < 5) ? (wing_flying_animation_frame + 1) : 2;


    walk_animation_frame = (walk_animation_frame < 5) ? (walk_animation_frame + 1) : 1;
}


void DuckView::draw_dead_duck() {}

void DuckView::draw_jumping_duck() {}

void DuckView::draw_falling_duck() {}

void DuckView::draw_moving_duck() {}

DuckView::~DuckView() {}

#include "game_view.h"

#include <iostream>
#include <algorithm>

#include "../common_src/game_snapshot_t.h"
// 835 490
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

GameView::GameView():
        sdl(SDL_INIT_VIDEO),
        window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_WINDOW_SHOWN),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        background_sprites(),
        platform_sprites(),
        duck_sprites(),
        wing_sprites(),
        weapon_sprites(),
        bullet_sprites(),
        duck_views() {
    set_up_game();
}

void GameView::add_map(map_structure_t map) {
    this->map = map;
}

void GameView::draw_scoreboard(score_DTO score) {
    renderer.SetDrawColor(Color(0, 0, 0, 0));
    renderer.FillRect(SDL_Rect{SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2});

    renderer.Copy(duck_sprites[score.first_place_id], SDL_Rect{0, 0, 32, 32},
                      SDL_Rect{SCREEN_WIDTH*3/8, SCREEN_HEIGHT/4+20, 64, 64}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score.first_place_score*8, 8, 8, 8},
                SDL_Rect{SCREEN_WIDTH*5/8, SCREEN_HEIGHT/4+36, 32, 32}, 0, NullOpt, 0);

    renderer.Copy(duck_sprites[score.second_place_id], SDL_Rect{0, 0, 32, 32},
            SDL_Rect{SCREEN_WIDTH*3/8, SCREEN_HEIGHT/4+90, 64, 64}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score.second_place_score*8, 8, 8, 8},
                SDL_Rect{SCREEN_WIDTH*5/8, SCREEN_HEIGHT/4+106, 32, 32}, 0, NullOpt, 0);

    renderer.Copy(duck_sprites[score.third_place_id], SDL_Rect{0, 0, 32, 32},
                      SDL_Rect{SCREEN_WIDTH*3/8, SCREEN_HEIGHT/4+160, 64, 64}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score.third_place_score*8, 8, 8, 8},
                SDL_Rect{SCREEN_WIDTH*5/8, SCREEN_HEIGHT/4+176, 32, 32}, 0, NullOpt, 0);

    renderer.Copy(duck_sprites[score.fourth_place_id], SDL_Rect{0, 0, 32, 32},
                      SDL_Rect{SCREEN_WIDTH*3/8, SCREEN_HEIGHT/4+230, 64, 64}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score.fourth_place_score*8, 8, 8, 8},
                SDL_Rect{SCREEN_WIDTH*5/8, SCREEN_HEIGHT/4+246, 32, 32}, 0, NullOpt, 0);
}

void GameView::load_score(score_DTO score) {
    draw_scoreboard(score);
    SDL_Delay(7000);
    renderer.Present();
}

void GameView::load_endgame_score(score_DTO score) {

    draw_scoreboard(score);
    renderer.Present();
    SDL_Delay(7000);
    window.Hide();
    std::cout << "Termino el juego todo el mundo a casa"  << std::endl;
}

void GameView::set_up_game() {
    background_sprites.push_back(Texture(renderer, "../assets/sprites/game.png"));

    platform_sprites.push_back(Texture(renderer, "../assets/sprites/platform.png"));

    scoreboard_font.push_back(Texture(renderer, "../assets/fonts/moneyFont.png"));

    Texture duck1Texture(renderer, "../assets/sprites/duck.png");

    Texture duck2Texture(renderer, "../assets/sprites/duck.png");
    duck2Texture.SetColorMod(200, 40, 40);

    Texture duck3Texture(renderer, "../assets/sprites/duck.png");
    duck3Texture.SetColorMod(40, 200, 40);

    Texture duck4Texture(renderer, "../assets/sprites/duck.png");
    duck4Texture.SetColorMod(40, 40, 200);

    duck_sprites.push_back(std::move(duck1Texture));
    duck_sprites.push_back(std::move(duck2Texture));
    duck_sprites.push_back(std::move(duck3Texture));
    duck_sprites.push_back(std::move(duck4Texture));

    Texture wing1Texture(renderer, "../assets/sprites/wing.png");

    Texture wing2Texture(renderer, "../assets/sprites/wing.png");
    wing2Texture.SetColorMod(200, 40, 40);

    Texture wing3Texture(renderer, "../assets/sprites/wing.png");
    wing3Texture.SetColorMod(40, 200, 40);

    Texture wing4Texture(renderer, "../assets/sprites/wing.png");
    wing4Texture.SetColorMod(40, 40, 200);

    wing_sprites.push_back(std::move(wing1Texture));
    wing_sprites.push_back(std::move(wing2Texture));
    wing_sprites.push_back(std::move(wing3Texture));
    wing_sprites.push_back(std::move(wing4Texture));

    weapon_sprites.push_back(Texture(renderer, "../assets/sprites/cowboyPistol.png"));
    weapon_sprites.push_back(Texture(renderer, "../assets/sprites/laserRifle.png"));
    bullet_sprites.push_back(Texture(renderer, "../assets/sprites/pistolShell.png"));
    bullet_sprites.push_back(Texture(renderer, "../assets/sprites/laserBeam.png"));

    /*duck_views.resize(gs.ducks.size(), 0);
    wing_views.resize(gs.ducks.size(), 0);
    dir.resize(gs.ducks.size(), 0);*/
}

void GameView::load_game(game_snapshot_t gs) {
    renderer.Clear();

    int duck_views_size = duck_views.size();

    int gs_ducks_size = gs.ducks.size();

    while (duck_views.size() < gs.ducks.size()) {
        for (int i = 0; i < gs.ducks.size(); i++) {
            duck_DTO duck = gs.ducks[i];
            duck_views.emplace_back(renderer, duck_sprites[duck.duck_id],
                                    wing_sprites[duck.duck_id], weapon_sprites);
        }
    }

    /*int x = gs.ducks[0].x;
    int y = gs.ducks[0].y;

    for (int i = 0; i < gs.ducks.size(); i++) {
        duck_DTO duck = gs.ducks[i];
        if (duck.x < x) {
            x = duck.x;
        }
        if (duck.y < y) {
            y = duck.y;
        }
    }

    int x_min = gs.ducks[0].x - 32;
    int y_min = gs.ducks[0].y - 32;
    int x_max = gs.ducks[0].x + 32;
    int y_max = gs.ducks[0].y + 32;

    for (const auto& duck : gs.ducks) {
        x_min = std::min(x_min, duck.x - 32);
        y_min = std::min(y_min, duck.y - 32);
        x_max = std::max(x_max, duck.x + 32);
        y_max = std::max(y_max, duck.y + 32);
    }

    int ducks_width = x_max - x_min;
    int ducks_height = y_max - y_min;

    float scale_factor_x = static_cast<float>(SCREEN_WIDTH) / ducks_width;
    float scale_factor_y = static_cast<float>(SCREEN_HEIGHT) / ducks_height;
    float scale_factor = std::min(scale_factor_x, scale_factor_y);
    scale_factor = std::clamp(scale_factor, 1.0f, 2.0f); 

    /*if (x*+SCREEN_WIDTH*scale_factor>SCREEN_WIDTH){
        x -= x*scale_factor+SCREEN_WIDTH*scale_factor-SCREEN_WIDTH;
    }
    if (y+SCREEN_HEIGHT*scale_factor>SCREEN_HEIGHT){
        y -= y+SCREEN_HEIGHT*scale_factor-SCREEN_HEIGHT;
    }

    
    SDL_Rect viewport = (SDL_Rect) {-x, -y, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderSetViewport(renderer.Get(), &viewport);
    SDL_RenderSetScale(renderer.Get(), scale_factor, scale_factor);*/

    load_map();
    load_ducks(gs);
    load_bullets(gs);
    load_weapons(gs);
    renderer.Present();
}

void GameView::load_weapons(game_snapshot_t gs) {
    for (int i = 0; i < gs.weapons.size(); i++) {
        weapon_DTO weapon = gs.weapons[i];
        int weapon_id = weapon.weapon_id;
        Texture& weaponTexture = weapon_sprites[weapon_id - 1];
        if (weapon_id == 1) {
            renderer.Copy(weaponTexture, SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{weapon.x - 14, weapon.y - 7, 36, 18}, 0, NullOpt, 0);
        } else if (weapon_id == 2) {
            renderer.Copy(
                    weaponTexture, SDL_Rect{0, 0, 32, 32},
                    SDL_Rect{weapon.x - 8, weapon.y - 8, weapon.width + 16, weapon.width + 16}, 0,
                    NullOpt, 0);
        }
    }
}

void GameView::load_bullets(game_snapshot_t gs) {
    for (int i = 0; i < gs.bullets.size(); i++) {
        bullet_DTO bullet = gs.bullets[i];
        int bullet_id = bullet.bullet_id;
        Texture& bulletTexture = bullet_sprites[bullet_id - 1];
        if (bullet_id == 1) {
            renderer.SetDrawColor(Color(143, 142, 137, 0));

            int yellow_x = (bullet.x_direction == 1) ? bullet.x - bullet.width * 4 : bullet.x;

            renderer.Copy(bulletTexture, SDL_Rect{0, 0, 16, 16},
                          SDL_Rect{bullet.x, bullet.y, bullet.width, bullet.height}, 0, NullOpt,
                          bullet.x_direction);
            renderer.FillRect(
                    SDL_Rect{yellow_x, bullet.y + 8, bullet.width * 4, bullet.height / 8});
        } else if (bullet.bullet_id == 2) {
            for (int x = 0; x < 32; x++) {
                if (bullet.x_direction == 1 && bullet.y_direction == 1) {
                    renderer.Copy(bulletTexture, SDL_Rect{0, 0, 1, 8},
                              SDL_Rect{bullet.x - x, bullet.y - x, 1, 8}, 0, NullOpt,
                              bullet.x_direction);
                    
                } else if (bullet.x_direction != 1 && bullet.y_direction != 1) {
                    renderer.Copy(bulletTexture, SDL_Rect{0, 0, 1, 8},
                              SDL_Rect{bullet.x +x, bullet.y +x , 1, 8}, 0, NullOpt,
                              bullet.x_direction);
                } else if (bullet.x_direction == 1 && bullet.y_direction != 1){
                    renderer.Copy(bulletTexture, SDL_Rect{0, 0, 1, 8},
                              SDL_Rect{bullet.x -x, bullet.y +x , 1, 8}, 0, NullOpt,
                              bullet.x_direction);

                } else if (bullet.x_direction != 1 && bullet.y_direction == 1){
                    renderer.Copy(bulletTexture, SDL_Rect{0, 0, 1, 8},
                              SDL_Rect{bullet.x +x, bullet.y -x, 1, 8}, 0, NullOpt,
                              bullet.x_direction);
                }

                
            }
        }
    }
}

void GameView::load_map() {
    Texture& backgroundTexture = background_sprites[0];
    renderer.Copy(backgroundTexture, SDL_Rect{0, 0, 2425, 1451},
                  SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

    for (int i = 0; i < map.platforms_len; i++) {
        platform_DTO platform = map.platforms[i];
        renderer.Copy(platform_sprites[0], SDL_Rect{0, 11 * 7, 16, 8},
                      SDL_Rect{platform.x, platform.y, platform.width, platform.height});
    }
}

void GameView::load_ducks(game_snapshot_t gs) {
    for (int i = 0; i < gs.ducks.size(); i++) {
        duck_DTO duck = gs.ducks[i];

        duck_views[i].draw_duck(duck);
    }
}


// Función auxiliar para calcular la distancia entre dos patos
float calculateDistance(const duck_DTO duck1, const duck_DTO duck2) {
    return std::sqrt(std::pow(duck2.x - duck1.x, 2) + std::pow(duck2.y - duck1.y, 2));
}


GameView::~GameView() {}
#include "game_view.h"

#include <algorithm>
#include <iostream>
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768
#define DELAY_AFTER_SCORE 7000

GameView::GameView():
        sdl(SDL_INIT_VIDEO),
        window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_WINDOW_SHOWN),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        background_sprites(),
        platform_sprites(),
        duck_sprites(),
        wing_sprites(),
        gear_sprites(),
        bullet_sprites(),
        duck_views(),
        gear_view(renderer, gear_sprites, accessories_sprites) {
    set_up_game();
}

void GameView::add_map(map_structure_t map) { this->map = map; }

void GameView::render_scoreboard(score_DTO score) {
    renderer.SetDrawColor(Color(0, 0, 0, 0));
    renderer.FillRect(
            SDL_Rect{SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

    renderer.Copy(scoreboard_font[1], SDL_Rect{0, 0, 218, 109},
                  SDL_Rect{SCREEN_WIDTH * 7 / 16, SCREEN_HEIGHT / 4, 218, 109}, 0, NullOpt, 0);

    renderer.Copy(duck_sprites[score.first_place_id], SDL_Rect{0, 0, 32, 32},
                  SDL_Rect{SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT / 3 + 30, 64, 64}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score.first_place_score * 8, 8, 8, 8},
                  SDL_Rect{SCREEN_WIDTH * 5 / 8, SCREEN_HEIGHT / 3 + 56, 32, 32}, 0, NullOpt, 0);

    renderer.Copy(duck_sprites[score.second_place_id], SDL_Rect{0, 0, 32, 32},
                  SDL_Rect{SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT / 3 + 100, 64, 64}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score.second_place_score * 8, 8, 8, 8},
                  SDL_Rect{SCREEN_WIDTH * 5 / 8, SCREEN_HEIGHT / 3 + 126, 32, 32}, 0, NullOpt, 0);

    renderer.Copy(duck_sprites[score.third_place_id], SDL_Rect{0, 0, 32, 32},
                  SDL_Rect{SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT / 3 + 170, 64, 64}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score.third_place_score * 8, 8, 8, 8},
                  SDL_Rect{SCREEN_WIDTH * 5 / 8, SCREEN_HEIGHT / 3 + 196, 32, 32}, 0, NullOpt, 0);

    renderer.Copy(duck_sprites[score.fourth_place_id], SDL_Rect{0, 0, 32, 32},
                  SDL_Rect{SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT / 3 + 240, 64, 64}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score.fourth_place_score * 8, 8, 8, 8},
                  SDL_Rect{SCREEN_WIDTH * 5 / 8, SCREEN_HEIGHT / 3 + 266, 32, 32}, 0, NullOpt, 0);
}

void GameView::render_score(score_DTO score) {
    render_scoreboard(score);
    renderer.Present();
    SDL_Delay(DELAY_AFTER_SCORE);
}

void GameView::render_endgame_score(score_DTO score) {

    render_scoreboard(score);
    renderer.Present();
    SDL_Delay(DELAY_AFTER_SCORE);
    window.Hide();
    Mix_CloseAudio();
}

void GameView::show_loading_screen(){
    Texture loging_image(renderer, "../assets/sprites/loading_screen.png");

    renderer.Copy(loging_image, SDL_Rect{0, 0, 1280, 720},
                  SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});

    renderer.Present();
}

void GameView::load_map_textures(){
    background_sprites.push_back(Texture(renderer, "../assets/sprites/game.png"));

    platform_sprites.push_back(Texture(renderer, "../assets/sprites/platform.png"));

    scoreboard_font.push_back(Texture(renderer, "../assets/fonts/moneyFont.png"));

    scoreboard_font.push_back(Texture(renderer, "../assets/fonts/duck_game_title.png"));

    box_sprites.push_back(Texture(renderer, "../assets/sprites/itemBox.png"));
}

void GameView::load_gear_textures(){
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/cowboyPistol.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/laserRifle.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/ak47.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/grenade.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/activeGrenade.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/magnum.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/oldPistol.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/pewpewLaser.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/shotgun.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/sniper.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/banana.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/activeBanana.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/helmetPickup.png"));
    gear_sprites.push_back(Texture(renderer, "../assets/sprites/armorPickup.png"));

    bullet_sprites.push_back(Texture(renderer, "../assets/sprites/pistolShell.png"));
    bullet_sprites.push_back(Texture(renderer, "../assets/sprites/laserBeam.png"));
    bullet_sprites.push_back(Texture(renderer, "../assets/sprites/shotgunShell.png"));
    bullet_sprites.push_back(Texture(renderer, "../assets/sprites/explosion.png"));
    bullet_sprites.push_back(Texture(renderer, "../assets/sprites/magnumShell.png"));

    accessories_sprites.push_back(Texture(renderer, "../assets/sprites/helmet.png"));
    accessories_sprites.push_back(Texture(renderer, "../assets/sprites/armor.png"));
}

void GameView::load_duck_textures(){
    Texture duck1Texture(renderer, "../assets/sprites/duck.png");

    Texture duck2Texture(renderer, "../assets/sprites/duck.png");
    duck2Texture.SetColorMod(200, 40, 40);

    Texture duck3Texture(renderer, "../assets/sprites/duck.png");
    duck3Texture.SetColorMod(40, 200, 40);

    Texture duck4Texture(renderer, "../assets/sprites/duck.png");
    duck4Texture.SetColorMod(40, 40, 200);

    Texture duck1TextureUp(renderer, "../assets/sprites/duckUp.png");

    Texture duck2TextureUp(renderer, "../assets/sprites/duckUp.png");
    duck2TextureUp.SetColorMod(200, 40, 40);

    Texture duck3TextureUp(renderer, "../assets/sprites/duckUp.png");
    duck3TextureUp.SetColorMod(40, 200, 40);

    Texture duck4TextureUp(renderer, "../assets/sprites/duckUp.png");
    duck4TextureUp.SetColorMod(40, 40, 200);

    duck_sprites.push_back(std::move(duck1Texture));
    duck_sprites.push_back(std::move(duck2Texture));
    duck_sprites.push_back(std::move(duck3Texture));
    duck_sprites.push_back(std::move(duck4Texture));

    duck_looking_up_sprites.push_back(std::move(duck1TextureUp));
    duck_looking_up_sprites.push_back(std::move(duck2TextureUp));
    duck_looking_up_sprites.push_back(std::move(duck3TextureUp));
    duck_looking_up_sprites.push_back(std::move(duck4TextureUp));

    Texture dead_duck(renderer, "../assets/sprites/cookedDuck.png");
    dead_duck_sprites.push_back(std::move(dead_duck));

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
}

void GameView::load_music(){
    int a = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (a < 0) {
        std::cout << "Error al abrir audio" << std::endl;
    }

    Mix_Music* efecto = Mix_LoadMUS("../assets/music/arcade.mp3");

    if (efecto == NULL) {
        std::cout << "Error al cargar musica" << std::endl;
    }
    Mix_VolumeMusic(40);
    Mix_PlayMusic(efecto, -1);

    if (TTF_Init() == -1) {
        std::cout << "Error al iniciar TTF" << std::endl;
    }
}

void GameView::set_up_game() {
    
    load_duck_textures();
    load_gear_textures();
    load_map_textures();
    load_music();

    show_loading_screen();
}

void GameView::render_game(game_snapshot_t gs) {
    renderer.Clear();

    add_ducks(gs);  // esto carga las duck views de cada pato y deberia estar al principio, y no siempre. Despues hay que cambiarlo

    //zoom(gs);
    render_map();
    render_boxes(gs);
    render_ducks(gs);
    render_bullets(gs);
    render_weapons(gs);
    
    renderer.Present();
}

void GameView::add_ducks(game_snapshot_t gs) {
    int duck_views_size = duck_views.size();

    int gs_ducks_size = gs.ducks.size();

    while (duck_views.size() < gs.ducks.size()) {
        for (int i = 0; i < gs.ducks.size(); i++) {

            int duck_id = static_cast<int>(gs.ducks[i].duck_id);

            duck_DTO duck = gs.ducks[i];
            duck_views.emplace_back(renderer, duck_sprites[duck_id], duck_looking_up_sprites[duck_id], dead_duck_sprites[0], wing_sprites[duck_id], gear_view);
        }
    }
}

void GameView::zoom(game_snapshot_t gs) {
    int x = gs.ducks[0].x;
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

    for (const auto& duck: gs.ducks) {
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
    }*/


    SDL_Rect viewport = (SDL_Rect){-x, -y, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderSetViewport(renderer.Get(), &viewport);
    SDL_RenderSetScale(renderer.Get(), scale_factor, scale_factor);
}

void GameView::render_boxes(game_snapshot_t gs) {
    for (int i = 0; i < gs.boxes.size(); i++) {
        box_DTO box = gs.boxes[i];
        renderer.Copy(box_sprites[0], SDL_Rect{0, 16, 16, 16},
                      SDL_Rect{box.x, box.y, box.width, box.height});
    }
}

void GameView::render_weapons(game_snapshot_t gs) {
    for (int i = 0; i < gs.weapons.size(); i++) {
        weapon_DTO weapon = gs.weapons[i];
        gear_view.draw_gear(weapon);
    }
}

void GameView::render_bullets(game_snapshot_t gs) {
    for (int i = 0; i < gs.bullets.size(); i++) {
        bullet_DTO bullet = gs.bullets[i];
        int bullet_id = bullet.bullet_id;
        Texture& bulletTexture = bullet_sprites[bullet_id - 1];
        if (bullet_id == 1) {
            renderer.Copy(bulletTexture, SDL_Rect{6, 6, 6, 3},
                          SDL_Rect{bullet.x, bullet.y, bullet.width, bullet.height}, 0, NullOpt,
                          bullet.x_direction);
        } else if (bullet.bullet_id == 2) {
            for (int b_pos = 0; b_pos < 32; b_pos++) {
                int dir_x = -bullet.x_direction;
                int dir_y = -bullet.y_direction;
                int angle = 0;
                if (dir_x == 0) {
                    angle = -90;
                }

                renderer.Copy(bulletTexture, SDL_Rect{0, 0, 1, 8},
                                  SDL_Rect{bullet.x - dir_x*b_pos, bullet.y - dir_y*b_pos, 1, 8}, angle, NullOpt,
                                  bullet.x_direction);
            }
        } else if (bullet_id == 3) {
            renderer.Copy(bulletTexture, SDL_Rect{5, 7, 6, 3},
                          SDL_Rect{bullet.x, bullet.y, bullet.width, bullet.height}, 0, NullOpt,
                          bullet.x_direction);
        } else if (bullet_id == 4) {
            renderer.Copy(bulletTexture, SDL_Rect{25*8, 2*8, 32, 32},
                          SDL_Rect{bullet.x, bullet.y, bullet.width, bullet.height}, 0, NullOpt,
                          bullet.x_direction);
        }
    }
}

void GameView::render_map() {
    Texture& backgroundTexture = background_sprites[0];
    renderer.Copy(backgroundTexture, SDL_Rect{0, 0, 2425, 1451},
                  SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
    for (int i = 0; i < map.platforms_len; i++) {
        platform_DTO platform = map.platforms[i];
        renderer.Copy(platform_sprites[0], SDL_Rect{0, 10 * 8, 16, 8},
                      SDL_Rect{platform.x, platform.y, platform.width , platform.height});
    }
}

void GameView::render_ducks(game_snapshot_t gs) {
    for (int i = 0; i < gs.ducks.size(); i++) {
        duck_DTO duck = gs.ducks[i];
        duck_views[i].draw_duck(duck);
    }
}

GameView::~GameView() {}
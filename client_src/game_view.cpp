#include "game_view.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#define DELAY_AFTER_SCORE 7000
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

GameView::GameView():
        sdl(SDL_INIT_VIDEO), 
        w_width(SCREEN_WIDTH),
        w_height(SCREEN_HEIGHT),
        window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        gear_view(renderer, gear_sprites, accessories_sprites) {
    set_up_game();
}

void GameView::add_map(map_structure_t map){
    this->map = map;
    w_width = map.width;
    w_height = map.height;
    window.SetSize(w_width, w_height);
    Mix_VolumeMusic(5);
    Mix_PlayMusic(background_music[random_number(0, background_music.size() - 1)], -1);
}

void GameView::render_scoreboard(score_DTO score) {
    SDL_RenderSetScale(renderer.Get(), 1.0f, 1.0f);
    SDL_RenderSetViewport(renderer.Get(), nullptr);

    renderer.SetDrawColor(Color(0, 0, 0, 0));
    renderer.FillRect(
            SDL_Rect{w_width / 4, w_height / 4, w_width / 2, w_height / 2});

    renderer.Copy(scoreboard_font[1], SDL_Rect{0, 0, 218, 109},
                  SDL_Rect{w_width * 7 / 16, w_height / 4, 218, 109}, 0, NullOpt, 0);

    int score_1 = score.first_place_score%10;
    int score_10 = score.first_place_score/10;

    renderer.Copy(duck_sprites[score.first_place_id], SDL_Rect{0, 0, 32, 32},
                  SDL_Rect{w_width * 3 / 8, w_height / 3 + 30, 64, 64}, 0, NullOpt, 0);
    
    renderer.Copy(scoreboard_font[0], SDL_Rect{score_10 * 8, 8, 8, 8},
                  SDL_Rect{w_width * 5 / 8 - 33, w_height / 3 + 56, 32, 32}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score_1 * 8, 8, 8, 8},
                  SDL_Rect{w_width * 5 / 8, w_height / 3 + 56, 32, 32}, 0, NullOpt, 0);

    score_1 = score.second_place_score%10;
    score_10 = score.second_place_score/10;

    renderer.Copy(duck_sprites[score.second_place_id], SDL_Rect{0, 0, 32, 32},
                  SDL_Rect{w_width * 3 / 8, w_height / 3 + 100, 64, 64}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score_1 * 8, 8, 8, 8},
                  SDL_Rect{w_width * 5 / 8, w_height / 3 + 126, 32, 32}, 0, NullOpt, 0);

    renderer.Copy(scoreboard_font[0], SDL_Rect{score_10 * 8, 8, 8, 8},
                  SDL_Rect{w_width * 5 / 8 - 33, w_height / 3 + 126, 32, 32}, 0, NullOpt, 0);

    if(score.amount_of_ducks > 2){

        score_1 = score.third_place_score%10;
        score_10 = score.third_place_score/10;
        renderer.Copy(duck_sprites[score.third_place_id], SDL_Rect{0, 0, 32, 32},
                    SDL_Rect{w_width * 3 / 8, w_height / 3 + 170, 64, 64}, 0, NullOpt, 0);

        renderer.Copy(scoreboard_font[0], SDL_Rect{score_1 * 8, 8, 8, 8},
                    SDL_Rect{w_width * 5 / 8, w_height / 3 + 196, 32, 32}, 0, NullOpt, 0);

        renderer.Copy(scoreboard_font[0], SDL_Rect{score_10 * 8, 8, 8, 8},
                    SDL_Rect{w_width * 5 / 8-33, w_height / 3 + 196, 32, 32}, 0, NullOpt, 0);
        if(score.amount_of_ducks > 3){

            score_1 = score.fourth_place_score%10;
            score_10 = score.fourth_place_score/10;

            renderer.Copy(duck_sprites[score.fourth_place_id], SDL_Rect{0, 0, 32, 32},
                        SDL_Rect{w_width * 3 / 8, w_height / 3 + 240, 64, 64}, 0, NullOpt, 0);

            renderer.Copy(scoreboard_font[0], SDL_Rect{score_1 * 8, 8, 8, 8},
                        SDL_Rect{w_width * 5 / 8, w_height / 3 + 266, 32, 32}, 0, NullOpt, 0);

            renderer.Copy(scoreboard_font[0], SDL_Rect{score_10* 8, 8, 8, 8},
                        SDL_Rect{w_width * 5 / 8-33, w_height / 3 + 266, 32, 32}, 0, NullOpt, 0);
        }
    }
}

void GameView::render_score(score_DTO score) {
    render_scoreboard(score);
    renderer.Present();
}

void GameView::render_endgame_score(score_DTO score) {

    render_scoreboard(score);
    renderer.Present();
    SDL_Delay(DELAY_AFTER_SCORE);
    window.Hide();
    Mix_CloseAudio();
}

void GameView::load_map_textures() {
    background_sprites.push_back(Texture(renderer, "../assets/sprites/game.png"));

    platform_sprites.push_back(Texture(renderer, "../assets/sprites/one_block.png"));
    platform_sprites.push_back(Texture(renderer, "../assets/sprites/horizontal_wood.png"));
    platform_sprites.push_back(Texture(renderer, "../assets/sprites/vertical_wood.png"));
    platform_sprites.push_back(Texture(renderer, "../assets/sprites/gunSpawner.png"));

    scoreboard_font.push_back(Texture(renderer, "../assets/fonts/moneyFont.png"));

    scoreboard_font.push_back(Texture(renderer, "../assets/fonts/duck_game_title.png"));

    box_sprites.push_back(Texture(renderer, "../assets/sprites/itemBox.png"));
}

void GameView::load_gear_textures() {
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

void GameView::load_duck_textures() {
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

void GameView::load_music() {
    int a = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    background_music.push_back(Mix_LoadMUS("../assets/music/arcade.mp3"));
    background_music.push_back(Mix_LoadMUS("../assets/music/fight.mp3"));
    background_music.push_back(Mix_LoadMUS("../assets/music/hypeUp.mp3"));
    background_music.push_back(Mix_LoadMUS("../assets/music/funkyDuck.mp3"));

    dead_duck_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/AAA.wav"));
    dead_duck_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/AUU.wav"));
    //dead_duck_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/my_leg.wav"));

    struck_duck_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/oof.wav"));

    weapon_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/smallWeapon.wav"));
    weapon_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/bigWeapon.wav"));
    weapon_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/laser.wav"));
    weapon_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/explotion.wav"));

    slipping_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/slipping.wav"));
    slipping_sound_effects.push_back(Mix_LoadWAV("../assets/music/sounds/slipping2.wav"));
}

int GameView::random_number(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distrib(min, max);

    return distrib(gen);
}

void GameView::make_noise(game_snapshot_t gs) {


    if (gs.sounds.death) {
        int channel = Mix_PlayChannel(
                -1, dead_duck_sound_effects[random_number(0, dead_duck_sound_effects.size() - 1)],
                0);
        Mix_Volume(channel, 30);
    }

    if (gs.sounds.duck_struck){
        int channel = Mix_PlayChannel(
                -1, struck_duck_sound_effects[random_number(0, struck_duck_sound_effects.size() - 1)],
                0);
        Mix_Volume(channel, 30);
    }

    if (gs.sounds.shooting_small_weapon) {
        int channel = Mix_PlayChannel(-1, weapon_sound_effects[0], 0);
        Mix_Volume(channel, 30);
    }

    if (gs.sounds.shooting_big_weapon) {
        int channel = Mix_PlayChannel(-1, weapon_sound_effects[1], 0);
        Mix_Volume(channel, 30);
    }

    if (gs.sounds.shooting_laser_weapon) {
        int channel = Mix_PlayChannel(-1, weapon_sound_effects[2], 0);
        Mix_Volume(channel, 30);
    }

    if (gs.sounds.explotion) {
        int channel = Mix_PlayChannel(-1, weapon_sound_effects[3], 0);
        Mix_Volume(channel, 30);
    }

    if (gs.sounds.duck_sliding) {
        int channel = Mix_PlayChannel(
                -1, slipping_sound_effects[random_number(0, slipping_sound_effects.size() - 1)], 0);
        Mix_Volume(channel, 30);
    }
}

void GameView::set_up_game() {
    load_duck_textures();
    load_gear_textures();
    load_map_textures();
    load_music();

    show_loading_screen();

}

void GameView::show_loading_screen() {
    Texture loging_image(renderer, "../assets/sprites/loading_screen.png");

    renderer.Copy(loging_image, SDL_Rect{0, 0, 1280, 720},
                  SDL_Rect{0, 0, w_width, w_height});

    //Mix_VolumeMusic(5);
    //Mix_PlayMusic(, -1);
    renderer.Present();
}

void GameView::render_game(game_snapshot_t gs) {
    renderer.Clear();

    add_ducks(gs); 

    zoom(gs);

    render_map();
    render_boxes(gs);
    render_ducks(gs);
    render_bullets(gs);
    render_weapons(gs);

    make_noise(gs);

    renderer.Present();
}

void GameView::add_ducks(game_snapshot_t gs) {
    int duck_views_size = duck_views.size();

    int gs_ducks_size = gs.ducks.size();

    while (duck_views.size() < gs.ducks.size()) {
        for (int i = 0; i < gs.ducks.size(); i++) {

            int duck_id = static_cast<int>(gs.ducks[i].duck_id);

            duck_DTO duck = gs.ducks[i];
            duck_views.emplace_back(renderer, duck_sprites[duck_id],
                                    duck_looking_up_sprites[duck_id], dead_duck_sprites[0],
                                    wing_sprites[duck_id], gear_view);
        }
    }
}

void GameView::zoom(game_snapshot_t gs) {
    int min_x = gs.ducks[0].x;
    int max_x = gs.ducks[0].x;
    int min_y = gs.ducks[0].y;
    int max_y = gs.ducks[0].y;

    for (int i = 0; i < gs.ducks.size(); i++) {
        duck_DTO duck = gs.ducks[i];
        min_x = std::min(min_x, static_cast<int>(duck.x));
        max_x = std::max(max_x, static_cast<int>(duck.x));
        min_y = std::min(min_y, static_cast<int>(duck.y));
        max_y = std::max(max_y, static_cast<int>(duck.y));
    }

    const float margin = 150.0f;

    min_x -= margin;
    max_x += margin;
    min_y -= margin;
    max_y += margin;

    float visible_width = max_x - min_x;
    float visible_height = max_y - min_y;

    float zoom_factor = std::min(w_width / visible_width, w_height / visible_height);

    const float max_zoom = 2.0f;
    const float min_zoom = 1.0f;
    zoom_factor = std::clamp(zoom_factor, min_zoom, max_zoom);

    float cam_x = (min_x + max_x) / 2.0f - (w_width / (2 * zoom_factor));
    float cam_y = (min_y + max_y) / 2.0f - (w_height / (2 * zoom_factor));

    const float world_width = static_cast<float>(w_width);
    const float world_height = static_cast<float>(w_height);

    float max_cam_x = world_width - (w_width / zoom_factor);
    float max_cam_y = world_height - (w_height / zoom_factor);

    if (cam_x < 0) {
        cam_x = 0;
    } else if (cam_x > max_cam_x) {
        cam_x = max_cam_x;
    }

    if (cam_y < 0) {
        cam_y = 0;
    } else if (cam_y > max_cam_y) {
        cam_y = max_cam_y;
    }

    SDL_RenderSetScale(renderer.Get(), zoom_factor, zoom_factor);
    SDL_Rect viewport = {static_cast<int>(-cam_x), static_cast<int>(-cam_y), w_width, w_height};
    SDL_RenderSetViewport(renderer.Get(), &viewport);
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
                              SDL_Rect{bullet.x - dir_x * b_pos, bullet.y - dir_y * b_pos, 1, 8},
                              angle, NullOpt, bullet.x_direction);
            }
        } else if (bullet_id == 3) {
            renderer.Copy(bulletTexture, SDL_Rect{5, 7, 6, 3},
                          SDL_Rect{bullet.x, bullet.y, bullet.width, bullet.height}, 0, NullOpt,
                          bullet.x_direction);
        } else if (bullet_id == 4) {
            renderer.Copy(bulletTexture, SDL_Rect{25 * 8, 2 * 8, 32, 32},
                          SDL_Rect{bullet.x, bullet.y, bullet.width, bullet.height}, 0, NullOpt,
                          bullet.x_direction);
        }
    }
}

void GameView::render_map() {
    Texture& backgroundTexture = background_sprites[0];
    renderer.Copy(backgroundTexture, SDL_Rect{0, 0, 2425, 1451},
                  SDL_Rect{0, 0, w_width, w_height});
    for (int i = 0; i < map.platforms_len; i++) {
        platform_DTO platform = map.platforms[i];
        if (platform.height>platform.width){
            renderer.Copy(platform_sprites[2], SDL_Rect{0, 0, 69, 238},
                      SDL_Rect{platform.x, platform.y, platform.width, platform.height});
        } else if (platform.height<platform.width){
            renderer.Copy(platform_sprites[1], SDL_Rect{0, 0, 238, 69},
                      SDL_Rect{platform.x, platform.y, platform.width, platform.height});
        } else {
            renderer.Copy(platform_sprites[0], SDL_Rect{0, 0, 109, 109},
                      SDL_Rect{platform.x, platform.y, platform.width, platform.height});
        }
    }
    for (int i = 0; i < map.spawns_platforms_len; i++) {
        platform_DTO platform = map.spawns_platforms[i];
        renderer.Copy(platform_sprites[3], SDL_Rect{0, 0, 14, 6},
                      SDL_Rect{platform.x, platform.y, platform.width, platform.height});
    }
}

void GameView::render_ducks(game_snapshot_t gs) {
    for (int i = 0; i < gs.ducks.size(); i++) {
        duck_DTO duck = gs.ducks[i];
        duck_views[i].draw_duck(duck);
    }
}

GameView::~GameView() {
}

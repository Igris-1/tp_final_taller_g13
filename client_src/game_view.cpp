#include "game_view.h"

#include <iostream>

#include "../common_src/game_snapshot_t.h"

#define SCREEN_WIDTH 820
#define SCREEN_HEIGHT 500

GameView::GameView(map_structure_t map):
        map(map),
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

void GameView::set_up_game() {
    background_sprites.push_back(Texture(renderer, "../assets/game_assets/game.png"));

    platform_sprites.push_back(Texture(renderer, "../assets/game_assets/platform.png"));

    Texture duck1Texture(renderer, "../assets/game_assets/duck.png");

    Texture duck2Texture(renderer, "../assets/game_assets/duck.png");
    duck2Texture.SetColorMod(200, 40, 40);

    Texture duck3Texture(renderer, "../assets/game_assets/duck.png");
    duck3Texture.SetColorMod(40, 200, 40);

    Texture duck4Texture(renderer, "../assets/game_assets/duck.png");
    duck4Texture.SetColorMod(40, 40, 200);

    duck_sprites.push_back(std::move(duck1Texture));
    duck_sprites.push_back(std::move(duck2Texture));
    duck_sprites.push_back(std::move(duck3Texture));
    duck_sprites.push_back(std::move(duck4Texture));

    Texture wing1Texture(renderer, "../assets/game_assets/wing.png");

    Texture wing2Texture(renderer, "../assets/game_assets/wing.png");
    wing2Texture.SetColorMod(200, 40, 40);

    Texture wing3Texture(renderer, "../assets/game_assets/wing.png");
    wing3Texture.SetColorMod(40, 200, 40);

    Texture wing4Texture(renderer, "../assets/game_assets/wing.png");
    wing4Texture.SetColorMod(40, 40, 200);

    wing_sprites.push_back(std::move(wing1Texture));
    wing_sprites.push_back(std::move(wing2Texture));
    wing_sprites.push_back(std::move(wing3Texture));
    wing_sprites.push_back(std::move(wing4Texture));

    weapon_sprites.push_back(Texture(renderer, "../assets/game_assets/cowboyPistol.png"));
    weapon_sprites.push_back(Texture(renderer, "../assets/game_assets/laserRifle.png"));
    bullet_sprites.push_back(Texture(renderer, "../assets/game_assets/pistolShell.png"));
    bullet_sprites.push_back(Texture(renderer, "../assets/game_assets/laserBeam.png"));

    SDL_QueryTexture(Texture(renderer, "../assets/game_assets/game.png").Get(), nullptr, nullptr,
                     &bgWidth, &bgHeight);
    float bgAspectRatio = static_cast<float>(bgWidth) / static_cast<float>(bgHeight);
    bgScaledWidth = SCREEN_WIDTH;
    bgScaledHeight = static_cast<int>(SCREEN_WIDTH / bgAspectRatio);
    bgScaledWidth = static_cast<int>(SCREEN_HEIGHT * bgAspectRatio);

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

    std::pair<duck_DTO, duck_DTO> mostDistantDucks = findMostDistantDucks(gs.ducks);
    std::cout << "Ducks: " << mostDistantDucks.first.x << mostDistantDucks.first.x << std::endl;
    std::cout << "Ducks: " << mostDistantDucks.second.x << mostDistantDucks.second.x << std::endl;


    // float scale_factor = 1; // el valor debe estar entre 1 y 2
    // int window_dimension = SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT; // el
    // menor de los dos int scaled_window_dimension = window_dimension * scale_factor; int cutoff =
    // scaled_window_dimension - window_dimension; SDL_Rect viewport = (SDL_Rect) {0 - cutoff / 2, 0
    // - cutoff / 2, scaled_window_dimension, scaled_window_dimension};
    // SDL_RenderSetScale(renderer.Get(), scale_factor, scale_factor);
    // SDL_RenderSetViewport(renderer.Get(), &viewport);


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
            for (int x = 0; x < 16; x++) {
                renderer.Copy(bulletTexture, SDL_Rect{0, 0, 1, 8},
                              SDL_Rect{bullet.x - x, bullet.y - x, 1, bullet.height}, 0, NullOpt,
                              bullet.x_direction);
            }
        }
    }
}

void GameView::load_map() {
    Texture& backgroundTexture = background_sprites[0];
    renderer.Copy(backgroundTexture, SDL_Rect{0, 0, bgWidth, bgHeight},
                  SDL_Rect{0, 0, bgScaledWidth, bgScaledHeight});

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

// Función para encontrar los dos patos más alejados
std::pair<duck_DTO, duck_DTO> GameView::findMostDistantDucks(std::vector<duck_DTO> ducks) {
    if (ducks.size() < 2) {
        // devolver los dos patos
        return {ducks[0], ducks[1]};
    }

    float maxDistance = 0.0f;
    std::pair<duck_DTO, duck_DTO> mostDistantPair;

    // Recorre todas las combinaciones de patos para encontrar los más alejados
    for (size_t i = 0; i < ducks.size(); ++i) {
        for (size_t j = i + 1; j < ducks.size(); ++j) {
            float distance = calculateDistance(ducks[i], ducks[j]);
            if (distance > maxDistance) {
                maxDistance = distance;
                mostDistantPair = {ducks[i], ducks[j]};
            }
        }
    }

    return mostDistantPair;
}

GameView::~GameView() {}
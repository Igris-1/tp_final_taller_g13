#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>

#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"

#include "duck_view.h"

using namespace SDL2pp;


class GameView {
private:
    map_structure_t map;
    SDL sdl;
    Window window;
    Renderer renderer;
    std::vector<Texture> background_sprites;
    std::vector<Texture> platform_sprites;
    std::vector<Texture> duck_sprites;
    std::vector<Texture> wing_sprites;
    std::vector<Texture> weapon_sprites;
    std::vector<Texture> bullet_sprites;
    std::vector<DuckView> duck_views;
    std::vector<Texture> scoreboard_font;
    std::vector<Texture> box_sprites;

    void set_up_game();
    void load_map();
    void load_ducks(game_snapshot_t gs);
    void load_bullets(game_snapshot_t gs);
    void load_weapons(game_snapshot_t gs);
    void draw_scoreboard(score_DTO score);
    void zoom(game_snapshot_t gs);
    void load_boxes(game_snapshot_t gs);
    void add_ducks(game_snapshot_t gs);

public:
    GameView();
    void add_map(map_structure_t map);
    void load_score(score_DTO score);
    void load_endgame_score(score_DTO score);
    void load_game(game_snapshot_t gs);
    ~GameView();
};

#endif
#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "../common_src/action_t.h"
#include "../common_src/game_snapshot_t.h"
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Exception.hh>

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

        std::vector<int> duck_views;
        std::vector<int> wing_views;
        std::vector<int> dir; //esto lo van a tener que cambiar en game eh

        int bgWidth;
        int bgHeight;
        int bgScaledWidth;
        int bgScaledHeight;

        void set_up_game();
        void load_map();
        void load_ducks(game_snapshot_t gs);
        void load_bullets(game_snapshot_t gs);
        
    public:
        GameView(map_structure_t map);
        void load_game(game_snapshot_t gs);
        ~GameView();
        
};

#endif
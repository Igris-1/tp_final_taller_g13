#include "game_view.h"
#include "../common_src/game_snapshot_t.h"

#define SCREEN_WIDTH 820
#define SCREEN_HEIGHT 500

GameView::GameView(map_structure_t map):map(map),
    sdl(SDL_INIT_VIDEO),
    window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    background_sprites(),
    platform_sprites(),
    duck_sprites(),
    wing_sprites(),
    weapon_sprites(),
    bullet_sprites(),
    duck_views(0),
    wing_views(0),
    dir(0){
    set_up_game();
}

void GameView::set_up_game(){
    background_sprites.push_back(Texture(renderer, "../game_ui/game.png"));

    
    platform_sprites.push_back(Texture(renderer, "../game_ui/platform.png"));
    
    duck_sprites.push_back(Texture(renderer, "../game_ui/duck_sprites.png"));

    wing_sprites.push_back(Texture (renderer, "../game_ui/alas.png"));

    //weapon_sprites.push_back(Texture(renderer, "../game_ui/weapon.png"));

    //bullet_sprites.push_back(Texture(renderer, "../game_ui/bullet.png"));
  
    SDL_QueryTexture(Texture(renderer, "../game_ui/game.png").Get(), nullptr, nullptr, &bgWidth, &bgHeight);
    float bgAspectRatio = static_cast<float>(bgWidth) / static_cast<float>(bgHeight);
    bgScaledWidth = SCREEN_WIDTH;
    bgScaledHeight = static_cast<int>(SCREEN_WIDTH / bgAspectRatio);
    bgScaledWidth = static_cast<int>(SCREEN_HEIGHT * bgAspectRatio);

    /*duck_views.resize(gs.ducks.size(), 0);
    wing_views.resize(gs.ducks.size(), 0);
    dir.resize(gs.ducks.size(), 0);*/
}

void GameView::load_game(game_snapshot_t gs){
    renderer.Clear();
    duck_views.resize(gs.ducks.size(), 1);
    wing_views.resize(gs.ducks.size(), 2);
    dir.resize(gs.ducks.size(), 0);
    load_map();
    load_ducks(gs);
    renderer.Present();
}

void GameView::load_map(){
    Texture& backgroundTexture = background_sprites[0];
    renderer.Copy(backgroundTexture, SDL_Rect{0, 0, bgWidth, bgHeight}, SDL_Rect{0, 0, bgScaledWidth, bgScaledHeight});

    for (int i=0; i<map.platforms_len;i++){
        platform_DTO platform = map.platforms[i];
        renderer.Copy(platform_sprites[0], SDL_Rect{0, 11*7, 16, 8}, SDL_Rect{platform.x, platform.y, platform.width, platform.height});
    }
}

void GameView::load_ducks(game_snapshot_t gs){
    Texture& duckTexture = duck_sprites[0];
    Texture& wingTexture = wing_sprites[0];

    for (int i=0; i < gs.ducks.size(); i++) {
        duck_DTO duck = gs.ducks[i];
        if (duck.is_moving_right){
            dir[i] = 0;
        } else if (duck.is_moving_left){
            dir[i] = 1;
        }
        if (duck.jumping){
            renderer.Copy(duckTexture, SDL_Rect{1*32+1, 44, 32, 32}, SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16}, 0, NullOpt, dir[i]);
        } else if (duck.falling){
            int ai = 10;
            if (dir[i]){
                ai = 22;
            }
            renderer.Copy(duckTexture, SDL_Rect{3*32+1, 44, 32, 32}, SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16}, 0, NullOpt, dir[i]);
            renderer.Copy(wingTexture, SDL_Rect{wing_views[i]*16, 32, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+15, 32, 32}, 0, NullOpt, dir[i]);
        } else if (duck.is_moving_right ^ duck.is_moving_left){
            int ai = 10;
            if (dir[i]){
                ai = 22;
            }
            renderer.Copy(duckTexture, SDL_Rect{duck_views[i]*32+1, 8, 32, 32}, SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16}, 0, NullOpt, dir[i]);
            renderer.Copy(wingTexture, SDL_Rect{16, 0, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+25, 32, 32}, 0, NullOpt, dir[i]);
        } else {
            
            renderer.Copy(duckTexture, SDL_Rect{1, 8, 32, 32}, SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16}, 0, NullOpt, dir[i]);
            int ai = 10;
            if (dir[i]){
                ai = 22;
            }
            SDL_Rect rect = SDL_Rect{0, 0, 16, 16};
            SDL_Rect duckRect = SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16};
            renderer.Copy(wingTexture, SDL_Rect{0, 0, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+25, 32, 32}, 0, NullOpt, dir[i]);
        }
        wing_views[i] = (wing_views[i] < 5) ? (wing_views[i] + 1) : 2;


        duck_views[i] = (duck_views[i] < 5) ? (duck_views[i] + 1) : 1;

    }
}

GameView::~GameView(){}
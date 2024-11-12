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

    Texture duck1Texture(renderer, "../game_ui/duck.png");

    Texture duck2Texture(renderer, "../game_ui/duck.png");
    duck2Texture.SetColorMod(200,40,40);

    Texture duck3Texture(renderer, "../game_ui/duck.png");
    duck3Texture.SetColorMod(40,200,40);

    Texture duck4Texture(renderer, "../game_ui/duck.png");
    duck4Texture.SetColorMod(40,40,200);
    
    duck_sprites.push_back(std::move(duck1Texture));
    duck_sprites.push_back(std::move(duck2Texture));
    duck_sprites.push_back(std::move(duck3Texture));
    duck_sprites.push_back(std::move(duck4Texture));
    
    Texture wing1Texture(renderer, "../game_ui/wing.png");

    Texture wing2Texture(renderer, "../game_ui/wing.png");
    wing2Texture.SetColorMod(200,40,40);

    Texture wing3Texture(renderer, "../game_ui/wing.png");
    wing3Texture.SetColorMod(40,200,40);

    Texture wing4Texture(renderer, "../game_ui/wing.png");
    wing4Texture.SetColorMod(40,40,200);

    wing_sprites.push_back(std::move(wing1Texture));
    wing_sprites.push_back(std::move(wing2Texture));
    wing_sprites.push_back(std::move(wing3Texture));
    wing_sprites.push_back(std::move(wing4Texture));

    weapon_sprites.push_back(Texture(renderer, "../game_ui/cowboyPistol.png"));

    bullet_sprites.push_back(Texture(renderer, "../game_ui/pistolShell.png"));
  
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
    load_bullets(gs);
    renderer.Present();
}

void GameView::load_bullets(game_snapshot_t gs){
    Texture& bulletTexture = bullet_sprites[0];
    for (int i=0; i < gs.bullets.size(); i++) {
        bullet_DTO bullet = gs.bullets[i];

         renderer.SetDrawColor(Color(143, 142, 137, 0));
        
        int yellow_x = (bullet.x_direction == 1) ? bullet.x - bullet.width * 4 : bullet.x;

        renderer.Copy(bulletTexture, SDL_Rect{0, 0, 16, 16}, SDL_Rect{bullet.x, bullet.y, bullet.width, bullet.height},0, NullOpt, bullet.x_direction);
        renderer.FillRect(SDL_Rect{yellow_x, bullet.y+8, bullet.width * 4, bullet.height/8});

    }
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
    

    for (int i=0; i < gs.ducks.size(); i++) {
        duck_DTO duck = gs.ducks[i];
        int duck_id = static_cast<int>(duck.duck_id);
        //std::cout << "Duck id: " << duck_id << std::endl;
        Texture& duckTexture = duck_sprites[duck_id];
        Texture& wingTexture = wing_sprites[duck_id];
        Texture& weaponTexture = weapon_sprites[0];
        if (duck.is_moving_right){
            dir[i] = 0;
        } else if (duck.is_moving_left){
            dir[i] = 1;
        }
        if(!duck.is_alive){
            Texture dead_duck(renderer, "../game_ui/cookedDuck.png");
            renderer.Copy(dead_duck, SDL_Rect{0, 0, 16, 16}, SDL_Rect{duck.x, duck.y+32, duck.width, duck.height-16}, 0, NullOpt, dir[i]);
        }
        else if (duck.jumping){
            int ai = 10;
            if (dir[i]){
                ai = 22;
            }
            int ai2 = 22;
            if (dir[i]){
                ai2 = 10;
            }
            renderer.Copy(duckTexture, SDL_Rect{1*32, 40, 32, 32}, SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16}, 0, NullOpt, dir[i]);
            renderer.Copy(weaponTexture, SDL_Rect{0, 0, 22, 11}, SDL_Rect{duck.x-16+ai2, duck.y+15, 36, 18}, 0, NullOpt, dir[i]);
            renderer.Copy(wingTexture, SDL_Rect{0, 6*8, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+15, 32, 32}, 0, NullOpt, dir[i]);
            
        } else if (duck.falling){
            int ai = 10;
            if (dir[i]){
                ai = 22;
            }
            int ai2 = 22;
            if (dir[i]){
                ai2 = 10;
            }

            renderer.Copy(duckTexture, SDL_Rect{3*32, 40, 32, 32}, SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16}, 0, NullOpt, dir[i]);
            renderer.Copy(weaponTexture, SDL_Rect{0, 0, 22, 11}, SDL_Rect{duck.x-16+ai2, duck.y+18, 36, 18}, 0, NullOpt, dir[i]);
            renderer.Copy(wingTexture, SDL_Rect{wing_views[i]*16, 32, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+15, 32, 32}, 0, NullOpt, dir[i]);
            renderer.Copy(wingTexture, SDL_Rect{0, 6*8, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+18, 32, 32}, 0, NullOpt, dir[i]);
            
        } else if (duck.is_moving_right ^ duck.is_moving_left){
            int ai = 10;
            if (dir[i]){
                ai = 22;
            }
            int ai2 = 22;
            if (dir[i]){
                ai2 = 10;
            }
            renderer.Copy(duckTexture, SDL_Rect{duck_views[i]*32, 0, 32, 32}, SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16}, 0, NullOpt, dir[i]);
            //renderer.Copy(wingTexture, SDL_Rect{10, 6*8, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+25, 32, 32}, 0, NullOpt, dir[i]);
            renderer.Copy(weaponTexture, SDL_Rect{0, 0, 22, 11}, SDL_Rect{duck.x-16+ai2, duck.y+27, 36, 18}, 0, NullOpt, dir[i]);
            renderer.Copy(wingTexture, SDL_Rect{0, 6*8, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+27, 32, 32}, 0, NullOpt, dir[i]);
            
        } else{
            
            renderer.Copy(duckTexture, SDL_Rect{0, 0, 32, 32}, SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16}, 0, NullOpt, dir[i]);
            int ai = 10;
            if (dir[i]){
                ai = 22;
            }
            int ai2 = 22;
            if (dir[i]){
                ai2 = 10;
            }
            SDL_Rect rect = SDL_Rect{0, 0, 16, 16};
            SDL_Rect duckRect = SDL_Rect{duck.x-16, duck.y, duck.width+32, duck.height+16};
            //renderer.Copy(wingTexture, SDL_Rect{0, 0, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+25, 32, 32}, 0, NullOpt, dir[i]);
            renderer.Copy(weaponTexture, SDL_Rect{0, 0, 22, 11}, SDL_Rect{duck.x-16+ai2, duck.y+27, 36, 18}, 0, NullOpt, dir[i]);
            renderer.Copy(wingTexture, SDL_Rect{0, 6*8, 16, 16}, SDL_Rect{duck.x-16+ai, duck.y+27, 32, 32}, 0, NullOpt, dir[i]);
            
        } 
        wing_views[i] = (wing_views[i] < 5) ? (wing_views[i] + 1) : 2;


        duck_views[i] = (duck_views[i] < 5) ? (duck_views[i] + 1) : 1;

    }
}

GameView::~GameView(){}
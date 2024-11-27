#include "gear_view.h"

#define AMOUNT_OF_DUCK_ACTIONS 3
#define IDLE_WALKING_CROUCHING_DUCK 0
#define JUMPING_FALLING_DUCK 1
#define FLYING_DUCK 2

GearView::GearView(Renderer& renderer, std::vector<Texture>& gear_textures, std::vector<Texture>& accessories_textures):
        renderer(renderer),
        gear_textures(gear_textures),
		accessories_textures(accessories_textures){
		gear_frames.resize(AMOUNT_OF_DUCK_ACTIONS);
		accessories_frames.resize(AMOUNT_OF_DUCK_ACTIONS);

		push_gear_frame_values();
}

void GearView::push_gear_frame_values(){
	push_gear_frame_for_idle_walking_crouching_duck();
	push_gear_frame_for_jumping_falling_duck();
	push_gear_frame_for_flying_duck();
}

void GearView::push_gear_frame_for_idle_walking_crouching_duck(){
	// cowboyPistol frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(6);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-14);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(11);
	// laserRifle frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-8);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-5);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(8);
	// ak47 frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-5);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-7);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(10);
	// grenade frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	// active grenade frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	// magnum frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	// oldPistol frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	// pewpewLaser frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	// shotgun frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-3);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-12);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(9);
	// sniper frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	// banana frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	// active banana frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	// helmet frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(6);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(2);
	// armor frames
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(2);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(4);
	gear_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(12);
	// helmet accessory frames
	accessories_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-5);
	accessories_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(11);
	accessories_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-8);
	// armor accessory frames
	accessories_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(5);
	accessories_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(-2);
	accessories_frames[IDLE_WALKING_CROUCHING_DUCK].push_back(15);
}

void GearView::push_gear_frame_for_jumping_falling_duck() {
    // cowboyPistol frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(6);
    gear_frames[JUMPING_FALLING_DUCK].push_back(-14);
    gear_frames[JUMPING_FALLING_DUCK].push_back(-1);
    // laserRifle frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(-8);
    gear_frames[JUMPING_FALLING_DUCK].push_back(-5);
    gear_frames[JUMPING_FALLING_DUCK].push_back(-4);
    // ak47 frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(-5);
    gear_frames[JUMPING_FALLING_DUCK].push_back(-7);
    gear_frames[JUMPING_FALLING_DUCK].push_back(-2);
    // grenade frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
	// active grenade frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    // magnum frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    // oldPistol frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    // pewpewLaser frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    // shotgun frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(-3);
    gear_frames[JUMPING_FALLING_DUCK].push_back(-12);
    gear_frames[JUMPING_FALLING_DUCK].push_back(-3);
    // sniper frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    // banana frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
	// active banana frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    // helmet frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
    gear_frames[JUMPING_FALLING_DUCK].push_back(6);
    gear_frames[JUMPING_FALLING_DUCK].push_back(-10);
    // armor frames
    gear_frames[JUMPING_FALLING_DUCK].push_back(2);
    gear_frames[JUMPING_FALLING_DUCK].push_back(4);
    gear_frames[JUMPING_FALLING_DUCK].push_back(0);
	// helmet accessory frames
	accessories_frames[JUMPING_FALLING_DUCK].push_back(0);
	accessories_frames[JUMPING_FALLING_DUCK].push_back(8);
	accessories_frames[JUMPING_FALLING_DUCK].push_back(-22);
	// armor accessory frames
	accessories_frames[JUMPING_FALLING_DUCK].push_back(3);
	accessories_frames[JUMPING_FALLING_DUCK].push_back(2);
	accessories_frames[JUMPING_FALLING_DUCK].push_back(-3);
}

void GearView::push_gear_frame_for_flying_duck() {
    // cowboyPistol frames
    gear_frames[FLYING_DUCK].push_back(-11);
    gear_frames[FLYING_DUCK].push_back(16);
    gear_frames[FLYING_DUCK].push_back(-16);
    // laserRifle frames
    gear_frames[FLYING_DUCK].push_back(-25);
    gear_frames[FLYING_DUCK].push_back(25);
    gear_frames[FLYING_DUCK].push_back(-19);
    // ak47 frames
    gear_frames[FLYING_DUCK].push_back(-22);
    gear_frames[FLYING_DUCK].push_back(23);
    gear_frames[FLYING_DUCK].push_back(-17);
    // grenade frames
    gear_frames[FLYING_DUCK].push_back(-17);
    gear_frames[FLYING_DUCK].push_back(30);
    gear_frames[FLYING_DUCK].push_back(-27);
	// active grenade frames
    gear_frames[FLYING_DUCK].push_back(-17);
    gear_frames[FLYING_DUCK].push_back(30);
    gear_frames[FLYING_DUCK].push_back(-27);
    // magnum frames
    gear_frames[FLYING_DUCK].push_back(-17);
    gear_frames[FLYING_DUCK].push_back(30);
    gear_frames[FLYING_DUCK].push_back(-27);
    // oldPistol frames
    gear_frames[FLYING_DUCK].push_back(-17);
    gear_frames[FLYING_DUCK].push_back(30);
    gear_frames[FLYING_DUCK].push_back(-27);
    // pewpewLaser frames
    gear_frames[FLYING_DUCK].push_back(-17);
    gear_frames[FLYING_DUCK].push_back(30);
    gear_frames[FLYING_DUCK].push_back(-27);
    // shotgun frames
    gear_frames[FLYING_DUCK].push_back(-20);
    gear_frames[FLYING_DUCK].push_back(18);
    gear_frames[FLYING_DUCK].push_back(-18);
    // sniper frames
    gear_frames[FLYING_DUCK].push_back(-17);
    gear_frames[FLYING_DUCK].push_back(30);
    gear_frames[FLYING_DUCK].push_back(-27);
    // banana frames
    gear_frames[FLYING_DUCK].push_back(-17);
    gear_frames[FLYING_DUCK].push_back(30);
    gear_frames[FLYING_DUCK].push_back(-27);
	// active banana frames
    gear_frames[FLYING_DUCK].push_back(-17);
    gear_frames[FLYING_DUCK].push_back(30);
    gear_frames[FLYING_DUCK].push_back(-27);
    // helmet frames
    gear_frames[FLYING_DUCK].push_back(-17);
    gear_frames[FLYING_DUCK].push_back(36);
    gear_frames[FLYING_DUCK].push_back(-10);
    // armor frames
    gear_frames[FLYING_DUCK].push_back(-10);
    gear_frames[FLYING_DUCK].push_back(24);
    gear_frames[FLYING_DUCK].push_back(-10);
	// helmet accessory frames
	accessories_frames[FLYING_DUCK].push_back(-4);
    accessories_frames[FLYING_DUCK].push_back(10);
    accessories_frames[FLYING_DUCK].push_back(-30);
	// armor accessory frames
	accessories_frames[FLYING_DUCK].push_back(5);
    accessories_frames[FLYING_DUCK].push_back(0);
    accessories_frames[FLYING_DUCK].push_back(-2);
}



/*void GearView::push_gear_frame_for_crouching_duck() {
	// cowboyPistol frames
	gear_frames[CROUCHING_DUCK].push_back(6);
	gear_frames[CROUCHING_DUCK].push_back(12);
	gear_frames[CROUCHING_DUCK].push_back(11);
	// laserRifle frames
	gear_frames[CROUCHING_DUCK].push_back(-4);
	gear_frames[CROUCHING_DUCK].push_back(7);
	gear_frames[CROUCHING_DUCK].push_back(-6);
	// ak47 frames
	gear_frames[CROUCHING_DUCK].push_back(6);
	gear_frames[CROUCHING_DUCK].push_back(7);
	gear_frames[CROUCHING_DUCK].push_back(-6);
	// grenade frames
	// magnum frames
	// oldPistol frames
	// pewpewLaser frames
	// shotgun frames
	// sniper frames
	// banana frames
}*/


//dibujar gear en el mapa
void GearView::draw_gear(weapon_DTO& weapon) {
	int gear = weapon.weapon_id-1;
	int x = weapon.x;
	int y = weapon.y;
	int width = weapon.width;
	int height = weapon.height;
	switch (gear){
		case 0:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
		case 3:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
			SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
		case 4:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
			SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
		case 10:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
			SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
		case 11:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
			SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
		case 12:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                    SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
		case 13:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
			SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
		default:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 8, 32, 16},
					SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
	}
}
//dibujar gear en las manos del pato
void GearView::draw_gear_in_hands(int x, int y, int gear, int inclination, int facing_direction){
	switch (gear){
		case 0: 
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 22, 11},
				SDL_Rect{x, y, 36, 18}, inclination, NullOpt, facing_direction);
			break;
		case 10:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                SDL_Rect{x, y, 24, 24}, inclination, NullOpt, 0);
			break;
		case 11:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                SDL_Rect{x, y, 24, 24}, inclination, NullOpt, 0);
			break;
		case 12:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                SDL_Rect{x, y, 24, 24}, inclination, NullOpt, 0);
			break;
		case 13:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 0, 16, 16},
                SDL_Rect{x, y, 24, 24}, inclination, NullOpt, 0);
			break;
		default:
			renderer.Copy(gear_textures[gear], SDL_Rect{0, 8, 32, 16},
				SDL_Rect{x, y, 48, 24}, inclination, NullOpt, facing_direction);
			break;
	}
}

void GearView::draw_accessories(duck_DTO duck, bool facing_direction, int action){
	int x = duck.x;
	int y = duck.y;
	int width = duck.width;
	int height = duck.height;

	int x_sum_value;
	int x_mult_value;
	int y_sum_value;
	
	if (duck.helmet_equipped){
		x_sum_value = accessories_frames[action][0];
		x_mult_value = accessories_frames[action][1];
		y_sum_value = accessories_frames[action][2];
		std::cout << "x_sum_value: " << x_sum_value << std::endl;	
		std::cout << "x_mult_value: " << x_mult_value << std::endl;
		std::cout << "y_sum_value: " << y_sum_value << std::endl;
		if (action == JUMPING_FALLING_DUCK){
			renderer.Copy(accessories_textures[0], SDL_Rect{8, 10, 16, 16},
                      SDL_Rect{x + x_sum_value + facing_direction*x_mult_value, y + y_sum_value, 24, 24}, 0, NullOpt,
                      facing_direction);
		} else {
			renderer.Copy(accessories_textures[0], SDL_Rect{8, 10, 16, 16},
                      SDL_Rect{x + x_sum_value + facing_direction*x_mult_value, y + y_sum_value, 32, 32}, 0, NullOpt,
                      facing_direction);
		}
		
	} else if (duck.armor_equipped){
		x_sum_value = accessories_frames[action][3];
		x_mult_value = accessories_frames[action][4];
		y_sum_value = accessories_frames[action][5];
		renderer.Copy(accessories_textures[1], SDL_Rect{8, 8, 16, 16},
                      SDL_Rect{x + x_sum_value + facing_direction*x_mult_value, y + y_sum_value, 24, 24}, 0, NullOpt,
                      facing_direction);
	}
}
//dibujar gear que tiene un pato
void GearView::draw_held_gear(bool& facing_direction, duck_DTO& duck){
	int gear = duck.weapon_id-1;
	int x = duck.x;
	int y = duck.y;

	int x_sum_value;
	int x_mult_value;
	int y_sum_value;
	int inclination = 0;

	if (duck.jumping){
		if (gear >= 0) {
			x_sum_value = gear_frames[JUMPING_FALLING_DUCK][gear*3];
			x_mult_value = gear_frames[JUMPING_FALLING_DUCK][gear*3+1];
			y_sum_value = gear_frames[JUMPING_FALLING_DUCK][gear*3+2];
		}
		draw_accessories(duck, facing_direction, JUMPING_FALLING_DUCK);

	} else if (duck.falling){
		if (gear >= 0) {
			x_sum_value = gear_frames[FLYING_DUCK][gear*3];
			x_mult_value = gear_frames[FLYING_DUCK][gear*3+1];
			y_sum_value = gear_frames[FLYING_DUCK][gear*3+2];
			inclination = -90 + facing_direction * 180;
		}
		draw_accessories(duck, facing_direction, FLYING_DUCK);

	} else {
		if (gear >= 0) {
			x_sum_value = gear_frames[IDLE_WALKING_CROUCHING_DUCK][gear*3];
			x_mult_value = gear_frames[IDLE_WALKING_CROUCHING_DUCK][gear*3+1];
			y_sum_value = gear_frames[IDLE_WALKING_CROUCHING_DUCK][gear*3+2];
		}
		draw_accessories(duck, facing_direction, IDLE_WALKING_CROUCHING_DUCK);

	} if (gear >= 0) {
		draw_gear_in_hands(x + x_sum_value + facing_direction*x_mult_value, y + y_sum_value, gear, inclination, facing_direction);
	}
	
}

GearView::~GearView() {
}
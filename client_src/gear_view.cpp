#include "gear_view.h"

#define AMOUNT_OF_DUCK_ACTIONS 4
#define IDLE_WALKING_DUCK 0
#define JUMPING_FALLING_DUCK 1
#define FLYING_DUCK 2
#define CROUCHING_DUCK 3
#define AMOUNT_OF_GEAR 10

GearView::GearView(Renderer& renderer, std::vector<Texture>& gear_textures, std::vector<Texture>& accessories_sprites):
        renderer(renderer),
        gear_textures(gear_textures),
		accessories_sprites(accessories_sprites){
		gear_frames.resize(AMOUNT_OF_DUCK_ACTIONS);

		push_gear_frame_values();
}

void GearView::push_gear_frame_values(){
	push_gear_frame_for_idle_walking_duck();
	push_gear_frame_for_jumping_falling_duck();
	push_gear_frame_for_flying_duck();
}

void GearView::push_gear_frame_for_idle_walking_duck(){
	// cowboyPistol frames
	gear_frames[IDLE_WALKING_DUCK].push_back(6);
	gear_frames[IDLE_WALKING_DUCK].push_back(12);
	gear_frames[IDLE_WALKING_DUCK].push_back(11);
	// laserRifle frames
	gear_frames[IDLE_WALKING_DUCK].push_back(-4);
	gear_frames[IDLE_WALKING_DUCK].push_back(7);
	gear_frames[IDLE_WALKING_DUCK].push_back(-6);
	// ak47 frames
	gear_frames[IDLE_WALKING_DUCK].push_back(6);
	gear_frames[IDLE_WALKING_DUCK].push_back(7);
	gear_frames[IDLE_WALKING_DUCK].push_back(-6);
	// grenade frames
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	// magnum frames
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	// oldPistol frames
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	// pewpewLaser frames
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	// shotgun frames
	gear_frames[IDLE_WALKING_DUCK].push_back(-16);
	gear_frames[IDLE_WALKING_DUCK].push_back(20);
	gear_frames[IDLE_WALKING_DUCK].push_back(-26);
	// sniper frames
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	// banana frames
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
	gear_frames[IDLE_WALKING_DUCK].push_back(0);
}

void GearView::push_gear_frame_for_jumping_falling_duck() {
	// cowboyPistol frames
	gear_frames[JUMPING_FALLING_DUCK].push_back(6);
	gear_frames[JUMPING_FALLING_DUCK].push_back(12);
	gear_frames[JUMPING_FALLING_DUCK].push_back(-1);
	// laserRifle frames
	gear_frames[JUMPING_FALLING_DUCK].push_back(-4);
	gear_frames[JUMPING_FALLING_DUCK].push_back(7);
	gear_frames[JUMPING_FALLING_DUCK].push_back(-16);
	// ak47 frames
	gear_frames[JUMPING_FALLING_DUCK].push_back(-4);
	gear_frames[JUMPING_FALLING_DUCK].push_back(7);
	gear_frames[JUMPING_FALLING_DUCK].push_back(-16);
	// grenade frames
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
	gear_frames[JUMPING_FALLING_DUCK].push_back(-16);
	gear_frames[JUMPING_FALLING_DUCK].push_back(20);
	gear_frames[JUMPING_FALLING_DUCK].push_back(-26);
	// sniper frames
	gear_frames[JUMPING_FALLING_DUCK].push_back(0);
	gear_frames[JUMPING_FALLING_DUCK].push_back(0);
	gear_frames[JUMPING_FALLING_DUCK].push_back(0);
	// banana frames
	gear_frames[JUMPING_FALLING_DUCK].push_back(0);
	gear_frames[JUMPING_FALLING_DUCK].push_back(0);
	gear_frames[JUMPING_FALLING_DUCK].push_back(0);
}

void GearView::push_gear_frame_for_flying_duck() {
	// cowboyPistol frames
	gear_frames[FLYING_DUCK].push_back(-11);
	gear_frames[FLYING_DUCK].push_back(20);
	gear_frames[FLYING_DUCK].push_back(-16);
	// laserRifle frames
	gear_frames[FLYING_DUCK].push_back(-16);
	gear_frames[FLYING_DUCK].push_back(20);
	gear_frames[FLYING_DUCK].push_back(-26);
	// ak47 frames
	gear_frames[FLYING_DUCK].push_back(-16);
	gear_frames[FLYING_DUCK].push_back(20);
	gear_frames[FLYING_DUCK].push_back(-26);
	// grenade frames
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	// magnum frames
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	// oldPistol frames
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	// pewpewLaser frames
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	// shotgun frames
	gear_frames[FLYING_DUCK].push_back(-16);
	gear_frames[FLYING_DUCK].push_back(20);
	gear_frames[FLYING_DUCK].push_back(-26);
	// sniper frames
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	// banana frames
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
	gear_frames[FLYING_DUCK].push_back(0);
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
	int gear_id = weapon.weapon_id-1;
	int x = weapon.x;
	int y = weapon.y;
	int width = weapon.width;
	int height = weapon.height;
	std::cout << "gear id" << gear_id << std::endl;

	switch (gear_id){
		case 1:
			renderer.Copy(gear_textures[gear_id], SDL_Rect{0, 0, 22, 11},
                          SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
		case 2:
			renderer.Copy(gear_textures[gear_id], SDL_Rect{0, 0, 32, 32},
                    SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
		default:
			renderer.Copy(gear_textures[gear_id], SDL_Rect{0, 0, 32, 32},
					SDL_Rect{x, y, width, height}, 0, NullOpt, 0);
			break;
	}
}

//dibujar gear que tiene un pato
void GearView::draw_held_gear(bool& facing_direction, duck_DTO& duck){
	int gear_id = duck.weapon_id-1;
	int x = duck.x;
	int y = duck.y;

	int x_sum_value;
	int x_mult_value;
	int y_sum_value;
	int inclination = 0;

	if (duck.jumping){
		x_sum_value = gear_frames[JUMPING_FALLING_DUCK][gear_id];
		x_mult_value = gear_frames[JUMPING_FALLING_DUCK][gear_id+1];
		y_sum_value = gear_frames[JUMPING_FALLING_DUCK][gear_id+2];
	} else if (duck.falling){
		x_sum_value = gear_frames[FLYING_DUCK][gear_id];
		x_mult_value = gear_frames[FLYING_DUCK][gear_id+1];
		y_sum_value = gear_frames[FLYING_DUCK][gear_id+2];
		inclination = -90 + facing_direction * 180;
		
	} else {
		x_sum_value = gear_frames[IDLE_WALKING_DUCK][gear_id];
		x_mult_value = gear_frames[IDLE_WALKING_DUCK][gear_id+1];
		y_sum_value = gear_frames[IDLE_WALKING_DUCK][gear_id+2];
	}
	if(gear_id == 1){
		renderer.Copy(gear_textures[gear_id], SDL_Rect{0, 0, 22, 11},
						SDL_Rect{x + x_sum_value + facing_direction*x_mult_value, y + y_sum_value, 36, 18}, inclination, NullOpt, facing_direction);
	}else{
		renderer.Copy(gear_textures[gear_id], SDL_Rect{0, 0, 32, 32},
				SDL_Rect{x + x_sum_value + facing_direction*x_mult_value, y + y_sum_value, 32, 32}, inclination, NullOpt, facing_direction);
	}

	
}

GearView::~GearView() {
}
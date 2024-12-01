#ifndef TRANSLATOR_DTOS_H
#define TRANSLATOR_DTOS_H

#include <string>
#include <arpa/inet.h>
#include "DTOs.h"

class TranslatorDTOs {
    private:
        bool is_little_endian(){
            uint16_t aux = 0x0b0d;
            uint8_t* ptr = reinterpret_cast<uint8_t*>(&aux);
            return ptr[0] == 0x0d;
        }

        // da vuelta los bytes para que cambie de endianess. osea un 0x123456 pasa a 0x563412
        void change_endianess(void * dto, size_t size){
            uint8_t* bytes = static_cast<uint8_t*>(dto);
            for (size_t i = 0; i < size / 2; ++i) {
                std::swap(bytes[i], bytes[size - 1 - i]);
            }
        }
    public:
        TranslatorDTOs() {}

        void ntoh_duck_DTO(duck_DTO *duck_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(duck_dto, sizeof(duck_DTO));
        }

        void hton_duck_DTO(duck_DTO *duck_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(duck_dto, sizeof(duck_DTO));
        }

        void ntoh_platform_DTO(platform_DTO *platform_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(platform_dto, sizeof(platform_DTO));
        }

        void hton_platform_DTO(platform_DTO *platform_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(platform_dto, sizeof(platform_DTO));
        }

        void ntoh_bullet_DTO(bullet_DTO *bullet_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(bullet_dto, sizeof(bullet_DTO));
        }

        void hton_bullet_DTO(bullet_DTO *bullet_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(bullet_dto, sizeof(bullet_DTO));
        }

        void ntoh_weapon_DTO(weapon_DTO *weapon_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(weapon_dto, sizeof(weapon_DTO));
        }

        void hton_weapon_DTO(weapon_DTO *weapon_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(weapon_dto, sizeof(weapon_DTO));
        }

        void ntoh_box_DTO(box_DTO *box_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(box_dto, sizeof(box_DTO));
        }

        void hton_box_DTO(box_DTO *box_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(box_dto, sizeof(box_DTO));
        }

        void ntoh_sounds_DTO(sounds_DTO *sound_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(sound_dto, sizeof(sounds_DTO));
        }

        void hton_sounds_DTO(sounds_DTO *sound_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(sound_dto, sizeof(sounds_DTO));
        }

        void ntoh_games_DTO(games_DTO *games_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(games_dto, sizeof(games_DTO));
        }

        void hton_games_DTO(games_DTO *games_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(games_dto, sizeof(games_DTO));
        }

        void ntoh_score_DTO(score_DTO *score_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(score_dto, sizeof(score_DTO));
        }

        void hton_score_DTO(score_DTO *score_dto){
            if(!this->is_little_endian()){
                return;
            }
            this->change_endianess(score_dto, sizeof(score_DTO));
        }
};

#endif // TRANSLATOR_DTOS_H
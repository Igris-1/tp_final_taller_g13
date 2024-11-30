#ifndef TRANSLATOR_DTOS_H
#define TRANSLATOR_DTOS_H

#include <string>
#include <arpa/inet.h>
#include "DTOs.h"

class TranslatorDTOs {
    private:

    public:
        TranslatorDTOs() {}

        void ntoh_duck_DTO(duck_DTO *duck_dto){
            duck_dto->x = ntohs(duck_dto->x);
            duck_dto->y = ntohs(duck_dto->y);
            duck_dto->width = ntohs(duck_dto->width);
            duck_dto->height = ntohs(duck_dto->height);
        }

        void hton_duck_DTO(duck_DTO *duck_dto){
            duck_dto->x = htons(duck_dto->x);
            duck_dto->y = htons(duck_dto->y);
            duck_dto->width = htons(duck_dto->width);
            duck_dto->height = htons(duck_dto->height);
        }

        void ntoh_platform_DTO(platform_DTO *platform_dto){
            platform_dto->x =  ntohs(platform_dto->x);
            platform_dto->y =  ntohs(platform_dto->y);
            platform_dto->width =  ntohs(platform_dto->width);
            platform_dto->height =  ntohs(platform_dto->height);
        }

        void hton_platform_DTO(platform_DTO *platform_dto){
            platform_dto->x =  htons(platform_dto->x);
            platform_dto->y =  htons(platform_dto->y);
            platform_dto->width =  htons(platform_dto->width);
            platform_dto->height =  htons(platform_dto->height);
        }

        void ntoh_bullet_DTO(bullet_DTO *bullet_dto){
            bullet_dto->x = ntohs(bullet_dto->x);
            bullet_dto->y = ntohs(bullet_dto->y);
            bullet_dto->width = ntohs(bullet_dto->width);
            bullet_dto->height = ntohs(bullet_dto->height);
        }

        void hton_bullet_DTO(bullet_DTO *bullet_dto){
            bullet_dto->x = htons(bullet_dto->x);
            bullet_dto->y = htons(bullet_dto->y);
            bullet_dto->width = htons(bullet_dto->width);
            bullet_dto->height = htons(bullet_dto->height);
        }

        void ntoh_weapon_DTO(weapon_DTO *weapon_dto){
            weapon_dto->x = ntohs(weapon_dto->x);
            weapon_dto->y = ntohs(weapon_dto->y);
            weapon_dto->width = ntohs(weapon_dto->width);
            weapon_dto->height = ntohs(weapon_dto->height);
        }

        void hton_weapon_DTO(weapon_DTO *weapon_dto){
            weapon_dto->x = htons(weapon_dto->x);
            weapon_dto->y = htons(weapon_dto->y);
            weapon_dto->width = htons(weapon_dto->width);
            weapon_dto->height = htons(weapon_dto->height);
        }

        void ntoh_box_DTO(box_DTO *box_dto){
            box_dto->x = ntohs(box_dto->x);
            box_dto->y = ntohs(box_dto->y);
            box_dto->width = ntohs(box_dto->width);
            box_dto->height = ntohs(box_dto->height);
        }

        void hton_box_DTO(box_DTO *box_dto){
            box_dto->x = htons(box_dto->x);
            box_dto->y = htons(box_dto->y);
            box_dto->width = htons(box_dto->width);
            box_dto->height = htons(box_dto->height);
        }

        void ntoh_sound_DTO(sounds_DTO *sound_dto){
            return;
        }

        void hton_sound_DTO(sounds_DTO *sound_dto){
            return;
        }

        void ntoh_games_DTO(games_DTO *games_dto){
            return;
        }

        void hton_games_DTO(games_DTO *games_dto){
            return;
        }

        void ntoh_score_DTO(score_DTO *score_dto){
            return;
        }

        void hton_score_DTO(score_DTO *score_dto){
            return;
        }
};

#endif // TRANSLATOR_DTOS_H
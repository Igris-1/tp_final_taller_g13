#ifndef FAKE_WEAPON_H
#define FAKE_WEAPON_H

#include "weapon.h"
class FakeWeapon : public Weapon {
    private:

    public:
        explicit FakeWeapon(): Weapon(0) {}
        bool is_fake() override { return true; }
        ~FakeWeapon() {}

};

#endif

#include "../server_src/game_model/duck.h"

#include <gtest/gtest.h>

#include "../server_src/game_model/armor.h"
#include "../server_src/game_model/helmet.h"
#include "../server_src/game_model/weapon.h"


TEST(DuckTest, MoveToNewPosition) {
    Duck duck(100);
    Position new_position(10, 20);
    Position old_position = duck.move_to(new_position);

    EXPECT_EQ(duck.get_position(), new_position);
    EXPECT_EQ(old_position, Position(-1, -1));
}

TEST(DuckTest, ThrowWeaponToPosition) {
    Duck duck(100);
    Weapon weapon(1);
    duck.take_weapon(weapon);
    Position new_position(10, 20);

    duck.throw_weapon_to(new_position);

    EXPECT_EQ(duck.get_weapon().get_position(), new_position);
}

TEST(DuckTest, TakeWeapon) {
    Duck duck(100);
    Weapon weapon(1);
    Position initial_position = duck.get_position();

    Weapon old_weapon = duck.take_weapon(weapon);

    EXPECT_EQ(duck.get_weapon().get_position(), initial_position);
    EXPECT_EQ(&old_weapon, &weapon);
}

TEST(DuckTest, TakeArmor) {
    Duck duck(100);
    Armor armor(1);
    Position initial_position = duck.get_position();

    Armor old_armor = duck.take_armor(armor);

    EXPECT_EQ(duck.get_armor().get_position(), initial_position);
    EXPECT_EQ(&old_armor, &armor);
}

TEST(DuckTest, TakeHelmet) {
    Duck duck(100);
    Helmet helmet(1);
    Position initial_position = duck.get_position();

    Helmet old_helmet = duck.take_helmet(helmet);

    EXPECT_EQ(duck.get_helmet().get_position(), initial_position);
    EXPECT_EQ(&old_helmet, &helmet);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

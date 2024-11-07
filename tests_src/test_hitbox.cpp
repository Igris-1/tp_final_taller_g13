#include <gtest/gtest.h>

#include "../server_src/game_model/hitbox.h"

TEST(HitboxTest, PointCollision) {
    Hitbox hitbox(0, 0, 10, 10);

    EXPECT_TRUE(hitbox.has_collision(0, 0));
    EXPECT_TRUE(hitbox.has_collision(5, 5));
    EXPECT_TRUE(hitbox.has_collision(10, 10));
    EXPECT_TRUE(hitbox.has_collision(0, 10));
    EXPECT_TRUE(hitbox.has_collision(10, 0));
    EXPECT_TRUE(hitbox.has_collision(10, 5));
    EXPECT_TRUE(hitbox.has_collision(5, 10));

    EXPECT_FALSE(hitbox.has_collision(-1, -1));
    EXPECT_FALSE(hitbox.has_collision(10, -1));
    EXPECT_FALSE(hitbox.has_collision(-1, 10));

    EXPECT_FALSE(hitbox.has_collision(11, 11));
    EXPECT_FALSE(hitbox.has_collision(11, 10));
    EXPECT_FALSE(hitbox.has_collision(10, 11));
}

TEST(HitboxTest, HitboxCollision) {
    Hitbox hitbox1(0, 0, 2, 2);
    Hitbox hitbox2(1, 1, 2, 2);

    EXPECT_TRUE(hitbox1.has_collision(hitbox2));
    EXPECT_TRUE(hitbox2.has_collision(hitbox1));

    Hitbox hitbox3(5, 5, 1, 1);
    Hitbox hitbox4(4, 4, 1, 1);

    EXPECT_TRUE(hitbox3.has_collision(hitbox4));
    EXPECT_TRUE(hitbox4.has_collision(hitbox3));

    Hitbox hitbox5(0, 0, 10, 10);
    Hitbox hitbox6(1, 1, 1, 1);

    EXPECT_TRUE(hitbox5.has_collision(hitbox6));
    EXPECT_TRUE(hitbox6.has_collision(hitbox5));

    Hitbox hitbox7(3, 2, 1, 1);

    EXPECT_FALSE(hitbox1.has_collision(hitbox7));
    EXPECT_FALSE(hitbox7.has_collision(hitbox1));
}
#include <gtest/gtest.h>

#include "../server_src/game_model/position.h"

TEST(PositionTest, PositionCompareEquals) {
        Position pos1(1, 1);
        Position pos2(1, 1);
        Position pos3(2, 2);

        EXPECT_TRUE(pos1 == pos2);
        EXPECT_FALSE(pos1 == pos3);
        EXPECT_FALSE(pos2 == pos3);
}

TEST(PositionTest, PositionCompareLess) {
    Position pos1(1, 1);
    Position pos2(1, 1);
    Position pos3(2, 2);
    Position pos4(-3, -3);

    EXPECT_FALSE(pos1 < pos2);
    EXPECT_TRUE(pos1 < pos3);
    EXPECT_TRUE(pos2 < pos3);
    EXPECT_TRUE(pos3 < pos4);
}

TEST(PositionTest, PositionCompareLessEquals) {
    Position pos1(1, 1);
    Position pos2(1, 1);
    Position pos3(2, 2);
    Position pos4(-3, -3);

    EXPECT_TRUE(pos1 <= pos2);
    EXPECT_TRUE(pos1 <= pos3);
    EXPECT_TRUE(pos2 <= pos3);
    EXPECT_TRUE(pos3 <= pos4);
}

TEST(PositionTest, PositionCompareGreater) {
    Position pos1(1, 1);
    Position pos2(1, 1);
    Position pos3(2, 2);
    Position pos4(-3, -3);

    EXPECT_FALSE(pos1 > pos2);
    EXPECT_TRUE(pos3 > pos1);
    EXPECT_TRUE(pos3 > pos2);
    EXPECT_TRUE(pos4 > pos3);
}

TEST(PositionTest, PositionCompareGreaterEquals) {
    Position pos1(1, 1);
    Position pos2(1, 1);
    Position pos3(2, 2);
    Position pos4(-3, -3);

    EXPECT_TRUE(pos1 >= pos2);
    EXPECT_TRUE(pos3 >= pos1);
    EXPECT_TRUE(pos3 >= pos2);
    EXPECT_TRUE(pos4 >= pos3);
}

TEST(PositionTest, PositionSum) {
    Position pos1(1, 1);
    Position pos2(1, 2);
    Position pos3(-1, 2);
    Position pos4(-3, -3);

    Position pos5 = pos1 + pos2;
    Position pos6 = pos3 + pos4;
    Position pos7 = pos2 + pos3;

    EXPECT_TRUE(pos5 == Position(2, 3));
    EXPECT_TRUE(pos6 == Position(-4, -1));
    EXPECT_TRUE(pos7 == Position(0, 4));
}

TEST(PositionTest, PositionGetters) {
    Position pos2(1, 2);
    Position pos3(-1, 2);

    EXPECT_EQ(pos2.get_x(), 1);
    EXPECT_EQ(pos2.get_y(), 2);
    EXPECT_EQ(pos3.get_x(), -1);
    EXPECT_EQ(pos3.get_y(), 2);

    Position pos1 = pos2 + pos3;

    EXPECT_EQ(pos1.get_x(), 0);
    EXPECT_EQ(pos1.get_y(), 4);
}

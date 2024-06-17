#include <gtest/gtest.h>
#include "module.h"

TEST(ModuleTest, Add) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(-1, -1), -2);
    EXPECT_EQ(add(0, 0), 0);
}

TEST(ModuleTest, Subtract) {
    EXPECT_EQ(subtract(2, 1), 1);
    EXPECT_EQ(subtract(1, 1), 0);
    EXPECT_EQ(subtract(0, 1), -1);
    EXPECT_EQ(subtract(-1, -1), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

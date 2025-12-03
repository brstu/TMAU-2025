#include <gtest/gtest.h>
#include "func.h"

TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearModel(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linearModel(10, 0), A * 10);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linearModel(0, 5), B * 5);
}

TEST(LinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(linearModel(10, 5), A * 10 + B * 5);
}

// ------------------------
// NONLINEAR MODEL TESTS
// ------------------------

TEST(NonlinearModel, ZeroInput) {
    // В твоей формуле:
    // A*0 - B*0^2 + C*0 + D*sin(0) = 0
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, OnlyY) {
    // nonlinear(yt=10, yt1=10, ut=0, ut1=0)
    // = A*10 - B*100
    EXPECT_DOUBLE_EQ(nonlinearModel(10, 10, 0, 0),
                     A * 10 - B * pow(10, 2));
}

TEST(NonlinearModel, OnlyU) {
    // nonlinear(yt=0, yt1=0, ut=5, ut1=5)
    // = C*5 + D*sin(5)
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 5, 5),
                     C * 5 + D * sin(5));
}

TEST(NonlinearModel, GeneralCase) {
    // nonlinear(yt=10, yt1=10, ut=5, ut1=5)
    EXPECT_DOUBLE_EQ(nonlinearModel(10, 10, 5, 5),
                     A * 10 - B * pow(10, 2) + C * 5 + D * sin(5));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

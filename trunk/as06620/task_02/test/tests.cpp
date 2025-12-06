#include <gtest/gtest.h>
#include "../src/temp_model.h"

TEST(TemperatureModelTest, LinearInitialConditions) {
    TemperatureModel model(0.8, 0.2);
    model.setInitialConditions(20.0, 20.0, 0.0);

    EXPECT_DOUBLE_EQ(model.getCurrentTemperature(), 20.0);
}

TEST(TemperatureModelTest, LinearNextValueCalculation) {
    TemperatureModel model(0.8, 0.2);
    model.setInitialConditions(20.0, 20.0, 0.0);

    double y = model.calculateNext(10.0);
    EXPECT_NEAR(y, 0.8 * 20.0 + 0.2 * 10.0, 1e-9);
}

TEST(TemperatureModelTest, NonlinearUpdateCalculation) {
    TemperatureModel model(0.7, 0.01, 0.3, 0.1);
    model.setInitialConditions(20.0, 19.5, 5.0);

    double y = model.calculateNext(10.0);
    double expected = 0.7 * 20.0
                    - 0.01 * 19.5 * 19.5
                    + 0.3 * 10.0
                    + 0.1 * sin(5.0);

    EXPECT_NEAR(y, expected, 1e-9);
}

TEST(TemperatureModelTest, NonlinearMultipleSteps) {
    TemperatureModel model(0.7, 0.01, 0.3, 0.1);
    model.setInitialConditions(20.0, 19.5, 5.0);

    model.calculateNext(10);
    model.calculateNext(15);
    EXPECT_NO_THROW(model.getCurrentTemperature());
}

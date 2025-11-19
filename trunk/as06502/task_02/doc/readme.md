
<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Грущинский Д.Д.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md) в соответствующей строке.

# Выполнение работы
## temperature_model.h  
```
#pragma once

class TemperatureModel {
public:
    static const int STEPS = 10;
    static const double A;
    static const double B; 
    static const double C;
    static const double D;

    // y(t) = A * y(t-1) + B * u(t)
    static double calcLinear(double currentY, double inputU);
    
    // y(t) = A * y(t-1) - B * y(t-1)^2 + C * u(t) + D * sin(u(t-1))
    static double calcNonlinear(double currentY, double prevY, double inputU, double prevU);
    
    static bool validateInput(double temperature);
    static bool validateInputArray(const double inputs[], int size);
    
    static void calculateLinearModel(double initialTemp, const double inputs[], int size, double results[]);
      
    static void calculateNonlinearModel(double initialTemp, const double inputs[], int size, double results[]);
};
```


## temperature_model.cpp
```
#include "temperature_model.h"
#include <cmath>
#include <stdexcept>

const double TemperatureModel::A = 0.2;
const double TemperatureModel::B = 0.02;
const double TemperatureModel::C = 0.03;
const double TemperatureModel::D = 0.04;


double TemperatureModel::calcLinear(double currentY, double inputU) {
    if (!validateInput(currentY) || !validateInput(inputU)) {
        throw std::invalid_argument("Invalid input parameters");
    }
    return (A * currentY) + (B * inputU);
}

double TemperatureModel::calcNonlinear(double currentY, double prevY, double inputU, double prevU) {
    if (!validateInput(currentY) || !validateInput(prevY) || 
        !validateInput(inputU) || !validateInput(prevU)) {
        throw std::invalid_argument("Invalid input parameters");
    }
    return (A * currentY) - (B * prevY * prevY) + (C * inputU) + D * sin(prevU);
}

bool TemperatureModel::validateInput(double temperature) {
    return !std::isnan(temperature) && 
           !std::isinf(temperature) &&
           temperature >= -100.0 && 
           temperature <= 1000.0;
}

bool TemperatureModel::validateInputArray(const double inputs[], int size) {
    if (size <= 0) return false;
    
    for (int i = 0; i < size; ++i) {
        if (!validateInput(inputs[i])) {
            return false;
        }
    }
    return true;
}

void TemperatureModel::calculateLinearModel(double initialTemp, const double inputs[], int size, double results[]) {
    if (!validateInput(initialTemp) || !validateInputArray(inputs, size) || size > STEPS) {
        throw std::invalid_argument("Invalid input parameters for linear model");
    }
    
    double prevTemperature = initialTemp;
    
    for (int t = 0; t < size; ++t) {
        results[t] = calcLinear(prevTemperature, inputs[t]);
        prevTemperature = results[t];
    }
}

void TemperatureModel::calculateNonlinearModel(double initialTemp, const double inputs[], int size, double results[]) {
    if (!validateInput(initialTemp) || !validateInputArray(inputs, size) || size > STEPS) {
        throw std::invalid_argument("Invalid input parameters for nonlinear model");
    }
    
    if (size < 2) {
        throw std::invalid_argument("Nonlinear model requires at least 2 steps");
    }
    
    double currentY = initialTemp;
    double previousY = initialTemp;
    results[0] = initialTemp; 
    
    for (int t = 1; t < size; ++t) {
        double uCurr = inputs[t];
        double uPrev = inputs[t-1];
        
        results[t] = calcNonlinear(currentY, previousY, uCurr, uPrev);
        previousY = currentY;
        currentY = results[t];
    }
}
```

## main.cpp
```
#include <iostream>
#include <cstdlib>
#include "temperature_model.h"

using namespace std;

void systemPause() {
    #ifdef _WIN32
        system("pause");
    #else
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    #endif
}


void setConsoleEncoding() {
    #ifdef _WIN32
        system("chcp 6501 > nul");
    #endif
}

int main() {
    setConsoleEncoding();

    double temperatureInitial = 20.0;

    double inputs[TemperatureModel::STEPS] = {
        15.0, 16.5, 18.0, 20.0, 22.5, 25.0, 24.0, 21.0, 18.0, 16.0
    };

    cout << "Линейная модель\nНачальное значение: " << temperatureInitial << "\n";

    try {
        double linearResults[TemperatureModel::STEPS];
        TemperatureModel::calculateLinearModel(temperatureInitial, inputs, TemperatureModel::STEPS, linearResults);
        
        for (int t = 0; t < TemperatureModel::STEPS; ++t) {
            cout << "y[" << t + 1 << "] = " << linearResults[t] << endl;
        }
    } catch (const exception& e) {
        cerr << "Ошибка в линейной модели: " << e.what() << endl;
        return 1;
    }

    cout << "\nНелинейная модель\nНачальное значение: " << temperatureInitial << "\n";

    try {
        double nonlinearResults[TemperatureModel::STEPS];
        TemperatureModel::calculateNonlinearModel(temperatureInitial, inputs, TemperatureModel::STEPS, nonlinearResults);
        
        for (int t = 0; t < TemperatureModel::STEPS; ++t) {
            cout << "y[" << t << "] = " << nonlinearResults[t] << endl;
        }
    } catch (const exception& e) {
        cerr << "Ошибка в нелинейной модели: " << e.what() << endl;
        return 1;
    }

    systemPause();
    return 0;
}
```

## test_temperature_model.cpp
```
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include "temperature_model.h"

class TemperatureModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        testInputs[0] = 15.0;
        testInputs[1] = 16.5;
        testInputs[2] = 18.0;
        initialTemp = 20.0;
    }
    
    double testInputs[3];
    double initialTemp;
};


TEST_F(TemperatureModelTest, LinearModelBasicCalculation) {
    double result = TemperatureModel::calcLinear(20.0, 15.0);
    EXPECT_NEAR(result, (0.2 * 20.0) + (0.02 * 15.0), 0.001);
}

TEST_F(TemperatureModelTest, LinearModelZeroInput) {
    double result = TemperatureModel::calcLinear(0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(TemperatureModelTest, LinearModelSequence) {
    double results[3];
    TemperatureModel::calculateLinearModel(initialTemp, testInputs, 3, results);
    
    double expected1 = (0.2 * 20.0) + (0.02 * 15.0);
    EXPECT_NEAR(results[0], expected1, 0.001);
    
    double expected2 = (0.2 * expected1) + (0.02 * 16.5);
    EXPECT_NEAR(results[1], expected2, 0.001);
}


TEST_F(TemperatureModelTest, NonlinearModelBasicCalculation) {
    double result = TemperatureModel::calcNonlinear(20.0, 20.0, 15.0, 14.0);
    
    double expected = (0.2 * 20.0) - (0.02 * 20.0 * 20.0) + 
                     (0.03 * 15.0) + (0.04 * sin(14.0));
    EXPECT_NEAR(result, expected, 0.001);
}

TEST_F(TemperatureModelTest, NonlinearModelSequence) {
    double results[3];
    double localInputs[3] = {10.0, 12.0, 14.0};
    
    TemperatureModel::calculateNonlinearModel(initialTemp, localInputs, 3, results);
    
    EXPECT_DOUBLE_EQ(results[0], initialTemp);
    
    EXPECT_TRUE(results[1] != initialTemp);
}

TEST_F(TemperatureModelTest, NonlinearModelWithExtremeValues) {
    double result = TemperatureModel::calcNonlinear(100.0, 100.0, 50.0, 50.0);
    EXPECT_FALSE(std::isnan(result));
    EXPECT_FALSE(std::isinf(result));
}

TEST_F(TemperatureModelTest, InputValidationValid) {
    EXPECT_TRUE(TemperatureModel::validateInput(20.0));
    EXPECT_TRUE(TemperatureModel::validateInput(0.0));
    EXPECT_TRUE(TemperatureModel::validateInput(-10.0));
    EXPECT_TRUE(TemperatureModel::validateInput(100.0));
}

TEST_F(TemperatureModelTest, InputValidationInvalid) {
    EXPECT_FALSE(TemperatureModel::validateInput(NAN));
    EXPECT_FALSE(TemperatureModel::validateInput(INFINITY));
    EXPECT_FALSE(TemperatureModel::validateInput(-INFINITY));
    EXPECT_FALSE(TemperatureModel::validateInput(-101.0)); 
    EXPECT_FALSE(TemperatureModel::validateInput(1001.0));
}

TEST_F(TemperatureModelTest, InputArrayValidation) {
    double validInputs[3] = {10.0, 20.0, 30.0};
    double invalidInputs[3] = {10.0, NAN, 30.0};
    
    EXPECT_TRUE(TemperatureModel::validateInputArray(validInputs, 3));
    EXPECT_FALSE(TemperatureModel::validateInputArray(invalidInputs, 3));
    EXPECT_FALSE(TemperatureModel::validateInputArray(validInputs, 0));
}


TEST_F(TemperatureModelTest, LinearModelInvalidInputThrows) {
    EXPECT_THROW(TemperatureModel::calcLinear(NAN, 10.0), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calcLinear(20.0, INFINITY), std::invalid_argument);
}

TEST_F(TemperatureModelTest, NonlinearModelInvalidInputThrows) {
    EXPECT_THROW(TemperatureModel::calcNonlinear(NAN, 20.0, 10.0, 10.0), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calcNonlinear(20.0, -101.0, 10.0, 10.0), std::invalid_argument);
}

TEST_F(TemperatureModelTest, ModelSequenceInvalidInputThrows) {
    double invalidInputs[3] = {10.0, NAN, 30.0};
    double results[3];
    
    EXPECT_THROW(TemperatureModel::calculateLinearModel(20.0, invalidInputs, 3, results), 
                 std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calculateNonlinearModel(20.0, invalidInputs, 3, results), 
                 std::invalid_argument);
}

TEST_F(TemperatureModelTest, NonlinearModelInsufficientStepsThrows) {
    double singleInput[1] = {10.0};
    double results[1];
    
    EXPECT_THROW(TemperatureModel::calculateNonlinearModel(20.0, singleInput, 1, results), 
                 std::invalid_argument);
}


TEST_F(TemperatureModelTest, ConstantsAreCorrect) {
    EXPECT_DOUBLE_EQ(TemperatureModel::A, 0.2);
    EXPECT_DOUBLE_EQ(TemperatureModel::B, 0.02);
    EXPECT_DOUBLE_EQ(TemperatureModel::C, 0.03);
    EXPECT_DOUBLE_EQ(TemperatureModel::D, 0.04);
}


TEST_F(TemperatureModelTest, BoundaryCases) {
    EXPECT_NO_THROW(TemperatureModel::calcLinear(1000.0, 1000.0));
    EXPECT_NO_THROW(TemperatureModel::calcLinear(-100.0, -100.0));
    
    EXPECT_THROW(TemperatureModel::calcLinear(1001.0, 10.0), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calcLinear(10.0, -101.0), std::invalid_argument);
}


TEST_F(TemperatureModelTest, MathematicalProperties) {
    double result1 = TemperatureModel::calcLinear(10.0, 5.0);
    double result2 = TemperatureModel::calcLinear(20.0, 10.0);
    
    EXPECT_NEAR(result2, 2 * result1, 1.0);
}


TEST_F(TemperatureModelTest, PerformanceNoCrash) {
    for (int i = 0; i < 100; ++i) {
        double temp = static_cast<double>(i);
        double input = static_cast<double>(i * 2);
        EXPECT_NO_THROW(TemperatureModel::calcLinear(temp, input));
    }
}
```

## test_main.cpp
```
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## CMakeLists.txt
```
cmake_minimum_required(VERSION 3.14)
project(TemperatureModel)

set(CMAKE_CXX_STANDARD 17)

# подкачка и юз googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_library(temperature_model src/temperature_model.cpp)
target_include_directories(temperature_model PUBLIC src)

add_executable(temperature_app src/main.cpp)
target_link_libraries(temperature_app temperature_model)

add_executable(temperature_tests test/test_temperature_model.cpp test/test_main.cpp)
target_link_libraries(temperature_tests PRIVATE temperature_model gtest_main)

include(GoogleTest)
gtest_discover_tests(temperature_tests)

# библиотека для coverage
add_library(temperature_model_coverage src/temperature_model.cpp)
target_include_directories(temperature_model_coverage PUBLIC src)
target_compile_options(temperature_model_coverage PRIVATE -fprofile-arcs -ftest-coverage)

# тесты с покрытием
add_executable(temperature_tests_coverage test/test_temperature_model.cpp test/test_main.cpp)
target_link_libraries(temperature_tests_coverage PRIVATE temperature_model_coverage gtest_main -lgcov)

# цель для coverage с правильными фильтрами
add_custom_target(coverage
    COMMAND ./temperature_tests_coverage
    COMMAND gcovr --print-summary --exclude=".*googletest.*" --exclude=".*test.*" --root=..
    COMMAND gcovr --html-nested -o coverage_report.html --exclude=".*googletest.*" --exclude=".*test.*" --root=..
    DEPENDS temperature_tests_coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running coverage analysis for project files only"
)
```

# Вывод тестов программы
```
[==========] Running 17 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 17 tests from TemperatureModelTest
[ RUN      ] TemperatureModelTest.LinearModelBasicCalculation
[       OK ] TemperatureModelTest.LinearModelBasicCalculation (0 ms)
[ RUN      ] TemperatureModelTest.LinearModelZeroInput
[       OK ] TemperatureModelTest.LinearModelZeroInput (0 ms)
[ RUN      ] TemperatureModelTest.LinearModelSequence
[       OK ] TemperatureModelTest.LinearModelSequence (0 ms)
[ RUN      ] TemperatureModelTest.NonlinearModelBasicCalculation
[       OK ] TemperatureModelTest.NonlinearModelBasicCalculation (9 ms)
[ RUN      ] TemperatureModelTest.NonlinearModelSequence
[       OK ] TemperatureModelTest.NonlinearModelSequence (0 ms)
[ RUN      ] TemperatureModelTest.NonlinearModelWithExtremeValues
[       OK ] TemperatureModelTest.NonlinearModelWithExtremeValues (0 ms)
[ RUN      ] TemperatureModelTest.InputValidationValid
[       OK ] TemperatureModelTest.InputValidationValid (0 ms)
[ RUN      ] TemperatureModelTest.InputValidationInvalid
[       OK ] TemperatureModelTest.InputValidationInvalid (0 ms)
[ RUN      ] TemperatureModelTest.InputArrayValidation
[       OK ] TemperatureModelTest.InputArrayValidation (0 ms)
[ RUN      ] TemperatureModelTest.LinearModelInvalidInputThrows
[       OK ] TemperatureModelTest.LinearModelInvalidInputThrows (1 ms)
[ RUN      ] TemperatureModelTest.NonlinearModelInvalidInputThrows
[       OK ] TemperatureModelTest.NonlinearModelInvalidInputThrows (0 ms)
[ RUN      ] TemperatureModelTest.ModelSequenceInvalidInputThrows
[       OK ] TemperatureModelTest.ModelSequenceInvalidInputThrows (0 ms)
[ RUN      ] TemperatureModelTest.NonlinearModelInsufficientStepsThrows
[       OK ] TemperatureModelTest.NonlinearModelInsufficientStepsThrows (0 ms)
[ RUN      ] TemperatureModelTest.ConstantsAreCorrect
[       OK ] TemperatureModelTest.ConstantsAreCorrect (0 ms)
[ RUN      ] TemperatureModelTest.BoundaryCases
[       OK ] TemperatureModelTest.BoundaryCases (0 ms)
[ RUN      ] TemperatureModelTest.MathematicalProperties
[       OK ] TemperatureModelTest.MathematicalProperties (0 ms)
[ RUN      ] TemperatureModelTest.PerformanceNoCrash
[       OK ] TemperatureModelTest.PerformanceNoCrash (0 ms)
[----------] 17 tests from TemperatureModelTest (11 ms total)

[----------] Global test environment tear-down
[==========] 17 tests from 1 test suite ran. (11 ms total)
[  PASSED  ] 17 tests.
libgcov profiling error:/mnt/c/Development/TMAU/1/TMAU-2025/trunk/as06502/task_02/build/CMakeFiles/temperature_model_coverage.dir/src/temperature_model.cpp.gcda:overwriting an existing profile data with a different checksum
(INFO) Reading coverage data...
(INFO) Writing coverage report...
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: ..
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
src/temperature_model.cpp                     43      43   100%
------------------------------------------------------------------------------
TOTAL                                         43      43   100%
------------------------------------------------------------------------------
lines: 100.0% (43 out of 43)
functions: 100.0% (6 out of 6)
branches: 82.3% (51 out of 62)
```

**Вывод:** В ходе данной лабораторной работы были усвоены и опробованы инструменты модульного тестирования googletest, а также инструменты анализа покрытия тестов gcovr.



<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“ Брестский Государственный Технический университет ”</p>
<p align="center">Кафедра интеллектуальных информационных технологий</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студентка 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Рапин Е. Ю.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
# Общее задание #
Написать модульные тесты для программы, которая была разработана в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test].
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами.
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`] в соответствующей строке.

# Выполнение работы
## temperature_model.h  
```
#pragma once
#include <vector>

class TemperatureModel {
private:
    double a;
    double b; 
    double c;
    double d;
    double startTemp;
    std::vector<double> heatInput;
    std::vector<double> linearResults;
    std::vector<double> nonlinearResults;
    bool verbose; // Флаг для управления выводом

public:
    TemperatureModel(double a_val, double b_val, double c_val, double d_val,
                    double temp, const std::vector<double>& inputs, bool verbose_mode = true);

    void runLinear();
    void runNonlinear();
    
    // Методы для доступа к результатам (для тестирования)
    const std::vector<double>& getLinearResults() const { return linearResults; }
    const std::vector<double>& getNonlinearResults() const { return nonlinearResults; }
    void setVerbose(bool verbose_mode) { verbose = verbose_mode; }
};
```


## temperature_model.cpp
```
#include "temperature_model.h"
#include <iostream>
#include <cmath>

using namespace std;

TemperatureModel::TemperatureModel(double a_val, double b_val, double c_val, double d_val,
                    double temp, const std::vector<double>& inputs, bool verbose_mode)
    : a(a_val), b(b_val), c(c_val), d(d_val), startTemp(temp), 
      heatInput(inputs), verbose(verbose_mode) {
    linearResults.clear();
    nonlinearResults.clear();
}

void TemperatureModel::runLinear() {
    linearResults.clear();
    if (verbose) {
        cout << "Linear model results:" << endl;
    }
    double current = startTemp;

    for (size_t i = 0; i < heatInput.size(); i++) {
        current = a * current + b * heatInput[i];
        linearResults.push_back(current);
        if (verbose) {
            cout << "Y" << i + 1 << ": " << current << endl;
        }
    }
}

void TemperatureModel::runNonlinear() {
    nonlinearResults.clear();
    if (verbose) {
        cout << "\nResults of the nonlinear model:" << endl;
    }
    double prev = startTemp;
    double current = startTemp;

    for (size_t i = 0; i < heatInput.size(); i++) {
        double prevHeat = (i > 0) ? heatInput[i - 1] : 0;
        double next = a * current - b * prev + c * heatInput[i] + d * sin(prevHeat);
        nonlinearResults.push_back(next);
        if (verbose) {
            cout << "Y" << i + 1 << ": " << next << endl;
        }
        prev = current;
        current = next;
    }
}
```

## main.cpp
```
#include <iostream>
#include <vector>
#include "temperature_model.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    vector<double> inputs = {3, 4, 5, 6, 7, 8, 9, 10, 9, 8};

    TemperatureModel model(0.7, 0.3, 0.05, 0.01, 20.0, inputs);

    model.runLinear();
    model.runNonlinear();

    return 0;
}
```

## test_temperature_model.cpp
```
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <limits>
#include "../src/temperature_model.h"

class TemperatureModelTest : public ::testing::Test {
private:
    std::vector<double> testInputs;

protected:
    void SetUp() override {
        testInputs = {3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 9.0, 8.0};
    }
    
    const std::vector<double>& getTestInputs() const { return testInputs; }
    
    
    TemperatureModel createSilentModel(double a = 0.7, double b = 0.3, double c = 0.05, 
                                      double d = 0.01, double temp = 20.0, 
                                      const std::vector<double>& inputs = {}) {
        if (inputs.empty()) {
            return TemperatureModel(a, b, c, d, temp, getTestInputs(), false);
        }
        return TemperatureModel(a, b, c, d, temp, inputs, false);
    }
    
    
    void CheckResultsValid(const std::vector<double>& results) {
        for (const auto& value : results) {
            EXPECT_FALSE(std::isnan(value)) << "Found NaN in results";
            EXPECT_FALSE(std::isinf(value)) << "Found infinity in results";
        }
    }
};

TEST_F(TemperatureModelTest, ConstructorInitialization) {
    TemperatureModel model = createSilentModel();
    
    
    EXPECT_TRUE(model.getLinearResults().empty());
    EXPECT_TRUE(model.getNonlinearResults().empty());
}

TEST_F(TemperatureModelTest, RunLinearModelOutput) {
    TemperatureModel model = createSilentModel();
    model.runLinear();
    
    auto results = model.getLinearResults();
    
    
    EXPECT_EQ(results.size(), getTestInputs().size());
    
    
    CheckResultsValid(results);
    
    
    for (const auto& value : results) {
        EXPECT_GT(value, -10000.0);
        EXPECT_LT(value, 10000.0);
    }
}

TEST_F(TemperatureModelTest, RunNonlinearModelOutput) {
    TemperatureModel model = createSilentModel();
    model.runNonlinear();
    
    auto results = model.getNonlinearResults();
    
    EXPECT_EQ(results.size(), getTestInputs().size());
    CheckResultsValid(results);
    
    for (const auto& value : results) {
        EXPECT_GT(value, -10000.0);
        EXPECT_LT(value, 10000.0);
    }
}


TEST_F(TemperatureModelTest, SingleElementInput) {
    std::vector<double> singleInput = {5.0};
    TemperatureModel model = createSilentModel(0.7, 0.3, 0.05, 0.01, 20.0, singleInput);
    
    model.runLinear();
    model.runNonlinear();
    
    
    EXPECT_EQ(model.getLinearResults().size(), 1);
    EXPECT_EQ(model.getNonlinearResults().size(), 1);
    
    
    CheckResultsValid(model.getLinearResults());
    CheckResultsValid(model.getNonlinearResults());
}

TEST_F(TemperatureModelTest, MathematicalConsistencyLinear) {
    
    std::vector<double> inputs = {1.0, 2.0};
    TemperatureModel model = createSilentModel(0.5, 0.5, 0.0, 0.0, 1.0, inputs);
    
    model.runLinear();
    auto results = model.getLinearResults();
    
    
    
    ASSERT_EQ(results.size(), 2);
    EXPECT_NEAR(results[0], 1.0, 0.001);
    EXPECT_NEAR(results[1], 1.5, 0.001);
}

TEST_F(TemperatureModelTest, MathematicalConsistencyNonlinear) {
    
    std::vector<double> inputs = {1.0};
    TemperatureModel model = createSilentModel(1.0, 0.0, 1.0, 0.0, 0.0, inputs); 
    
    model.runNonlinear();
    auto results = model.getNonlinearResults();
    
    
    
    ASSERT_EQ(results.size(), 1);
    EXPECT_NEAR(results[0], 1.0, 0.001);
}

TEST_F(TemperatureModelTest, CompareLinearAndNonlinear) {
    TemperatureModel model = createSilentModel();
    
    model.runLinear();
    model.runNonlinear();
    
    auto linearResults = model.getLinearResults();
    auto nonlinearResults = model.getNonlinearResults();
    
    ASSERT_EQ(linearResults.size(), nonlinearResults.size());
    
    
    bool resultsDiffer = false;
    for (size_t i = 0; i < linearResults.size(); ++i) {
        if (std::abs(linearResults[i] - nonlinearResults[i]) > 0.001) {
            resultsDiffer = true;
            break;
        }
    }
    EXPECT_TRUE(resultsDiffer) << "Linear and nonlinear models should produce different results";
}

TEST_F(TemperatureModelTest, RepeatedModelUsageConsistency) {
    TemperatureModel model = createSilentModel();
    
    
    model.runLinear();
    model.runNonlinear();
    auto firstLinear = model.getLinearResults();
    auto firstNonlinear = model.getNonlinearResults();
    
    
    model.runLinear();
    model.runNonlinear();
    auto secondLinear = model.getLinearResults();
    auto secondNonlinear = model.getNonlinearResults();
    
    
    ASSERT_EQ(firstLinear.size(), secondLinear.size());
    ASSERT_EQ(firstNonlinear.size(), secondNonlinear.size());
    
    for (size_t i = 0; i < firstLinear.size(); ++i) {
        EXPECT_NEAR(firstLinear[i], secondLinear[i], 0.001);
        EXPECT_NEAR(firstNonlinear[i], secondNonlinear[i], 0.001);
    }
}

TEST_F(TemperatureModelTest, SensitivityToCoefficients) {
    std::vector<double> inputs = {1.0, 2.0};
    
    
    TemperatureModel model1 = createSilentModel(0.7, 0.3, 0.05, 0.01, 10.0, inputs);
    TemperatureModel model2 = createSilentModel(0.8, 0.2, 0.05, 0.01, 10.0, inputs);
    
    model1.runLinear();
    model2.runLinear();
    
    auto results1 = model1.getLinearResults();
    auto results2 = model2.getLinearResults();
    
    ASSERT_EQ(results1.size(), results2.size());
    
    
    bool resultsDiffer = false;
    for (size_t i = 0; i < results1.size(); ++i) {
        if (std::abs(results1[i] - results2[i]) > 0.001) {
            resultsDiffer = true;
            break;
        }
    }
    EXPECT_TRUE(resultsDiffer) << "Results should differ with different coefficients";
}

TEST_F(TemperatureModelTest, BoundaryTemperatureValues) {
    std::vector<double> inputs = {1.0, 2.0};
    
    
    TemperatureModel model1 = createSilentModel(0.7, 0.3, 0.05, 0.01, 0.0, inputs);     
    TemperatureModel model2 = createSilentModel(0.7, 0.3, 0.05, 0.01, -100.0, inputs);  
    TemperatureModel model3 = createSilentModel(0.7, 0.3, 0.05, 0.01, 1000.0, inputs);  
    
    EXPECT_NO_THROW(model1.runLinear());
    EXPECT_NO_THROW(model2.runLinear());
    EXPECT_NO_THROW(model3.runLinear());
    
    EXPECT_NO_THROW(model1.runNonlinear());
    EXPECT_NO_THROW(model2.runNonlinear());
    EXPECT_NO_THROW(model3.runNonlinear());
    
    
    CheckResultsValid(model1.getLinearResults());
    CheckResultsValid(model2.getLinearResults());
    CheckResultsValid(model3.getLinearResults());
}

TEST_F(TemperatureModelTest, ExtremeCoefficientValues) {
    std::vector<double> inputs = {1.0, 2.0};
    
    
    TemperatureModel model1 = createSilentModel(0.0, 1.0, 0.0, 0.0, 10.0, inputs);  
    TemperatureModel model2 = createSilentModel(1.0, 0.0, 0.0, 0.0, 10.0, inputs);  
    TemperatureModel model3 = createSilentModel(2.0, 1.0, 0.0, 0.0, 10.0, inputs);  
    
    EXPECT_NO_THROW(model1.runLinear());
    EXPECT_NO_THROW(model2.runLinear());
    EXPECT_NO_THROW(model3.runLinear());
    
    
    CheckResultsValid(model1.getLinearResults());
    CheckResultsValid(model2.getLinearResults());
    CheckResultsValid(model3.getLinearResults());
}

TEST_F(TemperatureModelTest, PerformanceAndStability) {
    
    std::vector<double> largeInputs(100, 1.0); 
    
    TemperatureModel model = createSilentModel(0.7, 0.3, 0.05, 0.01, 20.0, largeInputs);
    
    for (int i = 0; i < 10; ++i) {
        EXPECT_NO_THROW(model.runLinear());
        EXPECT_NO_THROW(model.runNonlinear());
        
        auto linearResults = model.getLinearResults();
        auto nonlinearResults = model.getNonlinearResults();
        
        EXPECT_EQ(linearResults.size(), largeInputs.size());
        EXPECT_EQ(nonlinearResults.size(), largeInputs.size());
        
        CheckResultsValid(linearResults);
        CheckResultsValid(nonlinearResults);
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

# Включение GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Основная библиотека
add_library(temperature_model temperature_model.cpp)
target_include_directories(temperature_model PUBLIC .)

# Основное приложение
add_executable(temperature_app main.cpp)
target_link_libraries(temperature_app temperature_model)

# Тесты
add_executable(temperature_tests 
    ../test/test_temperature_model.cpp
    ../test/test_main.cpp
)
target_link_libraries(temperature_tests 
    PRIVATE temperature_model 
    gtest_main
)
target_include_directories(temperature_tests PRIVATE . ../test)

include(GoogleTest)
gtest_discover_tests(temperature_tests)

# Coverage библиотека
add_library(temperature_model_coverage temperature_model.cpp)
target_include_directories(temperature_model_coverage PUBLIC .)
target_compile_options(temperature_model_coverage PRIVATE -fprofile-arcs -ftest-coverage)

# Тесты с покрытием
add_executable(temperature_tests_coverage 
    ../test/test_temperature_model.cpp
    ../test/test_main.cpp
)
target_compile_options(temperature_tests_coverage PRIVATE -fprofile-arcs -ftest-coverage)
target_link_libraries(temperature_tests_coverage 
    PRIVATE temperature_model_coverage 
    gtest_main
    gcov  # Добавляем явную линковку с gcov
)
target_include_directories(temperature_tests_coverage PRIVATE . ../test)

# Цель для coverage анализа
find_program(GCOVR_PATH gcovr)

if(GCOVR_PATH)
    add_custom_target(coverage
        COMMAND ./temperature_tests_coverage
        COMMAND ${GCOVR_PATH} --print-summary --exclude=".*googletest.*" --exclude=".*test.*" --root=${CMAKE_SOURCE_DIR}
        COMMAND ${GCOVR_PATH} --html-nested -o coverage_report.html --exclude=".*googletest.*" --exclude=".*test.*" --root=${CMAKE_SOURCE_DIR}
        DEPENDS temperature_tests_coverage
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running coverage analysis for project files only"
    )
else()
    message(WARNING "gcovr not found, coverage target will not be available")
endif()

# Цель для запуска тестов с покрытием
add_custom_target(run_coverage_tests
    COMMAND ./temperature_tests_coverage
    DEPENDS temperature_tests_coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests with coverage instrumentation"
)
```

# Вывод тестов программы
```
dadjil@Dadjil:/mnt/c/Development/RapinTMAU/task_02$ ./run_tests.sh 
Temperature Model Tests
Configuring and building project...
CMake Deprecation Warning at build/_deps/googletest-src/CMakeLists.txt:4 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


CMake Deprecation Warning at build/_deps/googletest-src/googlemock/CMakeLists.txt:39 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


CMake Deprecation Warning at build/_deps/googletest-src/googletest/CMakeLists.txt:49 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- Configuring done (3.1s)
-- Generating done (2.6s)
-- Build files have been written to: /mnt/c/Development/RapinTMAU/task_02/src/build
[ 20%] Built target temperature_model
[ 20%] Built target temperature_model_coverage
[ 30%] Built target temperature_app
[ 40%] Built target gtest
[ 50%] Built target gtest_main
[ 60%] Built target gmock
[ 70%] Building CXX object CMakeFiles/temperature_tests.dir/mnt/c/Development/RapinTMAU/task_02/test/test_temperature_model.cpp.o
[ 70%] Building CXX object CMakeFiles/temperature_tests_coverage.dir/mnt/c/Development/RapinTMAU/task_02/test/test_temperature_model.cpp.o
[ 80%] Built target gmock_main
[ 85%] Linking CXX executable temperature_tests
[ 90%] Built target temperature_tests
[ 95%] Linking CXX executable temperature_tests_coverage
[100%] Built target temperature_tests_coverage

RUNNING TESTS
[==========] Running 12 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 12 tests from TemperatureModelTest
[ RUN      ] TemperatureModelTest.ConstructorInitialization
[       OK ] TemperatureModelTest.ConstructorInitialization (0 ms)
[ RUN      ] TemperatureModelTest.RunLinearModelOutput
[       OK ] TemperatureModelTest.RunLinearModelOutput (0 ms)
[ RUN      ] TemperatureModelTest.RunNonlinearModelOutput
[       OK ] TemperatureModelTest.RunNonlinearModelOutput (0 ms)
[ RUN      ] TemperatureModelTest.SingleElementInput
[       OK ] TemperatureModelTest.SingleElementInput (0 ms)
[ RUN      ] TemperatureModelTest.MathematicalConsistencyLinear
[       OK ] TemperatureModelTest.MathematicalConsistencyLinear (0 ms)
[ RUN      ] TemperatureModelTest.MathematicalConsistencyNonlinear
[       OK ] TemperatureModelTest.MathematicalConsistencyNonlinear (0 ms)
[ RUN      ] TemperatureModelTest.CompareLinearAndNonlinear
[       OK ] TemperatureModelTest.CompareLinearAndNonlinear (0 ms)
[ RUN      ] TemperatureModelTest.RepeatedModelUsageConsistency
[       OK ] TemperatureModelTest.RepeatedModelUsageConsistency (0 ms)
[ RUN      ] TemperatureModelTest.SensitivityToCoefficients
[       OK ] TemperatureModelTest.SensitivityToCoefficients (0 ms)
[ RUN      ] TemperatureModelTest.BoundaryTemperatureValues
[       OK ] TemperatureModelTest.BoundaryTemperatureValues (0 ms)
[ RUN      ] TemperatureModelTest.ExtremeCoefficientValues
[       OK ] TemperatureModelTest.ExtremeCoefficientValues (0 ms)
[ RUN      ] TemperatureModelTest.PerformanceAndStability
[       OK ] TemperatureModelTest.PerformanceAndStability (0 ms)
[----------] 12 tests from TemperatureModelTest (0 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 12 tests.

TESTS COMPLETED
```
# Вывод покрытия тестов
```
(INFO) Reading coverage data...
(INFO) Writing coverage report...
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: ..
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
temperature_model.cpp                         33      29    87%   18,26,34,44
temperature_model.h                            2       2   100%
------------------------------------------------------------------------------
TOTAL                                         35      31    88%
------------------------------------------------------------------------------
lines: 88.6% (31 out of 35)
functions: 100.0% (5 out of 5)
branches: 28.6% (12 out of 42)
(INFO) Reading coverage data...
(INFO) Writing coverage report...
[100%] Built target coverage

**Вывод:** В ходе лабораторной работы изучила и использовала инструменты модульного тестирования googletest, а также инструменты анализа покрытия тестов gcovr.


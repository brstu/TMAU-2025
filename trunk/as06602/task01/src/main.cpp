#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

/**
 * @class TemperatureModel
 * @brief A model for simulating temperature dynamics using linear and nonlinear approaches.
 *
 * This class generates control signals, calculates temperature responses based on linear and nonlinear models,
 * and provides methods for printing results to console and saving to file.
 */
class TemperatureModel {
private:
    double a;
    double b;
    double c;
    double d;
    double roomTemp;  // Y0 -> roomTemp
    double initialTemp;  // y0 -> initialTemp
    std::vector<double> linear_temps;
    std::vector<double> nonlinear_temps;
    std::vector<double> control_signals;

    // Constants for control signal generation (moved from magic numbers)
    static constexpr double BASE_SIGNAL = 10.0;
    static constexpr double AMPLITUDE = 5.0;
    static constexpr double FREQUENCY = 0.1;
    
public:
    /**
     * @brief Constructor for TemperatureModel.
     * @param a_val Coefficient for linear model.
     * @param b_val Coefficient for linear model.
     * @param c_val Coefficient for nonlinear model.
     * @param d_val Coefficient for nonlinear model.
     * @param room_temp Room temperature value.
     * @param init_temp Initial temperature value.
     */
    explicit TemperatureModel(double a_val = 0.98, double b_val = 0.05,
                     double c_val = 0.03, double d_val = 0.02,
                     double room_temp = 25.0, double init_temp = 20.0)
        : a(a_val), b(b_val), c(c_val), d(d_val),
          roomTemp(room_temp), initialTemp(init_temp) {}
    
    /**
     * @brief Generates control signals using a sinusoidal function.
     * @param step The current step number.
     * @return The control signal value at the given step.
     */
    double generateControlSignal(int step) const {
        return BASE_SIGNAL + AMPLITUDE * sin(FREQUENCY * step);
    }
    
    /**
     * @brief Calculates linear temperature response.
     * @param steps Number of simulation steps.
     *
     * Computes linear temperature dynamics: y[k+1] = a * y[k] + b * u[k].
     */
    void calculateLinear(int steps) {
        linear_temps.clear();
        control_signals.clear();
        
        double y_current = initialTemp;
        linear_temps.push_back(y_current);
        
        for (int tau = 0; tau < steps; tau++) {
            double u = generateControlSignal(tau);
            control_signals.push_back(u);
            y_current = a * y_current + b * u;
            linear_temps.push_back(y_current);
        }
    }
    
    /**
     * @brief Calculates nonlinear temperature response.
     * @param steps Number of simulation steps.
     *
     * Computes nonlinear temperature dynamics: y[k+1] = a * y[k] - b * y[k-1]^2 + c * u[k] + d * sin(u[k-1]).
     */
    void calculateNonlinear(int steps) {
        nonlinear_temps.clear();
        
        double y_prev2 = initialTemp;
        double y_prev1 = initialTemp;
        nonlinear_temps.push_back(y_prev1);
        
        double u_prev = 0.0;
        
        for (int tau = 0; tau < steps; tau++) {
            double u_current = (tau < control_signals.size()) ?
                              control_signals[tau] :
                              generateControlSignal(tau);
            
            double y_current = a * y_prev1 - b * pow(y_prev2, 2) +
                             c * u_current + d * sin(u_prev);
            
            nonlinear_temps.push_back(y_current);
            u_prev = u_current;
            y_prev2 = y_prev1;
            y_prev1 = y_current;
        }
    }
    
    /**
     * @brief Prints simulation results to console.
     *
     * Safely accesses vectors with bounds checks to avoid out-of-bounds errors.
     */
    void printResults() const {
        std::cout << "=============================================\n";
        std::cout << "Результаты моделирования объекта управления\n";
        std::cout << "=============================================\n";
        std::cout << std::setw(6) << "Шаг"
                  << std::setw(12) << "u(τ)"
                  << std::setw(16) << "Линейная"
                  << std::setw(16) << "Нелинейная" << std::endl;
        std::cout << "---------------------------------------------\n";
        
        for (size_t i = 0; i < linear_temps.size(); i++) {
            std::cout << std::setw(6) << i
                      << std::setw(12) << std::fixed << std::setprecision(2)
                      << ((i < control_signals.size()) ? control_signals[i] : 0.0)
                      << std::setw(16) << std::fixed << std::setprecision(2)
                      << linear_temps[i]
                      << std::setw(16) << std::fixed << std::setprecision(2)
                      << (i < nonlinear_temps.size() ? nonlinear_temps[i] : 0.0)  // Bounds check
                      << std::endl;
        }
    }
    
    /**
     * @brief Saves simulation results to a CSV file.
     * @param filename Name of the output file.
     *
     * Safely accesses vectors with bounds checks to avoid out-of-bounds errors.
     */
    void saveToFile(const std::string& filename) const {
        std::ofstream outfile(filename);
        if (!outfile) {
            std::cerr << "Ошибка открытия файла для записи!" << std::endl;
            return;
        }
        
        outfile << "Step,u(tau),Linear_Model,Nonlinear_Model\n";
        for (size_t i = 0; i < linear_temps.size(); i++) {
            outfile << i << ","
                    << ((i < control_signals.size()) ? control_signals[i] : 0.0) << ","
                    << linear_temps[i] << ","
                    << (i < nonlinear_temps.size() ? nonlinear_temps[i] : 0.0)  // Bounds check
                    << "\n";
        }
        
        outfile.close();
        std::cout << "\nРезультаты сохранены в файл: " << filename << std::endl;
    }
    
    /**
     * @brief Prints simulation statistics.
     *
     * Displays initial conditions, final temperatures, and differences.
     */
    void printStatistics() const {
        if (linear_temps.empty() || nonlinear_temps.empty()) {
            std::cout << "Нет данных для анализа!" << std::endl;
            return;
        }
        
        double linear_final = linear_temps.back();
        double nonlinear_final = nonlinear_temps.back();
        
        std::cout << "\n=============================================\n";
        std::cout << "Статистика моделирования:\n";
        std::cout << "=============================================\n";
        std::cout << "Температура помещения (Y₀): " << roomTemp << "°C\n";
        std::cout << "Начальная температура: " << initialTemp << "°C\n";
        std::cout << "Установившаяся температура (линейная модель): "
                  << linear_final << "°C\n";
        std::cout << "Установившаяся температура (нелинейная модель): "
                  << nonlinear_final << "°C\n";
        std::cout << "Разница между моделями: "
                  << std::abs(linear_final - nonlinear_final) << "°C\n";
    }
};

int main() {
    // More robust locale handling: try UTF-8, fallback to Russian, then default
    if (setlocale(LC_ALL, "ru_RU.UTF-8") == nullptr && setlocale(LC_ALL, "Russian") == nullptr) {
        std::cerr << "Warning: Locale not supported, using default." << std::endl;
        setlocale(LC_ALL, "");
    }
    
    std::cout << "Лабораторная работа №1: Моделирование объекта управления\n";
    std::cout << "========================================================\n\n";
    
    TemperatureModel model(0.98, 0.05, 0.03, 0.02, 25.0, 20.0);
    
    int simulation_steps = 100;
    
    std::cout << "Выполняется расчет по линейной модели...\n";
    model.calculateLinear(simulation_steps);
    
    std::cout << "Выполняется расчет по нелинейной модели...\n";
    model.calculateNonlinear(simulation_steps);
    
    model.printResults();
    model.printStatistics();
    model.saveToFile("simulation_results.csv");
    
    std::cout << "\n=============================================\n";
    std::cout << "Информация для анализа:\n";
    std::cout << "=============================================\n";
    std::cout << "Для построения графиков используйте данные из файла simulation_results.csv\n";
    std::cout << "Рекомендуемые инструменты:\n";
    std::cout << "1. Microsoft Excel\n";
    std::cout << "2. Python с библиотеками matplotlib/pandas\n";
    std::cout << "3. GNUPlot\n";
    
    return 0;
}
#pragma once
#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>

namespace input {

    
    inline void checkText(const std::string& value) {
        if (value.find_first_not_of(" \t\r\n") == std::string::npos) {
            throw std::invalid_argument(
                "Значение не должно быть пустым."
            );
        }
    }

    
    inline std::string text(const std::string& message) {
        std::cout << message;

        std::string value;

        if (!std::getline(std::cin, value)) {
            throw std::runtime_error(
                "Не удалось прочитать введённые данные."
            );
        }

        checkText(value);

        return value;
    }

    
    inline void checkNumber(double value, bool positive = false) {
        if (!std::isfinite(value)) {
            throw std::invalid_argument(
                "Число должно быть конечным."
            );
        }

        if (positive ? value <= 0 : value < 0) {
            throw std::invalid_argument(
                positive
                ? "Число должно быть больше нуля."
                : "Число не должно быть отрицательным."
            );
        }
    }

   
    template <typename T>
    T number(const std::string& message) {
        std::string line = text(message);
        std::istringstream stream(line);

        T value{};

        if (!(stream >> value)) {
            throw std::invalid_argument(
                "Введите корректное число."
            );
        }

        
        stream >> std::ws;

        
        if (!stream.eof()) {
            throw std::invalid_argument(
                "После числа обнаружены лишние символы."
            );
        }

        if (!std::isfinite(static_cast<double>(value))) {
            throw std::invalid_argument(
                "Число должно быть конечным."
            );
        }

        return value;
    }

}
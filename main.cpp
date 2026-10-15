#include <iostream>
#include <memory>
#include <stdexcept>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "Keeper.h"
#include "Furniture.h"
#include "Worker.h"
#include "Car.h"
#include "Input.h"

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    Keeper keeper;

    while (true) {
        try {
            std::cout
                << "\n========== ФАБРИКА ==========\n"
                << "1. Добавить объект\n"
                << "2. Показать все объекты\n"
                << "3. Изменить объект\n"
                << "4. Удалить объект\n"
                << "5. Сохранить в файл\n"
                << "6. Загрузить из файла\n"
                << "7. Скопировать объект\n"
                << "0. Выход\n";

            int command = input::number<int>("Ваш выбор: ");

            if (command == 0) {
                break;
            }

            switch (command) {
            case 1: {
                std::cout
                    << "\n1. Мебель\n"
                    << "2. Работник\n"
                    << "3. Машина\n";

                int type = input::number<int>(
                    "Выберите тип объекта: "
                );

                std::unique_ptr<Factory> object;

                switch (type) {
                case 1:
                    object.reset(new Furniture());
                    break;

                case 2:
                    object.reset(new Worker());
                    break;

                case 3:
                    object.reset(new Car());
                    break;

                default:
                    throw std::invalid_argument(
                        "Выберите тип от 1 до 3."
                    );
                }

                object->read();
                keeper += *object;

                std::cout << "Объект добавлен.\n";
                break;
            }

            case 2: {
                std::cout << keeper;
                break;
            }

            case 3: {
                int number = input::number<int>(
                    "Номер объекта для изменения: "
                );

                if (number < 1) {
                    throw std::out_of_range(
                        "Нумерация начинается с 1."
                    );
                }

                keeper[number - 1].read();

                std::cout << "Данные изменены.\n";
                break;
            }

            case 4: {
                int number = input::number<int>(
                    "Номер объекта для удаления: "
                );

                if (number < 1) {
                    throw std::out_of_range(
                        "Нумерация начинается с 1."
                    );
                }

                keeper.remove(number - 1);

                std::cout << "Объект удалён.\n";
                break;
            }

            case 5: {
                std::string filename = input::text(
                    "Введите имя файла для сохранения: "
                );

                keeper.save(filename);

                std::cout << "Данные сохранены.\n";
                break;
            }

            case 6: {
                std::string filename = input::text(
                    "Введите имя файла для загрузки: "
                );

                keeper.load(filename);

                std::cout << "Список восстановлен из файла.\n";
                break;
            }

            case 7: {
                int number = input::number<int>(
                    "Номер объекта для копирования: "
                );

                if (number < 1) {
                    throw std::out_of_range(
                        "Нумерация начинается с 1."
                    );
                }

                keeper += keeper[number - 1];

                std::cout << "Копия добавлена в список.\n";
                break;
            }

            default:
                throw std::invalid_argument(
                    "Выберите команду от 0 до 7."
                );
            }
        }
        catch (const std::exception& error) {
            std::cerr << "Ошибка: " << error.what() << '\n';

            if (std::cin.eof() || std::cin.bad()) {
                break;
            }
        }
    }

    return 0;
}
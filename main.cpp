#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

#include "Keeper.h"
#include "Furniture.h"
#include "Worker.h"
#include "Car.h"
#include "Input.h"

std::unique_ptr<Factory> createObject() {
    std::cout
        << "1. Мебель\n"
        << "2. Работник\n"
        << "3. Машина\n";

    int type = input::number<int>("Тип объекта: ");

    if (type == 1) {
        std::string name = input::text("Тип мебели: ");

        double height = input::number<double>("Высота (см): ");
        double width = input::number<double>("Ширина (см): ");
        double depth = input::number<double>("Глубина (см): ");

        std::string color = input::text("Цвет: ");
        std::string material = input::text("Материал: ");

        double cost = input::number<double>("Стоимость (руб.): ");

        input::checkNumber(height, true);
        input::checkNumber(width, true);
        input::checkNumber(depth, true);
        input::checkNumber(cost);

        return std::unique_ptr<Factory>(
            new Furniture(
                name,
                height,
                width,
                depth,
                color,
                material,
                cost
            )
        );
    }

    if (type == 2) {
        std::string name = input::text("ФИО: ");
        std::string position = input::text("Должность: ");

        double salary = input::number<double>(
            "Заработная плата (руб.): "
        );

        std::string address = input::text("Адрес проживания: ");
        std::string phone = input::text("Телефон: ");

        input::checkNumber(salary);

        return std::unique_ptr<Factory>(
            new Worker(name, position, salary, address, phone)
        );
    }

    if (type == 3) {
        std::string brand = input::text("Марка: ");
        std::string model = input::text("Модель: ");
        std::string plate = input::text("Госномер: ");

        return std::unique_ptr<Factory>(
            new Car(brand, model, plate)
        );
    }

    throw std::invalid_argument("Выберите тип от 1 до 3.");
}

// Преобразование номера пользователя в индекс.
int readIndex() {
    int number = input::number<int>("Номер объекта: ");

    if (number < 1) {
        throw std::out_of_range("Нумерация начинается с 1.");
    }

    return number - 1;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    Keeper keeper;

    while (true) {
        try {
            std::cout
                << "\nМЕНЮ\n"
                << "1. Добавить объект\n"
                << "2. Показать все объекты\n"
                << "3. Показать объект\n"
                << "4. Изменить объект\n"
                << "5. Удалить объект\n"
                << "6. Копировать объект\n"
                << "7. Сохранить в файл\n"
                << "8. Загрузить из файла (заменить список)\n"
                << "9. Показать количество объектов\n"
                << "0. Выход\n";

            int command = input::number<int>("Выбор: ");

            if (command == 0) {
                break;
            }

            switch (command) {
            case 1: {
                std::unique_ptr<Factory> object = createObject();

                keeper.addOwned(std::move(object));

                std::cout << "Объект успешно добавлен!\n";
                break;
            }

            case 2:
                std::cout << keeper;
                break;

            case 3: {
                int index = readIndex();

                std::cout << keeper[index];
                break;
            }

            case 4: {
                if (keeper.getSize() == 0) {
                    std::cout << "Список объектов пуст.\n";
                    break;
                }

                std::cout << keeper;

                int index = readIndex();
                keeper[index].read();

                std::cout << "Объект изменён.\n";
                break;
            }

            case 5: {
                if (keeper.getSize() == 0) {
                    std::cout << "Список объектов пуст.\n";
                    break;
                }

                std::cout << keeper;

                int index = readIndex();
                keeper.remove(index);

                std::cout << "Объект удалён.\n";
                break;
            }

            case 6: {
                if (keeper.getSize() == 0) {
                    std::cout << "Список объектов пуст.\n";
                    break;
                }

                std::cout << keeper;

                int index = readIndex();
                keeper += keeper[index];

                std::cout << "Копия добавлена.\n";
                break;
            }

            case 7: {
                std::string path = input::text(
                    "Имя файла для сохранения: "
                );

                keeper.save(path);

                std::cout << "Объекты сохранены в файл.\n";
                break;
            }

            case 8: {
                std::string path = input::text(
                    "Имя файла для загрузки: "
                );

                keeper.load(path);

                std::cout
                    << "Объекты загружены из файла.\n"
                    << "Объектов в основном хранилище: "
                    << keeper.getSize() << '\n';

                std::cout << keeper;
                break;
            }

            case 9:
                std::cout
                    << "Количество объектов: "
                    << keeper.getSize() << '\n';
                break;

            default:
                throw std::invalid_argument(
                    "Выберите команду от 0 до 9."
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

    std::cout << "Завершение программы.\n";
    return 0;
}
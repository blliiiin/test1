#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "Keeper.h"
#include "Furniture.h"
#include "Worker.h"
#include "Car.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cmath>

Keeper::Keeper() {
    std::cout << "Keeper: конструктор без параметров.\n";
}

Keeper::Keeper(const Factory& first) {
    add(first);
    std::cout << "Keeper: конструктор с параметрами.\n";
}

Keeper::Keeper(const Keeper& other) {
    try {
        for (Node* node = other.head_; node; node = node->next) {
            add(*node->item);
        }
    }
    catch (...) {
        clear();
        throw;
    }

    std::cout << "Keeper: конструктор копирования.\n";
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        Keeper copy(other);
        swap(copy);
    }

    return *this;
}

Keeper::~Keeper() {
    clear();
    std::cout << "Keeper: деструктор.\n";
}

void Keeper::swap(Keeper& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
}

int Keeper::getSize() const {
    return size_;
}

Keeper::Node* Keeper::nodeAt(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range(
            "Объекта с таким номером нет в списке."
        );
    }

    Node* node = head_;

    for (int i = 0; i < index; ++i) {
        node = node->next;
    }

    return node;
}

void Keeper::add(const Factory& item) {
    addOwned(std::unique_ptr<Factory>(item.clone()));
}

void Keeper::addOwned(std::unique_ptr<Factory> item) {
    if (!item) {
        throw std::invalid_argument(
            "Нельзя добавить пустой объект."
        );
    }

    Node* node = new Node{ item.get(), nullptr };
    item.release();

    if (!head_) {
        head_ = node;
    }
    else {
        Node* last = head_;

        while (last->next) {
            last = last->next;
        }

        last->next = node;
    }

    ++size_;
}

Keeper& Keeper::operator+=(const Factory& item) {
    add(item);
    return *this;
}

Factory& Keeper::operator[](int index) {
    return *nodeAt(index)->item;
}

const Factory& Keeper::operator[](int index) const {
    return *nodeAt(index)->item;
}

void Keeper::remove(int index) {
    Node* target = nodeAt(index);

    if (index == 0) {
        head_ = target->next;
    }
    else {
        nodeAt(index - 1)->next = target->next;
    }

    delete target->item;
    delete target;

    --size_;
}

void Keeper::clear() noexcept {
    while (head_) {
        Node* next = head_->next;

        delete head_->item;
        delete head_;

        head_ = next;
    }

    size_ = 0;
}

void Keeper::print(std::ostream& out) const {
    if (!head_) {
        out << "Список пуст.\n";
        return;
    }

    int number = 1;

    for (Node* node = head_; node; node = node->next) {
        out << "\n--- Объект № " << number++ << " ---\n";
        out << *node->item;
    }
}

// Вспомогательные функции чтения из файла.
namespace {
    std::string readField(std::istream& in) {
        std::string value;

        if (!std::getline(in, value)) {
            throw std::runtime_error(
                "В файле не хватает данных объекта."
            );
        }

        // Удаляем служебный символ переноса строки Windows.
        if (!value.empty() && value.back() == '\r') {
            value.pop_back();
        }

        return value;
    }

    double readNumber(std::istream& in) {
        std::istringstream line(readField(in));
        double value = 0;

        if (!(line >> value) || !std::isfinite(value)) {
            throw std::runtime_error(
                "В файле вместо числа указано неверное значение."
            );
        }

        line >> std::ws;

        if (!line.eof()) {
            throw std::runtime_error(
                "После числа в файле есть лишние символы."
            );
        }

        return value;
    }
}

void Keeper::save(const std::string& path) const {
    std::ofstream out(path);

    if (!out) {
        throw std::runtime_error(
            "Не удалось открыть файл для сохранения."
        );
    }

    out << std::setprecision(17);

    for (Node* node = head_; node; node = node->next) {
        const Factory& object = *node->item;

        if (const Furniture* item =
            dynamic_cast<const Furniture*>(&object)) {

            out << "Furniture\n"
                << item->getType() << '\n'
                << item->getHeight() << '\n'
                << item->getWidth() << '\n'
                << item->getDepth() << '\n'
                << item->getColor() << '\n'
                << item->getMaterial() << '\n'
                << item->getCost() << '\n';
        }
        else if (const Worker* item =
            dynamic_cast<const Worker*>(&object)) {

            out << "Worker\n"
                << item->getFullName() << '\n'
                << item->getPosition() << '\n'
                << item->getSalary() << '\n'
                << item->getAddress() << '\n'
                << item->getPhone() << '\n';
        }
        else if (const Car* item =
            dynamic_cast<const Car*>(&object)) {

            out << "Car\n"
                << item->getBrand() << '\n'
                << item->getModel() << '\n'
                << item->getPlate() << '\n';
        }
        else {
            throw std::runtime_error(
                "Неизвестный тип объекта."
            );
        }
    }

    out.close();

    if (!out) {
        throw std::runtime_error(
            "Ошибка записи данных в файл."
        );
    }
}

void Keeper::load(const std::string& path) {
    std::ifstream in(path);

    if (!in) {
        throw std::runtime_error(
            "Не удалось открыть файл для загрузки."
        );
    }

    Keeper temp;
    std::string type;
    bool firstLine = true;

    while (std::getline(in, type)) {
        // Поддержка UTF-8 как с BOM, так и без него.
        if (firstLine) {
            if (type.compare(0, 3, "\xEF\xBB\xBF") == 0) {
                type.erase(0, 3);
            }

            firstLine = false;
        }

        if (!type.empty() && type.back() == '\r') {
            type.pop_back();
        }

        // Между объектами разрешены пустые строки.
        if (type.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }

        std::unique_ptr<Factory> item;

        if (type == "Furniture") {
            std::string name = readField(in);
            double height = readNumber(in);
            double width = readNumber(in);
            double depth = readNumber(in);
            std::string color = readField(in);
            std::string material = readField(in);
            double cost = readNumber(in);

            item.reset(
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
        else if (type == "Worker") {
            std::string name = readField(in);
            std::string position = readField(in);
            double salary = readNumber(in);
            std::string address = readField(in);
            std::string phone = readField(in);

            item.reset(
                new Worker(name, position, salary, address, phone)
            );
        }
        else if (type == "Car") {
            std::string brand = readField(in);
            std::string model = readField(in);
            std::string plate = readField(in);

            item.reset(new Car(brand, model, plate));
        }
        else {
            throw std::runtime_error(
                "Неизвестный тип в файле: " + type
            );
        }

        temp.addOwned(std::move(item));
    }

    if (in.bad()) {
        throw std::runtime_error("Ошибка чтения файла.");
    }

    // Заменяем текущий список только после успешного чтения.
    swap(temp);
}

std::ostream& operator<<(std::ostream& out, const Keeper& keeper) {
    keeper.print(out);
    return out;
}
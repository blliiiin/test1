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

Keeper::Keeper() {
    std::cout << "[Keeper @ " << this
        << "] Конструктор без параметров\n";
}

Keeper::Keeper(const Factory& first) {
    add(first);

    std::cout << "[Keeper @ " << this
        << "] Конструктор с параметром\n";
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

    std::cout << "[Keeper @ " << this
        << "] Конструктор копирования\n";
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

    std::cout << "[Keeper @ " << this
        << "] Деструктор\n";
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
    std::unique_ptr<Factory> copy(item.clone());

    Node* node = new Node{ copy.get(), nullptr };
    copy.release();

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

void Keeper::save(const std::string& path) const {
    std::ofstream out(path);

    if (!out) {
        throw std::runtime_error(
            "Не удалось открыть файл для сохранения."
        );
    }

    out << "FACTORY_LAB6_V1\n";
    out << size_ << '\n';

    for (Node* node = head_; node; node = node->next) {
        out << node->item->kind() << '\n';
        node->item->save(out);
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

    std::string header;
    long long count = 0;

    if (!(in >> header >> count)
        || header != "FACTORY_LAB6_V1"
        || count < 0
        || count > 2147483647LL) {
        throw std::runtime_error(
            "Неверный заголовок файла или количество объектов."
        );
    }

    Keeper temp;

    for (long long i = 0; i < count; ++i) {
        std::string type;

        if (!(in >> type)) {
            throw std::runtime_error(
                "Не удалось прочитать тип объекта."
            );
        }

        std::unique_ptr<Factory> item;

        if (type == "Furniture") {
            item.reset(new Furniture());
        }
        else if (type == "Worker") {
            item.reset(new Worker());
        }
        else if (type == "Car") {
            item.reset(new Car());
        }
        else {
            throw std::runtime_error(
                "В файле указан неизвестный тип объекта."
            );
        }

        item->load(in);
        temp.add(*item);
    }

    in >> std::ws;

    if (!in.eof()) {
        throw std::runtime_error(
            "В конце файла обнаружены лишние данные."
        );
    }

    swap(temp);
}

std::ostream& operator<<(std::ostream& out, const Keeper& keeper) {
    keeper.print(out);
    return out;
}
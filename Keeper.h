#pragma once
#include "Factory.h"
#include <string>
class Keeper {
private:
    struct Node { Factory* item; Node* next; };
    Node* head_ = nullptr;
    int size_ = 0;
    Node* nodeAt(int index) const;
    void swap(Keeper& other) noexcept;
public:
    Keeper();
    explicit Keeper(const Factory& first);
    Keeper(const Keeper& other);
    Keeper& operator=(const Keeper& other);
    ~Keeper();
    int getSize() const;
    void add(const Factory& item);
    Keeper& operator+=(const Factory& item);
    Factory& operator[](int index);
    const Factory& operator[](int index) const;
    void remove(int index);
    void clear() noexcept;
    void print(std::ostream& out) const;
    void save(const std::string& path) const;
    void load(const std::string& path);
};
std::ostream& operator<<(std::ostream& out, const Keeper& keeper);

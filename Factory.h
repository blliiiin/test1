#pragma once
#include <iostream>
class Factory {
protected:
    void trace(const char* type, const char* action) const;
public:
    Factory();
    explicit Factory(const char* name);
    Factory(const Factory& other);
    Factory& operator=(const Factory& other);
    virtual ~Factory();
    virtual const char* kind() const = 0;
    virtual Factory* clone() const = 0;
    virtual void read() = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;
};
std::ostream& operator<<(std::ostream& out, const Factory& item);

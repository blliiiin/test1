#pragma once
#include "Factory.h"
#include <string>
class Car : public Factory {
private:
    std::string brand_;
    std::string model_;
    std::string plate_;
public:
    Car();
    Car(const std::string& brandValue, const std::string& modelValue, const std::string& plateValue);
    Car(const Car& other);
    Car& operator=(const Car& other);
    ~Car() override;
    const std::string& getBrand() const;
    void setBrand(const std::string& value);
    const std::string& getModel() const;
    void setModel(const std::string& value);
    const std::string& getPlate() const;
    void setPlate(const std::string& value);
    const char* kind() const override;
    Factory* clone() const override;
    void read() override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

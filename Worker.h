#pragma once
#include "Factory.h"
#include <string>
class Worker : public Factory {
private:
    std::string fullName_;
    std::string position_;
    double salary_ = 0;
    std::string address_;
    std::string phone_;
public:
    Worker();
    Worker(const std::string& fullNameValue, const std::string& positionValue, double salaryValue, const std::string& addressValue, const std::string& phoneValue);
    Worker(const Worker& other);
    Worker& operator=(const Worker& other);
    ~Worker() override;
    const std::string& getFullName() const;
    void setFullName(const std::string& value);
    const std::string& getPosition() const;
    void setPosition(const std::string& value);
    double getSalary() const;
    void setSalary(double value);
    const std::string& getAddress() const;
    void setAddress(const std::string& value);
    const std::string& getPhone() const;
    void setPhone(const std::string& value);
    const char* kind() const override;
    Factory* clone() const override;
    void read() override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

#pragma once
#include "Factory.h"
#include <string>
class Furniture : public Factory {
private:
    std::string type_;
    double height_ = 0;
    double width_ = 0;
    double depth_ = 0;
    std::string color_;
    std::string material_;
    double cost_ = 0;
public:
    Furniture();
    Furniture(const std::string& typeValue, double heightValue, double widthValue, double depthValue, const std::string& colorValue, const std::string& materialValue, double costValue);
    Furniture(const Furniture& other);
    Furniture& operator=(const Furniture& other);
    ~Furniture() override;
    const std::string& getType() const;
    void setType(const std::string& value);
    double getHeight() const;
    void setHeight(double value);
    double getWidth() const;
    void setWidth(double value);
    double getDepth() const;
    void setDepth(double value);
    const std::string& getColor() const;
    void setColor(const std::string& value);
    const std::string& getMaterial() const;
    void setMaterial(const std::string& value);
    double getCost() const;
    void setCost(double value);
    const char* kind() const override;
    Factory* clone() const override;
    void read() override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

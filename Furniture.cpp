#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif
#include "Furniture.h"
#include "Input.h"
#include <iomanip>
Furniture::Furniture() { trace("Furniture", "конструктор по умолчанию"); }
Furniture::Furniture(const std::string& typeValue, double heightValue, double widthValue, double depthValue, const std::string& colorValue, const std::string& materialValue, double costValue) : Factory("Furniture") {
    setType(typeValue);
    setHeight(heightValue);
    setWidth(widthValue);
    setDepth(depthValue);
    setColor(colorValue);
    setMaterial(materialValue);
    setCost(costValue);
    trace("Furniture", "конструктор с параметром");
}
Furniture::Furniture(const Furniture& other) : Factory(other), type_(other.type_), height_(other.height_), width_(other.width_), depth_(other.depth_), color_(other.color_), material_(other.material_), cost_(other.cost_) {
    trace("Furniture", "конструктор копирования");
}
Furniture& Furniture::operator=(const Furniture& other) {
    if (this != &other) {
        Factory::operator=(other);
        type_ = other.type_;
        height_ = other.height_;
        width_ = other.width_;
        depth_ = other.depth_;
        color_ = other.color_;
        material_ = other.material_;
        cost_ = other.cost_;
    }
    return *this;
}
Furniture::~Furniture() { trace("Furniture", "деструктор"); }
const std::string& Furniture::getType() const { return type_; }
void Furniture::setType(const std::string& value) { input::checkText(value); type_ = value; }
double Furniture::getHeight() const { return height_; }
void Furniture::setHeight(double value) { input::checkNumber(value, true); height_ = value; }
double Furniture::getWidth() const { return width_; }
void Furniture::setWidth(double value) { input::checkNumber(value, true); width_ = value; }
double Furniture::getDepth() const { return depth_; }
void Furniture::setDepth(double value) { input::checkNumber(value, true); depth_ = value; }
const std::string& Furniture::getColor() const { return color_; }
void Furniture::setColor(const std::string& value) { input::checkText(value); color_ = value; }
const std::string& Furniture::getMaterial() const { return material_; }
void Furniture::setMaterial(const std::string& value) { input::checkText(value); material_ = value; }
double Furniture::getCost() const { return cost_; }
void Furniture::setCost(double value) { input::checkNumber(value, false); cost_ = value; }
const char* Furniture::kind() const { return "Furniture"; }
Factory* Furniture::clone() const { return new Furniture(*this); }
void Furniture::read() {
    std::string typeValue = input::text("Тип мебели: ");
    double heightValue = input::number<double>("Высота (cm): ");
    double widthValue = input::number<double>("Ширина (cm): ");
    double depthValue = input::number<double>("Высота (cm): ");
    std::string colorValue = input::text("Цвет: ");
    std::string materialValue = input::text("Материал: ");
    double costValue = input::number<double>("Стоимость в рублях: ");
    Furniture valid(typeValue, heightValue, widthValue, depthValue, colorValue, materialValue, costValue);
    *this = valid;
}
void Furniture::print(std::ostream& out) const {
    out << "МЕбель\n";
    out << "Тип мебели: " << type_ << "\n";
    out << "Длина (cm): " << height_ << "\n";
    out << "Ширина (cm): " << width_ << "\n";
    out << "Высота (cm): " << depth_ << "\n";
    out << "Цвет: " << color_ << "\n";
    out << "Материал: " << material_ << "\n";
    out << "Стоимость в рублях: " << cost_ << "\n";
}
void Furniture::save(std::ostream& out) const {
    out << std::setprecision(17) << std::quoted(type_) << "\n" << height_ << "\n" << width_ << "\n" << depth_ << "\n" << std::quoted(color_) << "\n" << std::quoted(material_) << "\n" << cost_ << "\n";
}
void Furniture::load(std::istream& in) {
    std::string typeValue;
    double heightValue = 0;
    double widthValue = 0;
    double depthValue = 0;
    std::string colorValue;
    std::string materialValue;
    double costValue = 0;
    if (!(in >> std::quoted(typeValue) >> heightValue >> widthValue >> depthValue >> std::quoted(colorValue) >> std::quoted(materialValue) >> costValue))
        throw std::runtime_error("Неверная запись бро");
    Furniture valid(typeValue, heightValue, widthValue, depthValue, colorValue, materialValue, costValue);
    *this = valid;
}

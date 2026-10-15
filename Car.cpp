#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "Car.h"
#include "Input.h"

#include <iomanip>
#include <stdexcept>

Car::Car() {
    trace("Автомобиль", "конструктор без параметров");
}

Car::Car(
    const std::string& brand,
    const std::string& model,
    const std::string& plate
) : Factory("Car") {
    setBrand(brand);
    setModel(model);
    setPlate(plate);

    trace("Автомобиль", "конструктор с параметрами");
}

Car::Car(const Car& other)
    : Factory(other),
    brand_(other.brand_),
    model_(other.model_),
    plate_(other.plate_) {
    trace("Автомобиль", "конструктор копирования");
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        Factory::operator=(other);

        brand_ = other.brand_;
        model_ = other.model_;
        plate_ = other.plate_;
    }

    return *this;
}

Car::~Car() {
    trace("Автомобиль", "деструктор");
}

const std::string& Car::getBrand() const {
    return brand_;
}

const std::string& Car::getModel() const {
    return model_;
}

const std::string& Car::getPlate() const {
    return plate_;
}

void Car::setBrand(const std::string& value) {
    input::checkText(value);
    brand_ = value;
}

void Car::setModel(const std::string& value) {
    input::checkText(value);
    model_ = value;
}

void Car::setPlate(const std::string& value) {
    input::checkText(value);
    plate_ = value;
}

const char* Car::kind() const {
    return "Car";
}

Factory* Car::clone() const {
    return new Car(*this);
}

void Car::read() {
    std::string brand = input::text("Введите марку: ");
    std::string model = input::text("Введите модель: ");
    std::string plate = input::text("Введите госномер: ");

    *this = Car(brand, model, plate);
}

void Car::print(std::ostream& out) const {
    out << "Автомобиль\n"
        << "Марка: " << brand_ << '\n'
        << "Модель: " << model_ << '\n'
        << "Госномер: " << plate_ << '\n';
}

void Car::save(std::ostream& out) const {
    out << std::quoted(brand_) << '\n'
        << std::quoted(model_) << '\n'
        << std::quoted(plate_) << '\n';
}

void Car::load(std::istream& in) {
    std::string brand, model, plate;

    if (!(in >> std::quoted(brand)
        >> std::quoted(model)
        >> std::quoted(plate))) {
        throw std::runtime_error(
            "Не удалось прочитать данные автомобиля из файла."
        );
    }

    *this = Car(brand, model, plate);
}
#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "Worker.h"
#include "Input.h"

#include <iomanip>
#include <stdexcept>

Worker::Worker() {
    trace("Работник", "конструктор без параметров");
}

Worker::Worker(
    const std::string& fullNameValue,
    const std::string& positionValue,
    double salaryValue,
    const std::string& addressValue,
    const std::string& phoneValue
) : Factory("Worker") {
    setFullName(fullNameValue);
    setPosition(positionValue);
    setSalary(salaryValue);
    setAddress(addressValue);
    setPhone(phoneValue);

    trace("Работник", "конструктор с параметрами");
}

Worker::Worker(const Worker& other)
    : Factory(other),
    fullName_(other.fullName_),
    position_(other.position_),
    salary_(other.salary_),
    address_(other.address_),
    phone_(other.phone_) {
    trace("Работник", "конструктор копирования");
}

Worker& Worker::operator=(const Worker& other) {
    if (this != &other) {
        Factory::operator=(other);

        fullName_ = other.fullName_;
        position_ = other.position_;
        salary_ = other.salary_;
        address_ = other.address_;
        phone_ = other.phone_;
    }

    return *this;
}

Worker::~Worker() {
    trace("Работник", "деструктор");
}

const std::string& Worker::getFullName() const {
    return fullName_;
}

void Worker::setFullName(const std::string& value) {
    input::checkText(value);
    fullName_ = value;
}

const std::string& Worker::getPosition() const {
    return position_;
}

void Worker::setPosition(const std::string& value) {
    input::checkText(value);
    position_ = value;
}

double Worker::getSalary() const {
    return salary_;
}

void Worker::setSalary(double value) {
    input::checkNumber(value, false);
    salary_ = value;
}

const std::string& Worker::getAddress() const {
    return address_;
}

void Worker::setAddress(const std::string& value) {
    input::checkText(value);
    address_ = value;
}

const std::string& Worker::getPhone() const {
    return phone_;
}

void Worker::setPhone(const std::string& value) {
    input::checkText(value);
    phone_ = value;
}

const char* Worker::kind() const {
    return "Worker";
}

Factory* Worker::clone() const {
    return new Worker(*this);
}

void Worker::read() {
    std::string fullName = input::text("Введите ФИО: ");
    std::string position = input::text("Введите должность: ");

    double salary = input::number<double>(
        "Введите заработную плату в рублях: "
    );

    std::string address = input::text(
        "Введите адрес проживания: "
    );

    std::string phone = input::text("Введите телефон: ");

    *this = Worker(fullName, position, salary, address, phone);
}

void Worker::print(std::ostream& out) const {
    out << "Работник\n"
        << "ФИО: " << fullName_ << '\n'
        << "Должность: " << position_ << '\n'
        << "Заработная плата (руб.): " << salary_ << '\n'
        << "Адрес проживания: " << address_ << '\n'
        << "Телефон: " << phone_ << '\n';
}

void Worker::save(std::ostream& out) const {
    out << std::setprecision(17)
        << std::quoted(fullName_) << '\n'
        << std::quoted(position_) << '\n'
        << salary_ << '\n'
        << std::quoted(address_) << '\n'
        << std::quoted(phone_) << '\n';
}

void Worker::load(std::istream& in) {
    std::string fullName, position, address, phone;
    double salary = 0;

    if (!(in >> std::quoted(fullName)
        >> std::quoted(position)
        >> salary
        >> std::quoted(address)
        >> std::quoted(phone))) {
        throw std::runtime_error(
            "Не удалось прочитать данные работника из файла."
        );
    }

    *this = Worker(fullName, position, salary, address, phone);
}
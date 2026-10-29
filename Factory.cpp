#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "Factory.h"
#include <cstring>

void Factory::trace(const char* type, const char* action) const {
    const char* className = type;
    const char* message = action;

    if (std::strcmp(type, "Factory") == 0) {
        className = "Base";
    }
    else if (std::strcmp(type, "Автомобиль") == 0) {
        className = "Car";
    }
    else if (std::strcmp(type, "Работник") == 0) {
        className = "Worker";
    }

    if (std::strcmp(action, "конструктор по умолчанию") == 0) {
        message = "конструктор без параметров";
    }
    else if (std::strcmp(action, "конструктор с параметром") == 0) {
        message = "конструктор с параметрами";
    }

    std::cout << className << ": " << message << ".\n";
}

Factory::Factory() {
    trace("Factory", "конструктор без параметров");
}

Factory::Factory(const char*) {
    trace("Factory", "конструктор с параметрами");
}

Factory::Factory(const Factory&) {
    trace("Factory", "конструктор копирования");
}

Factory& Factory::operator=(const Factory&) {
    return *this;
}

Factory::~Factory() {
    trace("Factory", "деструктор");
}

std::ostream& operator<<(std::ostream& out, const Factory& item) {
    item.print(out);
    return out;
}
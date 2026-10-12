#include "Factory.h"
void Factory::trace(const char* type, const char* action) const {
    std::cout << "[" << type << " @ " << static_cast<const void*>(this) << "] " << action << '\n';
}
Factory::Factory() { trace("Factory", "default constructor"); }
Factory::Factory(const char* name) { trace(name, "Factory parameter constructor"); }
Factory::Factory(const Factory&) { trace("Factory", "copy constructor"); }
Factory& Factory::operator=(const Factory&) { return *this; }
Factory::~Factory() { trace("Factory", "destructor"); }
std::ostream& operator<<(std::ostream& out, const Factory& item) {
    item.print(out);
    return out;
}

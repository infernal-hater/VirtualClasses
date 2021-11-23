#include "animals.h"

// class Animal
Animal::Animal(Type type) : _type(type)
{
}

Animal::Type Animal::type() const {
    return _type;
}

Prey::Prey() : Animal(Type::PREY)
{
}


// class Prey
// preY и preDator
char Prey::charType() const {
    return 'Y';
}

// вовзращает true только если тип другого "Животного" = "Хищник"
bool Prey::willBeEatenBy(const Animal* forward_animal) const {
    return forward_animal->type() == Animal::Type::PREDATOR;
}


// class Predator
Predator::Predator() : Animal(Type::PREDATOR)
{
}

char Predator::charType() const {
    return 'D';
}
// всегда вовзращает false, т.к. по условию задачи ни "Добыча", ни "Хищник" не могут съесть другого "Хищника"
bool Predator::willBeEatenBy(const Animal* forward_animal) const {
    return false;
}
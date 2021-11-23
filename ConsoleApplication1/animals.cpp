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
// preY � preDator
char Prey::charType() const {
    return 'Y';
}

// ���������� true ������ ���� ��� ������� "���������" = "������"
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
// ������ ���������� false, �.�. �� ������� ������ �� "������", �� "������" �� ����� ������ ������� "�������"
bool Predator::willBeEatenBy(const Animal* forward_animal) const {
    return false;
}
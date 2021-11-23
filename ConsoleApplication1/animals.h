#pragma once

// абстратный класс "Животное"
class Animal {
public:
	// перечисление типов животных (Добыча, Хищник)
	enum class Type {
		PREY,
		PREDATOR
	};

protected: // наследуемые параметры
	// тип животного 
	Type _type;

	// конструктор, принимающий тип животного и инициализирующий тип
	Animal(Type type);

public:
	// метод, возращающий тип (не виртуальный, одинаков у всех наследников)
	Type type() const;

	// чистый виртуальный метод, возвращающий свой типовой символ
	virtual char charType() const = 0;
	// чистый виртуальный метод, принимает указатель на другое "Животное" и возвращает true или false - будет ли оно съедено этим "Животным"
	virtual bool willBeEatenBy(const Animal* forward_animal) const = 0;
};
// класс абстрактный, потому что в нём есть чистые виртуальные функции, которые переопределяются в классах наследниках,
// и из-за которых мы не можем создать объект класса Animal (функции не имеют реализаций)


// класс "Добыча", наследуется от "Животного"
class Prey : public Animal {
public:
	// конструктор по умолчанию, вызывает родительский конструктор и передает тип "Добыча"
	Prey();

	// переопределение (override) чистых виртуальных методов класса-родителя:
	// возращает отличительный символ типа животного для вывода в консоль
	char charType() const override;
	bool willBeEatenBy(const Animal* forward_animal) const;
};

// класс "Хищник", наследуется от "Животного"
class Predator : public Animal {
public:
	// аналогично Prey
	Predator();

	char charType() const override;
	bool willBeEatenBy(const Animal* forward_animal) const;
};
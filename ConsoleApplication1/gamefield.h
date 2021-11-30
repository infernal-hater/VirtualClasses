#pragma once

#include "animals.h"
#include <iostream>
#include <vector> // для vector<>
#include <time.h> // для time()

#define GAME_FIELD_ROWS 10 // кол-во строк в матрице игровового поля
#define GAME_FIELD_COLS 10 // кол-во столбцов в матрице

using namespace std;

// класс "Игровое поле"
class GameField {

private:
	vector<vector<Animal*>> _data;
	int _count_predators = 0;
	int _count_prey = 0;

	// измененная функция получения рандомной клетки
	// принимает шанс выпадения prey и predator (по умолчанию шансы равны 1/3)
	Animal* _randCell(int prey_chance = 33, int predator_chance = 33);
	void _randStep(int& i, int& j) const;
	void _countAnimals();

public:
	// конструктор по умолчанию
	GameField();

	// конструктор с параметрами
	GameField(int prey_chance, int predator_chance);

	void step();
	void print() const;
};
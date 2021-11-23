#pragma once

#include "animals.h"
#include <iostream>
#include <vector> // дл€ vector<>
#include <time.h> // дл€ time()

#define GAME_FIELD_ROWS 5 // кол-во строк в матрице игровового пол€
#define GAME_FIELD_COLS 5 // кол-во столбцов в матрице

using namespace std;

// класс "»гровое поле"
class GameField {

private:
	// двумерна€ матрица игрового пол€ - массив массивов (vector - динамический массив),
	// где каждый элемент матрицы - указатель на "∆ивотное"
	vector<vector<Animal*>> _data;
	// кол-во ’ищников
	int _count_predators = 0;
	// кол-во ƒобыч
	int _count_prey = 0;

	// возвращает случайные данные дл€ указател€ клетки Animal* 
	Animal* _randCell();

	// метод принимает две переменных, в которые записывает рандомные координаты матрицы
	void _randStep(int& i, int& j) const;

	// метод проходитс€ по матрице и считает ƒобычи и ’ищников
	void _countAnimals();

public:
	// конструктор по умолчанию, задает размеры векторам и инициализирует рандомными значени€ми
	GameField();

	// метод реализует один шаг-итерацию
	void step();

	// метод печатает матрицу в консоль и кол-во животных
	void print() const;
};
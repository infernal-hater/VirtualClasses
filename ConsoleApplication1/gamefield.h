#pragma once

#include "animals.h"
#include <iostream>
#include <vector> // для vector<>
#include <time.h> // для time()

#define GAME_FIELD_ROWS 5 // кол-во строк в матрице игровового поля
#define GAME_FIELD_COLS 5 // кол-во столбцов в матрице

using namespace std;

// класс "Игровое поле"
class GameField {
private:
	// двумерная матрица игрового поля - массив массивов (vector - динамический массив), где каждый элемент матрицы - указатель на "Животное"
	vector<vector<Animal*>> _data;
	// кол-во Хищников
	int _count_predators = 0;
	// кол-во Добыч (по умолчанию нули)
	int _count_prey = 0;

	// метод возвращает рандомную клетку, а точнее какие данные присвоить указателю клетки Animal* 
	Animal* _randCell();

	// метод принимает две переменных, в которые записывает рандомные координаты матрицы
	void _randStep(int& i, int& j) const;

	// метод проходится по матрице и считает Добычи и Хищников
	void _countAnimals();

public:
	// конструктор по умолчанию, задает размеры векторам и инициализирует рандомными значениями
	GameField();

	// метод реализует один шаг-итерацию
	void step();

	// метод печатает матрицу в консоль и кол-во животных
	void print() const;
};
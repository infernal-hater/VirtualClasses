#pragma once

#include "animals.h"
#include <iostream>
#include <vector> // ��� vector<>
#include <time.h> // ��� time()

#define GAME_FIELD_ROWS 10 // ���-�� ����� � ������� ���������� ����
#define GAME_FIELD_COLS 10 // ���-�� �������� � �������

using namespace std;

// ����� "������� ����"
class GameField {

private:
	vector<vector<Animal*>> _data;
	int _count_predators = 0;
	int _count_prey = 0;

	// ���������� ������� ��������� ��������� ������
	// ��������� ���� ��������� prey � predator (�� ��������� ����� ����� 1/3)
	Animal* _randCell(int prey_chance = 33, int predator_chance = 33);
	void _randStep(int& i, int& j) const;
	void _countAnimals();

public:
	// ����������� �� ���������
	GameField();

	// ����������� � �����������
	GameField(int prey_chance, int predator_chance);

	void step();
	void print() const;
};
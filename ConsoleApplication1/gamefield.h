#pragma once

#include "animals.h"
#include <iostream>
#include <vector> // ��� vector<>
#include <time.h> // ��� time()

#define GAME_FIELD_ROWS 5 // ���-�� ����� � ������� ���������� ����
#define GAME_FIELD_COLS 5 // ���-�� �������� � �������

using namespace std;

// ����� "������� ����"
class GameField {
private:
	// ��������� ������� �������� ���� - ������ �������� (vector - ������������ ������), ��� ������ ������� ������� - ��������� �� "��������"
	vector<vector<Animal*>> _data;
	// ���-�� ��������
	int _count_predators = 0;
	// ���-�� ����� (�� ��������� ����)
	int _count_prey = 0;

	// ����� ���������� ��������� ������, � ������ ����� ������ ��������� ��������� ������ Animal* 
	Animal* _randCell();

	// ����� ��������� ��� ����������, � ������� ���������� ��������� ���������� �������
	void _randStep(int& i, int& j) const;

	// ����� ���������� �� ������� � ������� ������ � ��������
	void _countAnimals();

public:
	// ����������� �� ���������, ������ ������� �������� � �������������� ���������� ����������
	GameField();

	// ����� ��������� ���� ���-��������
	void step();

	// ����� �������� ������� � ������� � ���-�� ��������
	void print() const;
};
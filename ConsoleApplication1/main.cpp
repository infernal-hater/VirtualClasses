#include <iostream>
#include "gamefield.h" // класс Игрового Поля

#define MAX_ITERARIONS 5

using namespace std;

int main() {
	// создаем игровое поле
	GameField gf;

	// печатаем матрицу начального поля
	cout << "Start positions:\n";
	gf.print();
	cout << "\n";

	// делаем MAX_ITERATIONS шага-итерации и печатаем 
	for (int i = 0; i < MAX_ITERARIONS; i++) {

		gf.step(); // Делаем шаг
		cout << "Iteration #" << i << "\n";
		gf.print(); // Делаем вывод
		cout << "\n";

	}

	cout << "That's all Folks!\n";

	return 0;
}
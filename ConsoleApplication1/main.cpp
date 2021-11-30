#include <iostream>
#include <stdlib.h>
#include "gamefield.h" // класс Игрового Поля

#define MAX_ITERARIONS 5

using namespace std;

int main() {
	
	int lh_predator = 0, lh_prey = 0;

	do {
		cout << "Enter the likelihood of a prey spawn from 0 to 100: ";
		cin >> lh_prey;
	} while ((lh_prey <= -1) || (lh_prey >= 101));

	do {
		cout << "Enter the likelihood of a predator spawn from 0 to 100: ";
		cin >> lh_predator;
	} while ((lh_predator <= -1) || (lh_predator >= 101));
	
	system("cls");
	cout << "\nPrey spawn chance is " << lh_prey << "%. Predator spawn chance is " << lh_predator << "%\n";

	GameField gf(lh_prey, lh_predator);

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
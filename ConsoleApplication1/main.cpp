#include <iostream>
#include <stdlib.h>
#include "gamefield.h" // класс Игрового Поля

#define MAX_ITERARIONS 5

using namespace std;

int main() {
	
	int lh_predator, lh_prey;
	cout << "Enter the likelihood of a prey spawn: ";
	cin >> lh_prey;
	cout << "Enter the likelihood of a predator spawn: ";
	cin >> lh_predator;
	system("cls");
	cout << "\nPrey spawn chance is " << lh_prey << "%. Predator spawn chance is " << lh_predator << "%\n";
	cout << "Press any key to start the simulation...\n";
	system("pause");

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
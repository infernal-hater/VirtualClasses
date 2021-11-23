#include <iostream>
#include "gamefield.h" // класс Игрового Поля

using namespace std;

int main() {
	// создаем игровое поле
	GameField gf;

	// печатаем матрицу 
	gf.print();
	cout << "\n\n\n";

	// делаем 3 шага-итерации и печатаем 
	for (int i = 0; i < 3; i++) {

		gf.step(); // Делаем шаг
		gf.print(); // Делаем вывод
		cout << "\n\n\n";

	}

	cout << "That's all Folks!\n";

	return 0;
}
// ОНО, БЛИН, РАБОТАЕТ! Просто не трожь.
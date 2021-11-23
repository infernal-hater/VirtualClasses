#include "gamefield.h"

// Заполнение поля животными через рандом
Animal* GameField::_randCell() {
    switch (rand() % 3) {

    case 0:
        return nullptr; // Пустая клетка
    case 1:
        return new Prey; // Жертва
    case 2:
        return new Predator; // Хищник

    default:
        return nullptr;
    }
}

void GameField::_randStep(int& i, int& j) const {

    unsigned int temp = i;

    // Рандомизация позиции, отличной от текущей
    do {
        i = rand() % GAME_FIELD_ROWS;
    } while (i == temp);

    j = rand() % GAME_FIELD_COLS;

}


// Подсчет типов клеток.
void GameField::_countAnimals() {

    // Начальное обнуление счетчиков, куда же без этого?
    _count_predators = 0; 
    _count_prey = 0;

    for (int i = 0; i < _data.front().size(); i++) {
        for (int j = 0; j < _data.size(); j++) {

            if (_data[i][j] == nullptr) {
                continue;
            }
            
            // Подсчет хищников
            if (_data[i][j]->type() == Animal::Type::PREDATOR) {
                _count_predators++;
            }
            // Подсчет жертв
            else if (_data[i][j]->type() == Animal::Type::PREY) {
                _count_prey++;
            }
        }
    }
}

// Заполнение игрового поля
GameField::GameField()
{
    // для функции rand()
    srand(time(NULL));


    _data.resize(GAME_FIELD_ROWS);
    for (int i = 0; i < GAME_FIELD_ROWS; i++) {
        _data[i].resize(GAME_FIELD_COLS);
        for (int j = 0; j < GAME_FIELD_COLS; j++) {
            _data[i][j] = _randCell();
        }
    }

    // посчитать хищников и добыч
    _countAnimals();
}

// Метод, отвечающий за шаг
void GameField::step() {

    // объявляем временную матрицу булевых значений, такую же по размерам как _data
    // нужна для отслеживаний перемещений Животных, чтобы не перемещать одно Животное несколько раз
    vector<vector<bool>> moving;
    moving.resize(_data.front().size());
    for (int i = 0; i < _data.front().size(); i++) {
        moving[i].resize(_data.size());
        for (int j = 0; j < _data.size(); j++) {
            moving[i][j] = false;
        }
    }
    // изначально вся матрица = false, когда Животное перемещается в клетку, эту клетку ставим true, и при итерации пропускаем 

    // проходимся по матрице _data и перемещаем животных
    for (int i = 0; i < _data.front().size(); i++) {
        for (int j = 0; j < _data.size(); j++) {
            // если клетка пустая или в неё уже перемещались, то пропускаем
            if (_data[i][j] == nullptr || moving[i][j]) {
                continue;
            }

            // получаем новые координаты
            int new_i, new_j;
            _randStep(new_i, new_j);

            // если новые координаты указывают на пустую клетку, просто перемещаем Животное туда
            if (_data[new_i][new_j] == nullptr) {
                _data[new_i][new_j] = _data[i][j];
                _data[i][j] = nullptr;

                // в перемещенной клетке - true
                moving[new_i][new_j] = true;
                continue;
            }

            // если по новым координатам находится животное, то смотрим - будет ли оно съедено перемещаемым животным
            // Жертва не может съесть кого-либо, Хищник не может съесть Хищника
            if (_data[new_i][new_j]->willBeEatenBy(_data[i][j])) {
                delete _data[new_i][new_j];
                _data[new_i][new_j] = _data[i][j];
                _data[i][j] = nullptr;

                moving[new_i][new_j] = true;
            }
        }
    }

    // считаем животных
    _countAnimals();
}


// Метод вывода игрового поля в окно консоли
void GameField::print() const {
    cout << "<=================>\n";
    for (int i = 0; i < _data.front().size(); i++) {
        for (int j = 0; j < _data.size(); j++) {
            if (_data[i][j] == nullptr) {
                cout << "_ ";
            }
            else {
                cout << _data[i][j]->charType() << " ";
            }
        }
        cout << "\n";
    }
    cout << "<=================>\n";
    cout << "\'Y\' prey: " << _count_prey << "\n";
    cout << "\'D\' predators: " << _count_predators << "\n";
}
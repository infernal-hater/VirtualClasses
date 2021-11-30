#include "gamefield.h"

Animal* GameField::_randCell(int prey_chance, int predator_chance) {
    // генерируем рандомное число от 1 до 100 включительно
    unsigned int rand_value = rand() % 100 + 1;

    // смотрим в каком диапазоне оно выпало и возвращаем нужное значение

    // [1 ; prey_chance]
    if (rand_value <= prey_chance) {
        return new Prey;
    }
    // [prey_chance + 1 ; prey_chance + predator_chance]
    if (rand_value <= prey_chance + predator_chance) {
        return new Predator;
    }

    // [prey_chance + predator_chance + 1 ; 100]
    return nullptr;
}

void GameField::_randStep(int& i, int& j) const {
    unsigned int temp = i;
    do {
        i = rand() % GAME_FIELD_ROWS;
    } while (i == temp);

    j = rand() % GAME_FIELD_COLS;
}

void GameField::_countAnimals() {
    _count_predators = _count_prey = 0;

    for (int i = 0; i < _data.front().size(); i++) {
        for (int j = 0; j < _data.size(); j++) {
            if (_data[i][j] == nullptr) {
                continue;
            }

            if (_data[i][j]->type() == Animal::Type::PREDATOR) {
                _count_predators++;
            }
            else if (_data[i][j]->type() == Animal::Type::PREY) {
                _count_prey++;
            }
        }
    }
}

// вызывает функцию _randCell(), без параметров - то есть вероятности будут по 1/3
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

    _countAnimals();
}

// принимает вероятности и передает в функцию _randCell(int, int)
GameField::GameField(int prey_chance, int predator_chance)
{
    // для функции rand()
    srand(time(NULL));

    _data.resize(GAME_FIELD_ROWS);
    for (int i = 0; i < GAME_FIELD_ROWS; i++) {
        _data[i].resize(GAME_FIELD_COLS);
        for (int j = 0; j < GAME_FIELD_COLS; j++) {
            _data[i][j] = _randCell(prey_chance, predator_chance);
        }
    }

    _countAnimals();
}

void GameField::step() {
    vector<vector<bool>> moving;
    moving.resize(_data.front().size());
    for (int i = 0; i < _data.front().size(); i++) {
        moving[i].resize(_data.size());
        for (int j = 0; j < _data.size(); j++) {
            moving[i][j] = false;
        }
    }

    for (int i = 0; i < _data.front().size(); i++) {
        for (int j = 0; j < _data.size(); j++) {
            if (_data[i][j] == nullptr || moving[i][j]) {
                continue;
            }

            int new_i, new_j;
            _randStep(new_i, new_j);

            if (_data[new_i][new_j] == nullptr) {
                _data[new_i][new_j] = _data[i][j];
                _data[i][j] = nullptr;

                moving[new_i][new_j] = true;
                continue;
            }

            if (_data[new_i][new_j]->willBeEatenBy(_data[i][j])) {
                delete _data[new_i][new_j];
                _data[new_i][new_j] = _data[i][j];
                _data[i][j] = nullptr;

                moving[new_i][new_j] = true;
            }
        }
    }

    _countAnimals();
}


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
    cout << "Amount of pre(Y)ers: " << _count_prey << "\n";
    cout << "Amount of pre(D)ators: " << _count_predators << "\n";
}
#include "gamefield.h"

// «аполнение пол€ животными
Animal* GameField::_randCell() {
    switch (rand() % 3) {

    case 0:
        return nullptr; // ѕуста€ клетка
    case 1:
        return new Prey; // ∆ертва
    case 2:
        return new Predator; // ’ищник

    default:
        return nullptr;
    }
}

void GameField::_randStep(int& i, int& j) const {

    unsigned int temp = i;

    // –андомизаци€ позиции, отличной от текущей
    do {
        i = rand() % GAME_FIELD_ROWS;
    } while (i == temp);

    j = rand() % GAME_FIELD_COLS;

}


// ѕодсчет типов клеток.
void GameField::_countAnimals() {

    // Ќачальное обнуление счетчиков, куда же без этого?
    _count_predators = 0; 
    _count_prey = 0;

    for (int i = 0; i < _data.front().size(); i++) {
        for (int j = 0; j < _data.size(); j++) {

            if (_data[i][j] == nullptr) {
                continue;
            }
            
            // ѕодсчет хищников
            if (_data[i][j]->type() == Animal::Type::PREDATOR) {
                _count_predators++;
            }
            // ѕодсчет жертв
            else if (_data[i][j]->type() == Animal::Type::PREY) {
                _count_prey++;
            }
        }
    }
}

GameField::GameField()
{
    // дл€ функции rand()
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

void GameField::step() {
    // объ€вл€ем временную матрицу булевых значений, такую же по размерам как _data
    // нужна дл€ отслеживаний перемещений ∆ивотных, чтобы не перемещать одно ∆ивотное несколько раз
    vector<vector<bool>> moving;
    moving.resize(_data.front().size());
    for (int i = 0; i < _data.front().size(); i++) {
        moving[i].resize(_data.size());
        for (int j = 0; j < _data.size(); j++) {
            moving[i][j] = false;
        }
    }
    // изначально вс€ матрица = false, когда ∆ивотное перемещаетс€ в клетку, эту клетку ставим true, и при итерации пропускаем 

    // проходимс€ по матрице _data и перемещаем животных
    for (int i = 0; i < _data.front().size(); i++) {
        for (int j = 0; j < _data.size(); j++) {
            // если клетка пуста€ или в неЄ уже перемещались, то пропускаем
            if (_data[i][j] == nullptr || moving[i][j]) {
                continue;
            }

            // получаем новые координаты
            int new_i, new_j;
            _randStep(new_i, new_j);

            // если новые координаты указывают на пустую клетку, просто перемещаем ∆ивотное туда
            if (_data[new_i][new_j] == nullptr) {
                _data[new_i][new_j] = _data[i][j];
                _data[i][j] = nullptr;

                // в перемещенной клетке стави true
                moving[new_i][new_j] = true;
                continue;
            }

            // если по новым координатам находитс€ животное, то смотрим - будет ли оно съедено перемещаемым животным
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

void GameField::print() const {
    cout << "=================\n";
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
    cout << "=================\n";
    cout << "\'Y\' prey: " << _count_prey << "\n";
    cout << "\'D\' predators: " << _count_predators << "\n";
}
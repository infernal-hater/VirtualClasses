#include "gamefield.h"

// ���������� ���� ��������� ����� ������
Animal* GameField::_randCell() {
    switch (rand() % 3) {

    case 0:
        return nullptr; // ������ ������
    case 1:
        return new Prey; // ������
    case 2:
        return new Predator; // ������

    default:
        return nullptr;
    }
}

void GameField::_randStep(int& i, int& j) const {

    unsigned int temp = i;

    // ������������ �������, �������� �� �������
    do {
        i = rand() % GAME_FIELD_ROWS;
    } while (i == temp);

    j = rand() % GAME_FIELD_COLS;

}


// ������� ����� ������.
void GameField::_countAnimals() {

    // ��������� ��������� ���������, ���� �� ��� �����?
    _count_predators = 0; 
    _count_prey = 0;

    for (int i = 0; i < _data.front().size(); i++) {
        for (int j = 0; j < _data.size(); j++) {

            if (_data[i][j] == nullptr) {
                continue;
            }
            
            // ������� ��������
            if (_data[i][j]->type() == Animal::Type::PREDATOR) {
                _count_predators++;
            }
            // ������� �����
            else if (_data[i][j]->type() == Animal::Type::PREY) {
                _count_prey++;
            }
        }
    }
}

// ���������� �������� ����
GameField::GameField()
{
    // ��� ������� rand()
    srand(time(NULL));


    _data.resize(GAME_FIELD_ROWS);
    for (int i = 0; i < GAME_FIELD_ROWS; i++) {
        _data[i].resize(GAME_FIELD_COLS);
        for (int j = 0; j < GAME_FIELD_COLS; j++) {
            _data[i][j] = _randCell();
        }
    }

    // ��������� �������� � �����
    _countAnimals();
}

// �����, ���������� �� ���
void GameField::step() {

    // ��������� ��������� ������� ������� ��������, ����� �� �� �������� ��� _data
    // ����� ��� ������������ ����������� ��������, ����� �� ���������� ���� �������� ��������� ���
    vector<vector<bool>> moving;
    moving.resize(_data.front().size());
    for (int i = 0; i < _data.front().size(); i++) {
        moving[i].resize(_data.size());
        for (int j = 0; j < _data.size(); j++) {
            moving[i][j] = false;
        }
    }
    // ���������� ��� ������� = false, ����� �������� ������������ � ������, ��� ������ ������ true, � ��� �������� ���������� 

    // ���������� �� ������� _data � ���������� ��������
    for (int i = 0; i < _data.front().size(); i++) {
        for (int j = 0; j < _data.size(); j++) {
            // ���� ������ ������ ��� � �� ��� ������������, �� ����������
            if (_data[i][j] == nullptr || moving[i][j]) {
                continue;
            }

            // �������� ����� ����������
            int new_i, new_j;
            _randStep(new_i, new_j);

            // ���� ����� ���������� ��������� �� ������ ������, ������ ���������� �������� ����
            if (_data[new_i][new_j] == nullptr) {
                _data[new_i][new_j] = _data[i][j];
                _data[i][j] = nullptr;

                // � ������������ ������ - true
                moving[new_i][new_j] = true;
                continue;
            }

            // ���� �� ����� ����������� ��������� ��������, �� ������� - ����� �� ��� ������� ������������ ��������
            // ������ �� ����� ������ ����-����, ������ �� ����� ������ �������
            if (_data[new_i][new_j]->willBeEatenBy(_data[i][j])) {
                delete _data[new_i][new_j];
                _data[new_i][new_j] = _data[i][j];
                _data[i][j] = nullptr;

                moving[new_i][new_j] = true;
            }
        }
    }

    // ������� ��������
    _countAnimals();
}


// ����� ������ �������� ���� � ���� �������
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
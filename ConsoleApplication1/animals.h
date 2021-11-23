#pragma once

// ���������� ����� "��������"
class Animal {
public:
	// ������������ ����� �������� (������, ������)
	enum class Type {
		PREY,
		PREDATOR
	};

protected: // ����������� ���������
	// ��� ��������� 
	Type _type;

	// �����������, ����������� ��� ��������� � ���������������� ���
	Animal(Type type);

public:
	// �����, ����������� ��� (�� �����������, �������� � ���� �����������)
	Type type() const;

	// ������ ����������� �����, ������������ ���� ������� ������
	virtual char charType() const = 0;
	// ������ ����������� �����, ��������� ��������� �� ������ "��������" � ���������� true ��� false - ����� �� ��� ������� ���� "��������"
	virtual bool willBeEatenBy(const Animal* forward_animal) const = 0;
};
// ����� �����������, ������ ��� � �� ���� ������ ����������� �������, ������� ���������������� � ������� �����������,
// � ��-�� ������� �� �� ����� ������� ������ ������ Animal (������� �� ����� ����������)


// ����� "������", ����������� �� "���������"
class Prey : public Animal {
public:
	// ����������� �� ���������, �������� ������������ ����������� � �������� ��� "������"
	Prey();

	// ��������������� (override) ������ ����������� ������� ������-��������:
	// ��������� ������������� ������ ���� ��������� ��� ������ � �������
	char charType() const override;
	bool willBeEatenBy(const Animal* forward_animal) const;
};

// ����� "������", ����������� �� "���������"
class Predator : public Animal {
public:
	// ���������� Prey
	Predator();

	char charType() const override;
	bool willBeEatenBy(const Animal* forward_animal) const;
};
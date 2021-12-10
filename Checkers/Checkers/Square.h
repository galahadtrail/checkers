#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf; 

wstring assignRegimeFromFile(std::string fileName) {
	wifstream in(fileName);
	std::wstring raw_result;
	in >> raw_result;
	in.close();
	size_t first = raw_result.find('|');

	int i = 0;
	std::wstring temp;
	while (i < first)
	{
		temp += raw_result[i];
		i++;
	}
	wstring regime = temp;

	temp = L"";
	i = first + 1;
	while (i < raw_result.size())
	{
		temp += raw_result[i];
		i++;
	}
	wstring guestName = temp;

	return guestName;
}

class Square {
private:
	bool backlight = 0;// ��������� 0 ���� ���, 1 ���� ����
	bool employment = 0;// 0 ��� ���������, 1 ��� �������
	bool checker_color;// 0 ��� �����, 1 ��� ������
	RectangleShape square = RectangleShape(Vector2f(50, 50));
public:
	Square() { ; }

	RectangleShape &get_square() {
		return this->square;
	}
	bool get_backlight() {
		return this->backlight;
	}
	bool get_employment() {
		return this->employment;
	}
	bool get_checker_color() {
		return this->checker_color;
	}

	void on_backlight() {
		this->backlight = 1;
	}
	void off_backlight() {
		this->backlight = 0;
	}
	void square_employment(bool _color) {
		this->employment = 1;
		this->checker_color = _color;
	}
	void square_free() {
		this->employment = 0;
	}
	void set_color(Color _color) {
		this->square.setFillColor(_color);
	}
	void set_position(float _x, float _y) {
		this->square.setPosition(_x, _y);
	}
};
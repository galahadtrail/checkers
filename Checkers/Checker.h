#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
using namespace sf;
using namespace std;

class Checker {
private:
	CircleShape checker = CircleShape(18);
	bool checker_color;// 0 для белых, 1 для черных
	bool select = 0;//1 если выбрана, 0 если нет
	bool queen = 0;//1 если шашка дамка, 0 если нет
	Texture texture;//текстура значка дамки
	Sprite sprite;//спрайт значка дамки
public:
	CircleShape &get_checker() {
		return this->checker;
	}
	Vector2f get_position() {
		return this->checker.getPosition();
	}
	float get_x() {
		return (this->get_position().x - 57) / 50;
	}
	float get_y() {
		return (this->get_position().y - 57) / 50;
	}
	bool get_color() {
		return this->checker_color;
	}
	bool get_select() {
		return this->select;
	}
	bool get_queen() {
		return this->queen;
	}

	void make_queen() {
		this->queen = 1;
	}
	void set_position(float _x_position, float _y_position) {
		this->checker.setPosition(_x_position, _y_position);
	}
	void set_color(Color _color) {
		this->checker.setFillColor(_color);
	}
	void select_checker() {//выбор фигуры
		this->select = 1;
	}
	void leave_checker() {//отмена выбора фигуры
		this->select = 0;
	}

	Checker() { }

	Checker(float _x_position, float _y_position, bool _color) {
		wifstream input("user.txt");
		wstring bulk;
		getline(input, bulk);
		int theme;
		input.close();

		int index = bulk.rfind(':') + 1;
		if (bulk[index] == 'D') {
			theme = 0;
		}
		else {
			theme = 1;
		}

		this->checker.setOutlineThickness(3);
		this->checker.setOutlineColor(sf::Color(0, 0, 0));
		this->checker_color = _color;
		if (_color == 0) {
			if (theme == 0) {
				this->set_color(Color(180, 120, 55));
			}
			else {
				this->set_color(Color(255, 255, 255));
			}
		}
		else if (_color == 1) {
			if (theme == 0) {
				this->set_color(Color(61, 25, 7));  
			}
			else {
				this->set_color(Color(0, 0, 0));
			}
		}
		this->set_position(_x_position, _y_position);
		this->select = 0;
	}

	void draw_checker(RenderWindow  &_window) {
		_window.draw(this->checker);
		if (queen == 1) {
			this->texture.loadFromFile("Images//Queen.png");
			this->sprite.setTexture(texture);
			this->sprite.setTextureRect(IntRect(0, 0, 25, 25));
			this->sprite.setPosition(this->get_position().x + 6, this->get_position().y + 6);
		}
		_window.draw(this->sprite);
	}

	Checker operator = (Checker _checker) {
		wifstream input("user.txt");
		wstring bulk;
		getline(input, bulk);
		int theme;
		input.close();

		int index = bulk.rfind(':') + 1;
		if (bulk[index] == 'D') {
			theme = 0;
		}
		else {
			theme = 1;
		}

		this->texture = _checker.texture;
		this->sprite = _checker.sprite;
		this->select = _checker.select;
		this->queen = _checker.queen;
		this->checker_color = _checker.checker_color;
		if (_checker.checker_color == 0) {
			if (theme == 0) {
				this->set_color(Color(180, 120, 55));
			}
			else {
				this->set_color(Color(255, 255, 255));
			}
		}
		else if (_checker.checker_color == 1) {
			if (theme == 0) {
				this->set_color(Color(61, 25, 7));
			}
			else {
				this->set_color(Color(0, 0, 0));
			}
		}
		this->set_position(_checker.get_position().x, _checker.get_position().y);
		return (*this);
	}
};
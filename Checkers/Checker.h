#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Checker {
private:
	CircleShape checker = CircleShape(18);
	bool checker_color;// 0  , 1  
	bool select = 0;//1  , 0  
	bool queen = 0;//1   , 0  
	Texture texture;//  
	Sprite sprite;//  
public:
	CircleShape &get_checker() {return this->checker;}
	Vector2f get_position() {return this->checker.getPosition();}
	float get_x() {return (this->get_position().x - 57) / 50;}
	float get_y() {return (this->get_position().y - 57) / 50;}
	bool get_color() {return this->checker_color;}
	bool get_select() {return this->select;}
	bool get_queen() {return this->queen;}
	void make_queen() {this->queen = 1;}
	void set_position(float _x_position, float _y_position) { this->checker.setPosition(_x_position, _y_position); }
	void set_color(Color _color) {this->checker.setFillColor(_color);}
	void select_checker() {this->select = 1;}
	void leave_checker() {this->select = 0;}
	Checker() { }

	Checker(float _x_position, float _y_position, bool _color)
	{
		
		this->checker.setOutlineThickness(3);
		this->checker.setOutlineColor(sf::Color(0, 0, 0));
		this->checker_color = _color;
		if (_color == 1) {
			this->set_color(Color(195, 132, 60));
		}
		if (_color == 0) {
			this->set_color(Color(88, 39, 15));
		}
		this->set_position(_x_position, _y_position);
		this->select = 0;
	}

	void draw_checker(RenderWindow  &_window)
	{
		_window.draw(this->checker);
		if (queen == 1) 
		{
			this->texture.loadFromFile("images//Queen.png");
			this->sprite.setTexture(texture);
			this->sprite.setTextureRect(IntRect(0, 0, 25, 25));
			this->sprite.setPosition(this->get_position().x + 6, this->get_position().y + 6);
		}
		_window.draw(this->sprite);
	}

	Checker operator = (Checker _checker)
	{
		this->texture = _checker.texture;
		this->sprite = _checker.sprite;
		this->select = _checker.select;
		this->queen = _checker.queen;
		this->checker_color = _checker.checker_color;
		if (_checker.checker_color == 1) 
			this->set_color(Color(195, 132, 60));

		if (_checker.checker_color == 0)
			this->set_color(Color(88, 39, 15));

		this->set_position(_checker.get_position().x, _checker.get_position().y);
		return (*this);
	}
};

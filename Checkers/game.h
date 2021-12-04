#pragma once
#include <SFML/Graphics.hpp>
#include "Checkers_on_board_Inter.h"
#include "Checkers_on_board_RCG.h"
#include <string>
#include <fstream>
using namespace sf;

class Game {
private:
	int how_many = 0;
	bool flag = false;//���������� ������, ��� �� ������ ���
	int who_can_move = 0;//���� ����, 0 ���� ��� �����, 1 ���� ��� ������
	bool select_is_made = 0;//0 ���� ������ �� �������, 1 ���� �������
	int choiseChecker;//����� ��������� ��� ���� �����
	std::string mode;//����� ����
	std::string rounds;//���������� �������
	std::string colorChecker;//���� �����
	float x;//����� ������ � ������� ����� �� ��� �
	float y;//����� ������ � ������� ����� �� ��� �
	Vector2i mousePosition;//������� ����
	Checkers_on_board_RCG checkers_on_board;//������������ ����� �� ����� � ������� ����� ��������������
	Checkers_on_board_Inter checkers_on_board_inter;//������������ ����� �� ����� � ������������� ������
	vector <int> who_must_eat;//����� �����, ������� ����� ������
public:
	std::string getMode() { return mode; }
	std::string getColor() { return colorChecker; }
	void assignValuesFromFile(std::string fileName)
	{
		ifstream in(fileName);
		std::string raw_result;
		in >> raw_result;
		in.close();
		size_t first = raw_result.find('|');
		size_t second = raw_result.find('|', first + 1);
		int i = 0;
		std::string temp;
		while (i < first)
		{
			temp += raw_result[i];
			i++;
		}

		rounds = temp;
		temp = "";
		i = first + 1;
		while (i < second)
		{
			temp += raw_result[i];
			i++;
		}

		mode = temp;
		temp = "";
		i = second + 1;
		while (i < raw_result.size())
		{
			temp += raw_result[i];
			i++;
		}
		colorChecker = temp;
		return;
	}
	Checkers_on_board_Inter& get_checkers_on_board_inter() { return this->checkers_on_board_inter; }
	Checkers_on_board_RCG& get_checkers_on_board_rcg() { return this->checkers_on_board; }
	void set_mause_position(RenderWindow& _window) { this->mousePosition = Mouse::getPosition(_window); }
	Vector2i centre_on_square() {
		int maxSize = mode == "International" ? 10 : 8;
		for (int i = 0; i < maxSize; i++) {
			for (int j = 0; j < maxSize; j++) {
				if (mousePosition.x < i * 50 + 100 && mousePosition.x < (i + 1) * 50 + 100 &&
					mousePosition.y < j * 50 + 100 && mousePosition.y < (j + 1) * 50 + 100) {
					return Vector2i(i * 50 + 57, j * 50 + 57);
				}
			}
		}
	}
	void set_who_can_move()
	{
		if(mode == "Checkers" && flag == false)
		{
			this->who_can_move = 1;
			flag = true;
		}
		//��� �������� �� �����������������,
		//�������� ������� �� - (mode == "Checkers" && who_can_move == 2) � ���������� who_can_move ��������� �� ��������� 2
	}

	void choise_of_chacker(RenderWindow& _window, Event _event) {
		if(mode != "International")
		{
			if (_event.type == sf::Event::MouseButtonPressed) {
				if (_event.key.code == Mouse::Left) {
					set_mause_position(_window);
					if (_event.type == sf::Event::MouseButtonPressed) {//��� ������ ������ ������
						if (_event.key.code == Mouse::Left) {
							if (checkers_on_board.get_checker(choiseChecker).get_select() == 1 && select_is_made == 1) {
								checkers_on_board.get_checker(choiseChecker).leave_checker();
								select_is_made = 0;
								checkers_on_board.delete_backlight();
								return;
							}
						}
					}
					for (int i = 0; i < checkers_on_board.get_size(); i++) {
						if (this->mousePosition.x >= checkers_on_board.get_checker(i).get_position().x - 7 &&
							this->mousePosition.x <= checkers_on_board.get_checker(i).get_position().x + 43 &&
							this->mousePosition.y >= checkers_on_board.get_checker(i).get_position().y - 7 &&
							this->mousePosition.y <= checkers_on_board.get_checker(i).get_position().y + 43) {
							if (checkers_on_board.get_checker(i).get_select() == 0 && select_is_made == 0) {
								if (checkers_on_board.get_checker(i).get_color() == who_can_move) {
									if (if_you_can_eat_you_must_eat(checkers_on_board.get_checker(i).get_color())) {
										int s = 0;
										for (int f : who_must_eat) {
											if (f == i) {
												s++;
											}
										}
										if (s == 0) {
											error_choise_checker(_window, _event);
											checkers_on_board.delete_backlight();
											return;
										}
									}
									choiseChecker = i;
									select_is_made = 1;
									checkers_on_board.get_checker(choiseChecker).select_checker();
									x = checkers_on_board.get_checker(choiseChecker).get_x();
									y = checkers_on_board.get_checker(choiseChecker).get_y();
									if (checkers_on_board.get_checker(choiseChecker).get_queen()) {
										queen_square_for_move(checkers_on_board.get_checker(choiseChecker).get_color(), 1, 1, 1, 1);
									}
									else {
										square_for_move();
									}
									return;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			if (_event.type == sf::Event::MouseButtonPressed) {
				if (_event.key.code == Mouse::Left) {
					set_mause_position(_window);
					if (_event.type == sf::Event::MouseButtonPressed) {//��� ������ ������ ������
						if (_event.key.code == Mouse::Left) {
							if (checkers_on_board_inter.get_checker(choiseChecker).get_select() == 1 && select_is_made == 1) {
								checkers_on_board_inter.get_checker(choiseChecker).leave_checker();
								select_is_made = 0;
								checkers_on_board_inter.delete_backlight();
								return;
							}
						}
					}
					for (int i = 0; i < checkers_on_board_inter.get_size(); i++) {
						if (this->mousePosition.x >= checkers_on_board_inter.get_checker(i).get_position().x - 7 &&
							this->mousePosition.x <= checkers_on_board_inter.get_checker(i).get_position().x + 43 &&
							this->mousePosition.y >= checkers_on_board_inter.get_checker(i).get_position().y - 7 &&
							this->mousePosition.y <= checkers_on_board_inter.get_checker(i).get_position().y + 43) {
							if (checkers_on_board_inter.get_checker(i).get_select() == 0 && select_is_made == 0) {
								if (checkers_on_board_inter.get_checker(i).get_color() == who_can_move) {
									if (if_you_can_eat_you_must_eat(checkers_on_board_inter.get_checker(i).get_color())) {
										int s = 0;
										for (int f : who_must_eat) {
											if (f == i) {
												s++;
											}
										}
										if (s == 0) {
											error_choise_checker(_window, _event);
											checkers_on_board_inter.delete_backlight();
											return;
										}
									}
									choiseChecker = i;
									select_is_made = 1;
									checkers_on_board_inter.get_checker(choiseChecker).select_checker();
									x = checkers_on_board_inter.get_checker(choiseChecker).get_x();
									y = checkers_on_board_inter.get_checker(choiseChecker).get_y();
									if (checkers_on_board_inter.get_checker(choiseChecker).get_queen()) {
										queen_square_for_move(checkers_on_board_inter.get_checker(choiseChecker).get_color(), 1, 1, 1, 1);
									}
									else {
										square_for_move();
									}
									return;
								}
							}
						}
					}
				}
			}
		}
	}

	void change_position(RenderWindow& _window, Event _event) {//��� �����
		if (_event.type == sf::Event::MouseButtonPressed) 
		{
			if (_event.key.code == Mouse::Right && mode != "International") 
			{
				if (checkers_on_board.get_checker(choiseChecker).get_select() == 1 && select_is_made == 1) {
					set_mause_position(_window);
					if (checkers_on_board.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).get_backlight()) {
						checkers_on_board.get_board().get_all_squares(x, y).square_free();
						if (checkers_on_board.get_checker(choiseChecker).get_queen() == 1) {
							checkers_on_board.get_checker(choiseChecker).set_position(centre_on_square().x, centre_on_square().y);
							if (queen_eat_checker()) {
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								checkers_on_board.delete_backlight();
								if (queen_square_for_move(checkers_on_board.get_checker(choiseChecker).get_color(), 1, 1, 1, 1)) 
									return;
							}
						}
						else {
							checkers_on_board.get_checker(choiseChecker).set_position(centre_on_square().x, centre_on_square().y);
							make_queen();
							if (eat_checker()) {
								checkers_on_board.delete_backlight();
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								if (!chance_eat_checker(checkers_on_board.get_checker(choiseChecker).get_color())) {
									return;
								}
							}
						}
						checkers_on_board.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).square_employment(checkers_on_board.get_checker(choiseChecker).get_color());
						who_can_move = !who_can_move;
						checkers_on_board.get_checker(choiseChecker).leave_checker();
						select_is_made = 0;
						checkers_on_board.delete_backlight();
						return;
					}
				}
			}
			else
			{
				if (checkers_on_board_inter.get_checker(choiseChecker).get_select() == 1 && select_is_made == 1) {
					set_mause_position(_window);
					if (checkers_on_board_inter.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).get_backlight()) {
						checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();
						if (checkers_on_board_inter.get_checker(choiseChecker).get_queen() == 1) {
							checkers_on_board_inter.get_checker(choiseChecker).set_position(centre_on_square().x, centre_on_square().y);
							if (queen_eat_checker()) {
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								checkers_on_board_inter.delete_backlight();
								if (queen_square_for_move(checkers_on_board_inter.get_checker(choiseChecker).get_color(), 1, 1, 1, 1))
									return;
							}
						}
						else {
							checkers_on_board_inter.get_checker(choiseChecker).set_position(centre_on_square().x, centre_on_square().y);
							make_queen();
							if (eat_checker()) {
								checkers_on_board_inter.delete_backlight();
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								if (!chance_eat_checker(checkers_on_board_inter.get_checker(choiseChecker).get_color())) {
									return;
								}
							}
						}
						checkers_on_board_inter.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).
						square_employment(checkers_on_board_inter.get_checker(choiseChecker).get_color());
						who_can_move = !who_can_move;
						checkers_on_board_inter.get_checker(choiseChecker).leave_checker();
						select_is_made = 0;
						checkers_on_board_inter.delete_backlight();
						return;
					}
				}
			}
		}
	}

	void make_move(RenderWindow& _window, Event _event) {
		choise_of_chacker(_window, _event);
		change_position(_window, _event);
	}

	void square_for_move() {//�������� ����
		if(mode != "International")
		{
			if (checkers_on_board.get_checker(choiseChecker).get_color()) {
				if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0) {
					if (end_board(x + 1, y + 1)) {
						checkers_on_board.get_board().get_all_squares(x + 1, y + 1).on_backlight();
					}
				}
				if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment() == 0) {
					if (end_board(x - 1, y + 1)) {
						checkers_on_board.get_board().get_all_squares(x - 1, y + 1).on_backlight();
					}
				}
			}
			else {
				if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment() == 0) {
					if (end_board(x + 1, y - 1)) {
						checkers_on_board.get_board().get_all_squares(x + 1, y - 1).on_backlight();
					}
				}
				if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment() == 0) {
					if (end_board(x - 1, y - 1)) {
						checkers_on_board.get_board().get_all_squares(x - 1, y - 1).on_backlight();
					}
				}
			}
			if (!chance_eat_checker(checkers_on_board.get_checker(choiseChecker).get_color())) {//�������� ������ �����
				checkers_on_board.delete_backlight();
				chance_eat_checker(checkers_on_board.get_checker(choiseChecker).get_color());
			}
		}
		else
		{
			if (checkers_on_board_inter.get_checker(choiseChecker).get_color()) {
				if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0) {
					if (end_board(x + 1, y + 1)) {
						checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).on_backlight();
					}
				}
				if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_employment() == 0) {
					if (end_board(x - 1, y + 1)) {
						checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).on_backlight();
					}
				}
			}
			else {
				if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_employment() == 0) {
					if (end_board(x + 1, y - 1)) {
						checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).on_backlight();
					}
				}
				if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_employment() == 0) {
					if (end_board(x - 1, y - 1)) {
						checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).on_backlight();
					}
				}
			}
			if (!chance_eat_checker(checkers_on_board_inter.get_checker(choiseChecker).get_color())) {//�������� ������ �����
				checkers_on_board_inter.delete_backlight();
				chance_eat_checker(checkers_on_board_inter.get_checker(choiseChecker).get_color());
			}
		}
		
	}

	bool chance_eat_checker(bool _color) {//�������� ������ �����
		//std::string word = mode;
		if (mode == "Russian" || mode == "Giveaway")
			return chance_eat_checker_Russian(_color);

		if (mode == "Checkers")
			return chance_eat_checker_Checkers(_color);

		return  chance_eat_checker_Inter(_color);
	}

	bool chance_eat_checker_Inter(bool _color) {//�������� ������ �����
		bool more = 1;
		if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_employment()) {
			if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != _color) {
				if (checkers_on_board_inter.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0) {
					if (end_board(x + 2, y + 2)) {
						checkers_on_board_inter.get_board().get_all_squares(x + 2, y + 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_employment()) {
			if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != _color) {
				if (checkers_on_board_inter.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0) {
					if (end_board(x - 2, y + 2)) {
						checkers_on_board_inter.get_board().get_all_squares(x - 2, y + 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_employment()) {
			if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != _color) {
				if (checkers_on_board_inter.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0) {
					if (end_board(x + 2, y - 2)) {
						checkers_on_board_inter.get_board().get_all_squares(x + 2, y - 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_employment()) {
			if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != _color) {
				if (checkers_on_board_inter.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0) {
					if (end_board(x - 2, y - 2)) {
						checkers_on_board_inter.get_board().get_all_squares(x - 2, y - 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		return more;
	}

	bool chance_eat_checker_Checkers(bool _color) {//�������� ������ �����
		bool more = 1;
		if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != _color && _color == true) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0) {
					if (end_board(x + 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y + 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != _color && _color == true) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0) {
					if (end_board(x - 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y + 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != _color && _color == false) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0) {
					if (end_board(x + 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y - 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != _color && _color == false) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0) {
					if (end_board(x - 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y - 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		return more;
	}

	bool chance_eat_checker_Russian(bool _color)//�������� ������ �����
	{
		bool more = 1;
		if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != _color) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0) {
					if (end_board(x + 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y + 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != _color) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0) {
					if (end_board(x - 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y + 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != _color) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0) {
					if (end_board(x + 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y - 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != _color) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0) {
					if (end_board(x - 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y - 2).on_backlight();
						more = 0;
					}
				}
			}
		}
		return more;
	}

	bool eat_checker()
	{//�� �����
		if (mode == "International")
			return eat_checker_inter();

		if ((centre_on_square().x - 57) / 50 - x == 2 || (centre_on_square().x - 57) / 50 - x == -2 &&
			(centre_on_square().y - 57) / 50 - y == 2 || (centre_on_square().y - 57) / 50 - y == -2) {
			for (int i = 0; i < checkers_on_board.get_size(); i++) {
				if (checkers_on_board.get_checker(i).get_x() == x + (checkers_on_board.get_checker(choiseChecker).get_x() - x) / 2 &&
					checkers_on_board.get_checker(i).get_y() == y + (checkers_on_board.get_checker(choiseChecker).get_y() - y) / 2) {
					checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(i).get_x(), checkers_on_board.get_checker(i).get_y()).square_free();
					for (int j = i; j < checkers_on_board.get_size() - 1; j++) {
						checkers_on_board.get_checker(j) = checkers_on_board.get_checker(j + 1);
					}
					checkers_on_board.delete_checker();
					if (i < choiseChecker) {
						choiseChecker = choiseChecker - 1;
					}
					return 1;
				}
			}
		}
		return 0;
	}

	bool eat_checker_inter()
	{//�� �����
		if ((centre_on_square().x - 57) / 50 - x == 2 || (centre_on_square().x - 57) / 50 - x == -2 &&
			(centre_on_square().y - 57) / 50 - y == 2 || (centre_on_square().y - 57) / 50 - y == -2) {
			for (int i = 0; i < checkers_on_board_inter.get_size(); i++) {
				if (checkers_on_board_inter.get_checker(i).get_x() == x + (checkers_on_board_inter.get_checker(choiseChecker).get_x() - x) / 2 &&
					checkers_on_board_inter.get_checker(i).get_y() == y + (checkers_on_board_inter.get_checker(choiseChecker).get_y() - y) / 2) {
					checkers_on_board_inter.get_board().get_all_squares(checkers_on_board_inter.get_checker(i).get_x(), checkers_on_board_inter.get_checker(i).get_y()).square_free();
					for (int j = i; j < checkers_on_board_inter.get_size() - 1; j++) {
						checkers_on_board_inter.get_checker(j) = checkers_on_board_inter.get_checker(j + 1);
					}
					checkers_on_board_inter.delete_checker();
					if (i < choiseChecker) {
						choiseChecker = choiseChecker - 1;
					}
					return 1;
				}
			}
		}
		return 0;
	}

	void make_queen() {
		if(mode == "International")
			make_queen_inter();
		else
		{
			if (checkers_on_board.get_checker(choiseChecker).get_color() == 0) {
				if (checkers_on_board.get_checker(choiseChecker).get_y() == 0) {
					checkers_on_board.get_checker(choiseChecker).make_queen();
				}
			}
			if (checkers_on_board.get_checker(choiseChecker).get_color() == 1) {
				if (checkers_on_board.get_checker(choiseChecker).get_y() == 7) {
					checkers_on_board.get_checker(choiseChecker).make_queen();
				}
			}
		}
	}

	void make_queen_inter() {
		if (checkers_on_board_inter.get_checker(choiseChecker).get_color() == 0 && size(who_must_eat) == 0) {
			if (checkers_on_board_inter.get_checker(choiseChecker).get_y() == 0) {
				checkers_on_board_inter.get_checker(choiseChecker).make_queen();
			}
		}
		if (checkers_on_board_inter.get_checker(choiseChecker).get_color() == 1 && size(who_must_eat) == 0) {
			if (checkers_on_board_inter.get_checker(choiseChecker).get_y() == 9) {
				checkers_on_board_inter.get_checker(choiseChecker).make_queen();
			}
		}
	}

	bool queen_square_for_move(bool _color, int _i1, int _i2, int _i3, int _i4) {//�������� ���� �����
		if (mode == "Russian" || mode == "Giveaway")
			return queen_square_for_move_Russian(_color, _i1, _i2, _i3, _i4);

		if (mode == "Checkers")
			return queen_square_for_move_Checkers(_color, _i1, _i2, _i3, _i4);

		return queen_square_for_move_Inter(_color, _i1, _i2, _i3, _i4);
	}

	bool queen_square_for_move_Inter(bool _color, int _i1, int _i2, int _i3, int _i4) {//�������� ���� �����
		int must_eat = 0;
		bool can_eat[4] = { _i1, _i2, _i3, _i4 };
		checkers_on_board_inter.delete_backlight();
		int x_queen = x;
		int y_queen = y;
		if (can_eat[0]) {
			can_eat[0] = 0;
			while (1) {
				if (end_board(x_queen + 1, y_queen + 1)) {
					if (checkers_on_board_inter.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_employment() == 1) {
						if (checkers_on_board_inter.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board_inter.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen + 2)) {
								if (checkers_on_board_inter.get_board().get_all_squares(x_queen + 2, y_queen + 2).get_employment() == 0) {
									checkers_on_board_inter.get_board().get_all_squares(x_queen + 2, y_queen + 2).on_backlight();
									x_queen = x_queen + 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[0] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board_inter.get_board().get_all_squares(x_queen + 1, y_queen + 1).on_backlight();
						x_queen = x_queen + 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[1]) {
			can_eat[1] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen + 1)) {
					if (checkers_on_board_inter.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_employment() == 1) {
						if (checkers_on_board_inter.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board_inter.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen + 2)) {
								if (checkers_on_board_inter.get_board().get_all_squares(x_queen - 2, y_queen + 2).get_employment() == 0) {
									checkers_on_board_inter.get_board().get_all_squares(x_queen - 2, y_queen + 2).on_backlight();
									x_queen = x_queen - 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[1] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board_inter.get_board().get_all_squares(x_queen - 1, y_queen + 1).on_backlight();
						x_queen = x_queen - 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[2]) {
			can_eat[2] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen + 1, y_queen - 1)) {
					if (checkers_on_board_inter.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_employment() == 1) {
						if (checkers_on_board_inter.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board_inter.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen - 2)) {
								if (checkers_on_board_inter.get_board().get_all_squares(x_queen + 2, y_queen - 2).get_employment() == 0) {
									checkers_on_board_inter.get_board().get_all_squares(x_queen + 2, y_queen - 2).on_backlight();
									x_queen = x_queen + 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[2] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board_inter.get_board().get_all_squares(x_queen + 1, y_queen - 1).on_backlight();
						x_queen = x_queen + 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (can_eat[3]) {
			can_eat[3] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen - 1)) {
					if (checkers_on_board_inter.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_employment() == 1) {
						if (checkers_on_board_inter.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board_inter.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen - 2)) {
								if (checkers_on_board_inter.get_board().get_all_squares(x_queen - 2, y_queen - 2).get_employment() == 0) {
									checkers_on_board_inter.get_board().get_all_squares(x_queen - 2, y_queen - 2).on_backlight();
									x_queen = x_queen - 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[3] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board_inter.get_board().get_all_squares(x_queen - 1, y_queen - 1).on_backlight();
						x_queen = x_queen - 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (must_eat == 0) {
			return 0;
		}
		else {
			if (_i1 == 1 && _i2 == 1 && _i3 == 1 && _i4 == 1) {
				queen_square_for_move(_color, can_eat[0], can_eat[1], can_eat[2], can_eat[3]);
			}
			else return 1;
		}
	}

	bool queen_square_for_move_Checkers(bool _color, int _i1, int _i2, int _i3, int _i4) {//�������� ���� �����
		int must_eat = 0;
		bool can_eat[4] = { _i1, _i2, _i3, _i4 };
		checkers_on_board.delete_backlight();
		int x_queen = x;
		int y_queen = y;
		if (can_eat[0]) {
			can_eat[0] = 0;
			while ((abs(x_queen - x) < 2 && abs(y_queen - y) < 2)) {
				if (end_board(x_queen + 1, y_queen + 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen + 2) && (abs(x_queen - x) == 0 && abs(y_queen - y) == 0)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).get_employment() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).on_backlight();
									x_queen = x_queen + 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[0] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).on_backlight();
						x_queen += 1;
						y_queen += 1;
					}
				}
				else break;
			}
		}
		if (can_eat[1]) {
			can_eat[1] = 0;
			x_queen = x;
			y_queen = y;
			while (abs(x_queen - x) < 2 && abs(y_queen - y) < 2) {
				if (end_board(x_queen - 1, y_queen + 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen + 2) && (abs(x_queen - x) == 0 && abs(y_queen - y) == 0)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).get_employment() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).on_backlight();
									x_queen = x_queen - 2;
									y_queen = y_queen + 2;
									can_eat[1] = 1;
									must_eat++;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).on_backlight();
						x_queen -= 1;
						y_queen += 1;
					}
				}
				else break;
			}
		}
		if (can_eat[2]) {
			can_eat[2] = 0;
			x_queen = x;
			y_queen = y;
			while (abs(x_queen - x) < 2 && abs(y_queen - y) < 2) {
				if (end_board(x_queen + 1, y_queen - 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen - 2) && (abs(x_queen - x) == 0 && abs(y_queen - y) == 0)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).get_employment() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).on_backlight();
									x_queen = x_queen + 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[2] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).on_backlight();
						x_queen += 1;
						y_queen -= 1;
					}
				}
				else break;
			}
		}
		if (can_eat[3]) {
			can_eat[3] = 0;
			x_queen = x;
			y_queen = y;
			while (abs(x_queen - x) < 2 && abs(y_queen - y) < 2) {
				if (end_board(x_queen - 1, y_queen - 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen - 2) && (abs(x_queen - x) == 0 && abs(y_queen - y) == 0)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).get_employment() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).on_backlight();
									x_queen = x_queen - 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[3] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).on_backlight();
						x_queen -= 1;
						y_queen -= 1;
					}
				}
				else break;
			}
		}
		if (must_eat == 0)
			return 0;

		if (_i1 == 1 && _i2 == 1 && _i3 == 1 && _i4 == 1)
			queen_square_for_move(_color, can_eat[0], can_eat[1], can_eat[2], can_eat[3]);

		return 1;
	}

	bool queen_square_for_move_Russian(bool _color, int _i1, int _i2, int _i3, int _i4) {//�������� ���� �����
		int must_eat = 0;
		bool can_eat[4] = { _i1, _i2, _i3, _i4 };
		checkers_on_board.delete_backlight();
		int x_queen = x;
		int y_queen = y;
		if (can_eat[0]) {
			can_eat[0] = 0;
			while (1) {
				if (end_board(x_queen + 1, y_queen + 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen + 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).get_employment() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).on_backlight();
									x_queen = x_queen + 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[0] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).on_backlight();
						x_queen = x_queen + 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[1]) {
			can_eat[1] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen + 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen + 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).get_employment() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).on_backlight();
									x_queen = x_queen - 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[1] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).on_backlight();
						x_queen = x_queen - 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[2]) {
			can_eat[2] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen + 1, y_queen - 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen - 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).get_employment() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).on_backlight();
									x_queen = x_queen + 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[2] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).on_backlight();
						x_queen = x_queen + 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (can_eat[3]) {
			can_eat[3] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen - 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen - 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).get_employment() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).on_backlight();
									x_queen = x_queen - 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[3] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).on_backlight();
						x_queen = x_queen - 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (must_eat == 0) {
			return 0;
		}
		else {
			if (_i1 == 1 && _i2 == 1 && _i3 == 1 && _i4 == 1) {
				queen_square_for_move(_color, can_eat[0], can_eat[1], can_eat[2], can_eat[3]);
			}
			else return 1;
		}
	}

	bool queen_eat_checker() //�� �����
	{
		if (mode == "International")
			return queen_eat_checker_inter();

		int x_eat = 0;
		int y_eat = 0;
		if ((centre_on_square().x - 57) / 50 - x >= 2 && (centre_on_square().y - 57) / 50 - y >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 57) / 50 - 1 && j < (centre_on_square().y - 57) / 50 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j + 1).get_employment() == 1) {
						x_eat = i + 1;
						y_eat = j + 1;
						break;
					}
					else {
						i++;
						j++;
					}
				}
				else break;
			}
		}
		if ((centre_on_square().x - 57) / 50 - x >= 2 && y - (centre_on_square().y - 57) / 50 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 57) / 50 - 1 && j >(centre_on_square().y - 57) / 50 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j - 1).get_employment() == 1) {
						x_eat = i + 1;
						y_eat = j - 1;
						break;
					}
					else {
						i++;
						j--;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 57) / 50 >= 2 && (centre_on_square().y - 57) - y / 50 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 57) / 50 + 1 && j < (centre_on_square().y - 57) / 50 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j + 1).get_employment() == 1) {
						x_eat = i - 1;
						y_eat = j + 1;
						break;
					}
					else {
						i--;
						j++;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 57) / 50 >= 2 && y - (centre_on_square().y - 57) / 50 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 57) / 50 + 1 && j > (centre_on_square().y - 57) / 50 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j - 1).get_employment() == 1) {
						x_eat = i - 1;
						y_eat = j - 1;
						break;
					}
					else {
						i--;
						j--;
					}
				}
				else break;
			}
		}

		for (int f = 0; f < checkers_on_board.get_size(); f++) {
			if (checkers_on_board.get_checker(f).get_x() == x_eat && checkers_on_board.get_checker(f).get_y() == y_eat) {
				checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(f).get_x(), checkers_on_board.get_checker(f).get_y()).square_free();

				for (int c = f; c < checkers_on_board.get_size() - 1; c++) {
					checkers_on_board.get_checker(c) = checkers_on_board.get_checker(c + 1);
				}
				checkers_on_board.delete_checker();
				if (f < choiseChecker) {
					choiseChecker = choiseChecker - 1;
				}
				return 1;
			}
		}
		return 0;
	}

	bool queen_eat_checker_inter() //�� �����
	{
		int x_eat = 0;
		int y_eat = 0;
		if ((centre_on_square().x - 57) / 50 - x >= 2 && (centre_on_square().y - 57) / 50 - y >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 57) / 50 - 1 && j < (centre_on_square().y - 57) / 50 - 1) {
					if (checkers_on_board_inter.get_board().get_all_squares(i + 1, j + 1).get_employment() == 1) {
						x_eat = i + 1;
						y_eat = j + 1;
						break;
					}
					else {
						i++;
						j++;
					}
				}
				else break;
			}
		}
		if ((centre_on_square().x - 57) / 50 - x >= 2 && y - (centre_on_square().y - 57) / 50 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 57) / 50 - 1 && j >(centre_on_square().y - 57) / 50 + 1) {
					if (checkers_on_board_inter.get_board().get_all_squares(i + 1, j - 1).get_employment() == 1) {
						x_eat = i + 1;
						y_eat = j - 1;
						break;
					}
					else {
						i++;
						j--;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 57) / 50 >= 2 && (centre_on_square().y - 57) - y / 50 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 57) / 50 + 1 && j < (centre_on_square().y - 57) / 50 - 1) {
					if (checkers_on_board_inter.get_board().get_all_squares(i - 1, j + 1).get_employment() == 1) {
						x_eat = i - 1;
						y_eat = j + 1;
						break;
					}
					else {
						i--;
						j++;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 57) / 50 >= 2 && y - (centre_on_square().y - 57) / 50 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 57) / 50 + 1 && j > (centre_on_square().y - 57) / 50 + 1) {
					if (checkers_on_board_inter.get_board().get_all_squares(i - 1, j - 1).get_employment() == 1) {
						x_eat = i - 1;
						y_eat = j - 1;
						break;
					}
					else {
						i--;
						j--;
					}
				}
				else break;
			}
		}

		for (int f = 0; f < checkers_on_board_inter.get_size(); f++) {
			if (checkers_on_board_inter.get_checker(f).get_x() == x_eat && checkers_on_board_inter.get_checker(f).get_y() == y_eat) {
				checkers_on_board_inter.get_board().get_all_squares(checkers_on_board_inter.get_checker(f).get_x(), checkers_on_board_inter.get_checker(f).get_y()).square_free();

				for (int c = f; c < checkers_on_board_inter.get_size() - 1; c++) {
					checkers_on_board_inter.get_checker(c) = checkers_on_board_inter.get_checker(c + 1);
				}
				checkers_on_board_inter.delete_checker();
				if (f < choiseChecker) {
					choiseChecker = choiseChecker - 1;
				}
				return 1;
			}
		}
		return 0;
	}

	bool end_board(float _x, float _y)
	{//�������� ������ �� ������� ����
		int maxSize = mode == "International" ? 10 : 8;
		if (_x >= 0 && _x < maxSize && _y >= 0 && _y < maxSize)
			return 1;

		return 0;
	}

	bool if_you_can_eat_you_must_eat(bool _color)
	{
		if (mode == "International")
			return if_you_can_eat_you_must_eat_inter(_color);

		while (who_must_eat.size() != 0) {
			who_must_eat.pop_back();
		}
		for (int i = 0; i < checkers_on_board.get_size(); i++) {
			if (checkers_on_board.get_checker(i).get_color() == _color) {
				if (checkers_on_board.get_checker(i).get_queen() == 0) {
					x = checkers_on_board.get_checker(i).get_x();
					y = checkers_on_board.get_checker(i).get_y();
					if (!chance_eat_checker(_color)) {
						who_must_eat.push_back(i);
					}
				}
				if (checkers_on_board.get_checker(i).get_queen() == 1) {
					x = checkers_on_board.get_checker(i).get_x();
					y = checkers_on_board.get_checker(i).get_y();
					if (queen_square_for_move(_color, 1, 1, 1, 1)) {
						who_must_eat.push_back(i);
					}
				}
			}
		}
		checkers_on_board.delete_backlight();
		if (who_must_eat.size() != 0) return 1;
		return 0;
	}

	bool if_you_can_eat_you_must_eat_inter(bool _color) {
		while (who_must_eat.size() != 0) {
			who_must_eat.pop_back();
		}
		for (int i = 0; i < checkers_on_board_inter.get_size(); i++) {
			if (checkers_on_board_inter.get_checker(i).get_color() == _color) {
				if (checkers_on_board_inter.get_checker(i).get_queen() == 0) {
					x = checkers_on_board_inter.get_checker(i).get_x();
					y = checkers_on_board_inter.get_checker(i).get_y();
					if (!chance_eat_checker(_color)) {
						who_must_eat.push_back(i);
					}
				}
				if (checkers_on_board_inter.get_checker(i).get_queen() == 1) {
					x = checkers_on_board_inter.get_checker(i).get_x();
					y = checkers_on_board_inter.get_checker(i).get_y();
					if (queen_square_for_move(_color, 1, 1, 1, 1)) {
						who_must_eat.push_back(i);
					}
				}
			}
		}
		checkers_on_board_inter.delete_backlight();
		if (who_must_eat.size() != 0) return 1;
		return 0;
	}

	void error_choise_checker(RenderWindow& _window, Event _event) {
		while (1) {
			RectangleShape back = RectangleShape(Vector2f(170, 50));
			back.setFillColor(Color(245, 210, 175));
			back.setPosition(165, 225);
			Font font;
			font.loadFromFile("Font//bahnschrift.ttf");
			Text t = Text("", font, 25);
			t.setString(L"Eat necessary");
			t.setFillColor(Color::Black);
			t.setPosition(172, 235);
			_window.draw(back);
			_window.draw(t);
			_window.display();
			while (_window.pollEvent(_event)) {
				if (_event.type == sf::Event::MouseButtonPressed || _event.type == sf::Event::KeyPressed) {
					return;
				}
			}
		}
	}

	void start_game(RenderWindow& _window, Event _event, bool& _start) {
		while (1) {
			_start = 0;
			return;
		}
	}

	bool end_game(RenderWindow& _window, Event _event) {
		int black = 0;
		int white = 0;
		if(mode == "International")
		{
			for (int i = 0; i < checkers_on_board.get_size(); i++) {
				if (checkers_on_board.get_checker(i).get_color() == 0) {
					white++;
				}
				if (checkers_on_board.get_checker(i).get_color() == 1) {
					black++;
				}
			}
		}
		else
		{
			for (int i = 0; i < checkers_on_board.get_size(); i++) {
				if (checkers_on_board.get_checker(i).get_color() == 0) {
					white++;
				}
				if (checkers_on_board.get_checker(i).get_color() == 1) {
					black++;
				}
			}
		}

		if (white == 0) {
			RectangleShape back = RectangleShape(Vector2f(350, 150));
			back.setFillColor(Color(245, 210, 175));
			back.setPosition(75, 175);
			Font font;
			font.loadFromFile("Font//bahnschrift.ttf");
			Text t = Text("", font, 81);
			t.setString(mode == "Giveaway" ? L"White win" : L"Black win");
			t.setFillColor(Color::Black);
			t.setPosition(78, 190);
			_window.draw(back);
			_window.draw(t);
			if (_event.type == Event::Closed)
				_window.close();
			return 0;
		}
		if (black == 0) {
			RectangleShape back = RectangleShape(Vector2f(350, 150));
			back.setFillColor(Color(245, 210, 175));
			back.setPosition(75, 175);
			Font font;
			font.loadFromFile("Font//bahnschrift.ttf");
			Text t = Text("", font, 81);
			t.setString(mode == "Giveaway" ? L"Black win" : L"White win");
			t.setFillColor(Color::Black);
			t.setPosition(75, 190);
			_window.draw(back);
			_window.draw(t);
			if (_event.type == Event::Closed)
				_window.close();
			return 0;
		}
		return 1;
	}
};
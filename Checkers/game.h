#pragma once
#include <SFML/Graphics.hpp>
#include "Checkers_on_board.h"
#include "Checkers_on_board_Inter.h"
#include <string>
#include <fstream>
#include "menu.h"
#include <Windows.h>
using namespace sf;

void winDisplay(RenderWindow& window, wstring guestName)
{
	Texture fons;
	fons.loadFromFile("images/fon8.jpg");
	Sprite fon(fons);
	sf::Font font1;
	font1.loadFromFile("Font//Deutsch Gothic.ttf");
	sf::Font font2;
	font2.loadFromFile("Font//bahnschrift.ttf");

	ifstream in("score.txt");
	int master_score = 0;
	int slave_score = 0;
	in >> master_score;
	in.ignore(1);
	in >> slave_score;
	in.close();
	wstring score = to_wstring(master_score) + L"-" + to_wstring(slave_score);

	wifstream input("user.txt");
	wstring str;
	input >> str;
	input.close();
	sf::Text textMaster(L"Победил: ", font2, 40);
	textMaster.setFillColor(sf::Color::Black);
	textMaster.setStyle(sf::Text::Bold);
	textMaster.setOutlineColor(sf::Color::White);
	textMaster.setOutlineThickness(1);
	textMaster.setPosition(200, 100);

	int posColon = str.find(L":");
	posColon++;
	int posDiv = str.find(L"|");
	wstring masterName;

	while (posColon < posDiv) {
		masterName += str[posColon];
		posColon++;
	}

	bool masterWin = false;
	bool slaveWin = false;
	bool paritet = false;
	if (master_score > slave_score) {
		masterWin = true;
	}
	else if (master_score < slave_score)  {
		slaveWin = false;
	}
	else {
		paritet = true;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				return;
			}
		}
		if (masterWin) {
			textMaster.setString(L"Победил: \n" + masterName + L"\nсо счётом: " + score);
		}
		if (slaveWin) {
			textMaster.setString(L"Победил: \n" + guestName + L"\nсо счётом: " + score);
		}
		if (paritet) {
			textMaster.setString(L"Ничья!\n" + score);	
		}
		window.draw(fon);
		window.draw(textMaster);
		window.display();
	}
}
class Game {
private:
	size_t amountSteps = 1;
	int how_many = 0;
	bool flag = false;//переменная хранит, был ли первый ход
	bool who_can_move = 0;//цвет хода, 0 если ход белых, 1 если ход черных
	bool select_is_made = 0;//0 если фигуры не выбрана, 1 если выбрана
	int choiseChecker;//номер выбранной для хода шашки
	std::string mode;//режим игры
	std::string rounds;//количество раундов
	std::string colorChecker;//Цвет шашек
	std::wstring regime;
	std::wstring guestName;
	float x;//номер клетки в которой шашка по оси х
	float y;//номер клетки в которой шашка по оси у
	Vector2i mousePosition;//позиция мыши
	Checkers_on_board checkers_on_board;
	Checkers_on_board_Inter checkers_on_board_inter;
	vector <int> who_must_eat;//храню шашки, которые могут съесть
	size_t time; //время игры в секундах.
public:
	std::string getMode() { return mode; }
	std::string getColor() { return colorChecker; }
	size_t getAmountOfSteps() { return amountSteps; }

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
	Checkers_on_board& get_checkers_on_board() { return this->checkers_on_board; }

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
		if (mode == "Checkers" && flag == false)
		{
			this->who_can_move = 1;
			flag = true;
		}
		//для проверки на работоспособность,
		//заменить условие на - (mode == "Checkers" && who_can_move == 2) и переменной who_can_move присвоить по умолчанию 2
	}

	void choise_of_chacker(RenderWindow& _window, Event _event) {
		if (mode != "International")
		{
			if (_event.type == sf::Event::MouseButtonPressed) {
				if (_event.key.code == Mouse::Left) {
					set_mause_position(_window);
					if (_event.type == sf::Event::MouseButtonPressed) {//для отмены взятия фигуры
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
					if (_event.type == sf::Event::MouseButtonPressed) {//для отмены взятия фигуры
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

	void change_position(RenderWindow& _window, Event _event) {//ход шашки
		if (_event.type == sf::Event::MouseButtonPressed)
		{
			if (_event.key.code == Mouse::Right && mode != "International")
			{
				if (checkers_on_board.get_checker(choiseChecker).get_select() == 1 && select_is_made == 1) {
					set_mause_position(_window);
					if (checkers_on_board.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).get_backlight()) {
						ofstream out("ligth.txt");
						out << ++amountSteps << "|" << this->getColor() << "|" << this->getMode();
						out.close();
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
							ofstream out("ligth.txt");
							out << ++amountSteps << "|" << this->getColor() << "|" << this->getMode();
							out.close();
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

	void square_for_move() {//варианты хода
		if (mode != "International")
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
			if (!chance_eat_checker(checkers_on_board.get_checker(choiseChecker).get_color())) {//варианты съесть шашку
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
			if (!chance_eat_checker(checkers_on_board_inter.get_checker(choiseChecker).get_color())) {//варианты съесть шашку
				checkers_on_board_inter.delete_backlight();
				chance_eat_checker(checkers_on_board_inter.get_checker(choiseChecker).get_color());
			}
		}

	}

	bool chance_eat_checker(bool _color) {//варианты съесть шашку
		std::string word = mode;
		if (mode == "Russian" || mode == "Giveaway")
			return chance_eat_checker_Russian(_color);

		if (mode == "Checkers")
			return chance_eat_checker_Checkers(_color);
	}

	bool chance_eat_checker_Inter(bool _color) {//варианты съесть шашку
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

	bool chance_eat_checker_Checkers(bool _color) {//варианты съесть шашку
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

	bool chance_eat_checker_Russian(bool _color)//варианты съесть шашку
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
	{//ем шашку
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
	{//ем шашку
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
		if (mode == "International")
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
	bool queen_square_for_move(bool _color, int _i1, int _i2, int _i3, int _i4) {//варианты хода дамки
		if (mode == "Russian" || mode == "Giveaway")
			return queen_square_for_move_Russian(_color, _i1, _i2, _i3, _i4);

		if (mode == "Checkers")
			return queen_square_for_move_Checkers(_color, _i1, _i2, _i3, _i4);
		return queen_square_for_move_Inter(_color, _i1, _i2, _i3, _i4);
	}

	bool queen_square_for_move_Inter(bool _color, int _i1, int _i2, int _i3, int _i4) {//варианты хода дамки
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

	bool queen_square_for_move_Checkers(bool _color, int _i1, int _i2, int _i3, int _i4) {//варианты хода дамки
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

	bool queen_square_for_move_Russian(bool _color, int _i1, int _i2, int _i3, int _i4) {//варианты хода дамки
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

	bool queen_eat_checker() //ем шашку
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

	bool queen_eat_checker_inter() //ем шашку
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

	bool end_board(float _x, float _y) {//проверка выходы за пределы поля
		int maxSize = mode == "International" ? 10 : 8;
		if (_x >= 0 && _x < maxSize && _y >= 0 && _y < maxSize)
			return 1;

		return 0;
	}

	bool if_you_can_eat_you_must_eat(bool _color) {
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
		else return 0;
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
			//Text out = Text("", font, 11);
			//out.setString(L"press any key to continue");
			//out.setFillColor(Color::Black);
			//out.setPosition(173, 260);
			_window.draw(back);
			_window.draw(t);
			//_window.draw(out);
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


	bool end_game(RenderWindow &_window, Event _event) {
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

		int black = 0;
		int white = 0;
		if (mode == "International")
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
			if (theme == 0) {
				back.setFillColor(Color(245, 210, 175));
			}
			else {
				back.setFillColor(Color(110, 110, 110));
			}
			back.setPosition(75, 175);
			Font font;
			font.loadFromFile("Font//bahnschrift.ttf");
			Text t = Text("", font, 81);
			string whoWin = (mode == "Giveaway") ? "White win" : "Black win";
			t.setString(mode == "Giveaway" ? L"White win" : L"Black win");
			t.setFillColor(Color::Black);
			t.setPosition(78, 190);

			int roundS = stoi(rounds);

			_window.draw(back);
			_window.draw(t);
			_window.display();
			Sleep(3000);

			ifstream in("score.txt");
			int master_score = 0;
			int slave_score = 0;
			in>>master_score;
			in.ignore(1);
			in >> slave_score;
			in.close();

			if (whoWin == "White win" && this->getColor() == "white") {
				master_score += 1;
			}
			else if (whoWin == "White win" && this->getColor() == "black") {
				slave_score += 1;
			}
			else if (whoWin == "Black win" && this->getColor() == "black") {
				master_score += 1;
			}
			else {
				slave_score += 1;
			}

			ofstream out("score.txt");
			out << to_string(master_score) << "|" << to_string(slave_score);
			out.close();

			if (roundS > 1) {
				rounds = to_string(roundS - 1);
				ofstream out("gameSettings.txt");
				out << rounds << "|" << mode << "|" << colorChecker;
				out.close();
				playGame(_window);
			}
			else {
				winDisplay(_window, guestName);
				_window.close();
			}

			
			return 0;

		}
		if (black == 0) {
			RectangleShape back = RectangleShape(Vector2f(350, 150));
			if (theme == 0) {
				back.setFillColor(Color(245, 210, 175));
			}
			else {
				back.setFillColor(Color(110, 110, 110));
			}
			back.setPosition(75, 175);
			Font font;
			font.loadFromFile("Font//bahnschrift.ttf");
			Text t = Text("", font, 81);
			string whoWin = mode == "Giveaway" ? "Black win" : "White win";
			t.setString(mode == "Giveaway" ? L"Black win" : L"White win");
			t.setFillColor(Color::Black);
			t.setPosition(75, 190);
			int roundS = stoi(rounds);
			
			_window.draw(back);
			_window.draw(t);
			_window.display();
			Sleep(3000);

			ifstream in("score.txt");
			int master_score = 0;
			int slave_score = 0;
			in >> master_score;
			in.ignore(1);
			in >> slave_score;
			in.close();

			if (whoWin == "White win" && this->getColor() == "white") {
				master_score += 1;
			}
			else if (whoWin == "White win" && this->getColor() == "black") {
				slave_score += 1;
			}
			else if (whoWin == "Black win" && this->getColor() == "black") {
				master_score += 1;
			}
			else {
				slave_score += 1;
			}

			ofstream out("score.txt");
			out << to_string(master_score) << "|" << to_string(slave_score);
			out.close();

			if (roundS > 1) {
				rounds = to_string(roundS - 1);
				ofstream out("gameSettings.txt");
				out << rounds << "|" << mode << "|" << colorChecker;
				out.close();
				playGame(_window);
			}
			else {
				winDisplay(_window, guestName);
				_window.close();
			}

			return 0;
		}
		return 1;
	}
};
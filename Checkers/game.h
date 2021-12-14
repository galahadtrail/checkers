#pragma once
#include <SFML/Graphics.hpp>
#include "Checkers_on_board.h"
#include "Checkers_on_board_Inter.h"
#include <string>
#include <fstream>
#include "menu.h"
#include <Windows.h>
#include <map>
#include <algorithm>
#include <ctime>
using namespace sf;

//Починка гита у себя.

void winDisplay(RenderWindow & window, wstring guestName)
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
	sf::Text textMaster(L"�������: ", font2, 40);
	textMaster.setFillColor(sf::Color::Black);
	textMaster.setStyle(sf::Text::Bold);
	textMaster.setOutlineColor(sf::Color::White);
	textMaster.setOutlineThickness(1);
	textMaster.setPosition(200, 100);

	bool leave = false;
	sf::Text no(L"����� � ����", font2, 23);
	no.setFillColor(sf::Color::Black);
	no.setOutlineColor(sf::Color::White);
	no.setOutlineThickness(1);
	no.setStyle(sf::Text::Bold);
	no.setPosition(200, 250);

	bool restart = false;
	sf::Text res(L"�������", font2, 23);
	res.setFillColor(sf::Color::Black);
	res.setOutlineColor(sf::Color::White);
	res.setOutlineThickness(1);
	res.setStyle(sf::Text::Bold);
	res.setPosition(200, 300);

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
	else if (master_score < slave_score) {
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

			if (IntRect(200, 250, 120, 30).contains(Mouse::getPosition(window))) {
				no.setFillColor(sf::Color::Color(160, 70, 0));
				leave = true;
			}
			else {
				no.setFillColor(sf::Color::Black);
				leave = false;
			}
			if (IntRect(200, 300, 150, 30).contains(Mouse::getPosition(window))) {
				res.setFillColor(sf::Color::Color(160, 70, 0));
				restart = true;
			}
			else {
				res.setFillColor(sf::Color::Black);
				restart = false;
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (leave) {
					window.close();
					menu();
					return;
				}

				if (restart) {
					ifstream in("score.txt");
					int master_score = 0;
					int slave_score = 0;
					in >> master_score;
					in.ignore(1);
					in >> slave_score;
					in.close();
					if (master_score > slave_score) {
						master_score--;
					}
					else if ((master_score < slave_score)) {
						slave_score--;
					}
					else {
						master_score--;
						slave_score--;
					}

					ofstream output("score.txt");
					output << master_score << "|" << slave_score;
					output.close();

					playGame(window);
				}
			}
		}
		if (masterWin) {
			textMaster.setString(L"�������: \n" + masterName + L"\n�� ������: " + score);
		}
		if (slaveWin) {
			textMaster.setString(L"�������: \n" + guestName + L"\n�� ������: " + score);
		}
		if (paritet) {
			textMaster.setString(L"�����!\n" + score);
		}
		window.clear();
		window.draw(fon);
		window.draw(textMaster);
		window.draw(no);
		window.draw(res);
		window.display();
	}
}




class Game {
private:
	size_t amountSteps = 1;
	size_t computerSteps = 0;
	size_t count_eat = 0;
	int how_many = 0;
	int direction;
	int queenRequest = -1;
	bool condition_first_dir;//����������� ��� �������� �����, ��� ����������
	bool condition_sec_dir;
	bool condition_third_dir;
	bool condition_four_dir;
	vector<int> comp_checker_can_move;
	bool flag = false;//���������� ������, ��� �� ������ ���
	bool who_can_move = 0;//���� ����, 0 ���� ��� �����, 1 ���� ��� ������
	bool select_is_made = 0;//0 ���� ������ �� �������, 1 ���� �������
	int choiseChecker;//����� ��������� ��� ���� �����
	int bot_choiseChecker;//����� ��������� ��� ���� ����� �����������
	int bot_number_eat_checker = -1;//����� ��������� ����� �����������, ������� ����� ������
	std::string mode;//����� ����
	std::string rounds;//���������� �������
	std::string colorChecker;//���� �����
	std::string regime;//PvP ��� ������ ����������
	std::wstring guestName;// ��� ������� ������, ���� ������ PvP
	bool computerColor;//���� ����� ���������� 
	float x;//����� ������ � ������� ����� �� ��� �
	float y;//����� ������ � ������� ����� �� ��� �
	Vector2i mousePosition;//������� ����
	Checkers_on_board checkers_on_board;
	Checkers_on_board_Inter checkers_on_board_inter;
	vector <int> who_must_eat;//����� �����, ������� ����� ������
	//size_t time; //����� ���� � ��������.
public:
	size_t getAmountSteps() { return amountSteps; }
	std::string getMode() { return mode; }
	std::string getColor() { return colorChecker; }
	std::string getRegime() { return regime; }
	size_t getWhoCanMove() { return who_can_move; }

	//��������� �������� ���� �� �����
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

	//��������� ������ ���� �� �����
	void assignRegimeFromFile(std::string fileName)
	{
		ifstream in(fileName);
		std::string raw_result;
		in >> raw_result;
		in.close();
		size_t first = raw_result.find('|');
		int i = 0;
		std::string temp;
		while (i < first)
		{
			temp += raw_result[i];
			i++;
		}
		regime = temp;
		temp = "";
	}

	//��������� ����� 
	Checkers_on_board_Inter& get_checkers_on_board_inter() { return this->checkers_on_board_inter; }

	//��������� ����� � ������������� ������
	Checkers_on_board& get_checkers_on_board() { return this->checkers_on_board; }

	//������������ ������� ���� �� ������
	void set_mouse_position(RenderWindow& _window) {
		auto current = Mouse::getPosition(_window);
		double maxSize = mode == "International" ? 10.9 : 8.9;
		if (current.x > maxSize * 50 || current.y > maxSize * 50) {
			this->mousePosition = Vector2i(0, 0);
		}
		else
			this->mousePosition = Mouse::getPosition(_window);
	}

	Vector2i centre_on_square()
	{
		int maxSize = mode == "International" ? 10 : 8;
		for (int i = 0; i < maxSize; i++) {
			for (int j = 0; j < maxSize; j++) {
				if (mousePosition.x < i * 50 + 100 && mousePosition.y < j * 50 + 100) {
					return Vector2i(i * 50 + 57, j * 50 + 57);
				}
			}
		}
	}

	//������������ ����� ����� ��� ������� ����
	void set_who_can_move()
	{
		if (mode == "Checkers" && flag == false)
		{
			this->who_can_move = 1;
			flag = true;
		}
	}

	//����� ����� ��� ����
	void choise_of_chacker(RenderWindow& _window, Event _event)
	{
		if (mode == "International")
			return choise_of_chacker_inter(_window, _event);

		if (_event.type == sf::Event::MouseButtonPressed) {
			if (_event.key.code == Mouse::Left) {
				set_mouse_position(_window);
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

	//����� ����� ��� ���� � ������������� ������
	void choise_of_chacker_inter(RenderWindow& _window, Event _event)
	{
		if (_event.type == sf::Event::MouseButtonPressed) {
			if (_event.key.code == Mouse::Left) {
				set_mouse_position(_window);
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

	//��� �����
	void change_position(RenderWindow& _window, Event _event)
	{
		if(mode =="International")
			return change_position_inter(_window, _event);

		if (_event.type == sf::Event::MouseButtonPressed)
		{
			if (_event.key.code == Mouse::Right)
			{
				if (checkers_on_board.get_checker(choiseChecker).get_select() == 1 && select_is_made == 1) {
					set_mouse_position(_window);
					ofstream out("ligth.txt");
					out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
					out.close();
					if (checkers_on_board.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).get_backlight()) 
					{
						checkers_on_board.get_board().get_all_squares(x, y).square_free();
						if (checkers_on_board.get_checker(choiseChecker).get_queen() == 1) 
						{
							checkers_on_board.get_checker(choiseChecker).set_position(centre_on_square().x, centre_on_square().y);
							if (queen_eat_checker()) {
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								checkers_on_board.delete_backlight();
								if (queen_square_for_move(checkers_on_board.get_checker(choiseChecker).get_color(), 1, 1, 1, 1))
									return;
							}
						}
						else 
						{
							checkers_on_board.get_checker(choiseChecker).set_position(centre_on_square().x, centre_on_square().y);
							make_queen();
							if (eat_checker()) {
								checkers_on_board.delete_backlight();
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								if (!chance_eat_checker(checkers_on_board.get_checker(choiseChecker).get_color())) {
									queen_eat_checker();
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
		}
	}

	//��� ����� � ������������� ������
	void change_position_inter(RenderWindow& _window, Event _event)
	{
		if (_event.type == sf::Event::MouseButtonPressed)
		{
			if (_event.key.code == Mouse::Right)
			{
				if (checkers_on_board_inter.get_checker(choiseChecker).get_select() == 1 && select_is_made == 1) {
					set_mouse_position(_window);
					ofstream out("ligth.txt");
					out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
					out.close();
					if (checkers_on_board_inter.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).get_backlight())
					{
						checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();
						if (checkers_on_board_inter.get_checker(choiseChecker).get_queen() == 1)
						{
							checkers_on_board_inter.get_checker(choiseChecker).set_position(centre_on_square().x, centre_on_square().y);
							if (queen_eat_checker_inter()) {
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								checkers_on_board_inter.delete_backlight();
								if (queen_square_for_move(checkers_on_board_inter.get_checker(choiseChecker).get_color(), 1, 1, 1, 1))
									return;
							}
						}
						else
						{
							checkers_on_board_inter.get_checker(choiseChecker).set_position(centre_on_square().x, centre_on_square().y);
							make_queen_inter();
							if (eat_checker_inter()) {
								checkers_on_board_inter.delete_backlight();
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								if (!chance_eat_checker(checkers_on_board_inter.get_checker(choiseChecker).get_color())) {
									queen_eat_checker();
									return;
								}
							}
						}
						checkers_on_board_inter.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).square_employment(checkers_on_board_inter.get_checker(choiseChecker).get_color());
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

	//����� ���� �����, �������� ��������� ����� ������� 
	vector<int> bot_choise_chacker()
	{
		computerColor = colorChecker == "white" ? 1 : 0;
		vector<int> checkers_can_make_move;
		for (int i = 0; i < checkers_on_board.get_size(); i++)
		{
			if (checkers_on_board.get_checker(i).get_color() == computerColor)
			{
				x = checkers_on_board.get_checker(i).get_x();
				y = checkers_on_board.get_checker(i).get_y();
				if ((checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0 && end_board(x + 1, y + 1)) || 
					(checkers_on_board.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0 && end_board(x + 2, y + 2) && 
						checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != computerColor)) {
					checkers_can_make_move.push_back(i);
					continue;
				}
				if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment() == 0 && end_board(x - 1, y + 1) || 
					(checkers_on_board.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0 && end_board(x - 2, y + 2) &&
						checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != computerColor)) {
					checkers_can_make_move.push_back(i);
					continue;
				}
				if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment() == 0 && end_board(x + 1, y - 1) ||
					(checkers_on_board.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0 && end_board(x + 2, y - 2) &&
						checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != computerColor)) {
					checkers_can_make_move.push_back(i);
					continue;
				}
				if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment() == 0 && end_board(x - 1, y - 1) ||
					(checkers_on_board.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0 && end_board(x - 2, y - 2) &&
						checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != computerColor)) {
					checkers_can_make_move.push_back(i);
					continue;
				}
			}
		}

		return checkers_can_make_move;
	}

	//����� ���� �����, �������� ��������� ����� ������� � ������������� ������
	vector<int> bot_choise_chacker_inter()
	{
		computerColor = colorChecker == "white" ? 1 : 0;
		vector<int> checkers_can_make_move;
		for (int i = 0; i < checkers_on_board_inter.get_size(); i++)
		{
			if (checkers_on_board_inter.get_checker(i).get_color() == computerColor)
			{
				x = checkers_on_board_inter.get_checker(i).get_x();
				y = checkers_on_board_inter.get_checker(i).get_y();
				if ((checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0 && end_board(x + 1, y + 1)) ||
					(checkers_on_board_inter.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0 && end_board(x + 2, y + 2) &&
						checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != computerColor)) {
					checkers_can_make_move.push_back(i);
					continue;
				}
				if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_employment() == 0 && end_board(x - 1, y + 1) ||
					(checkers_on_board_inter.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0 && end_board(x - 2, y + 2) &&
						checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != computerColor)) {
					checkers_can_make_move.push_back(i);
					continue;
				}
				if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_employment() == 0 && end_board(x + 1, y - 1) ||
					(checkers_on_board_inter.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0 && end_board(x + 2, y - 2) &&
						checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != computerColor)) {
					checkers_can_make_move.push_back(i);
					continue;
				}
				if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_employment() == 0 && end_board(x - 1, y - 1) ||
					(checkers_on_board_inter.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0 && end_board(x - 2, y - 2) &&
						checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != computerColor)) {
					checkers_can_make_move.push_back(i);
					continue;
				}
			}
		}

		return checkers_can_make_move;
	}

	//������������ ����� �����������
	void bot_make_move()
	{
		if (mode == "International")
			return bot_make_move_inter();

		srand(time(NULL));
		comp_checker_can_move = bot_choise_chacker();//������ �� ����� ���������, ������� ����� �������
		if (comp_checker_can_move.size() == 0)//���� ������ ����, �� ��������� _gme
			return;

		int size = comp_checker_can_move.size();
		int random = rand();
		int randResult = rand() % comp_checker_can_move.size();

		bot_choiseChecker = comp_checker_can_move[randResult];//����� �����, ������� ����� ������ ���������  БАГ БАГ БАГБАГ БАГ БАГБАГ БАГ БАГБАГ БАГ БАГ
		bot_number_eat_checker = computerSteps == 0 ? -1 : bot_checker_which_eat(comp_checker_can_move);//�������� �����, ������� ����� �������
		if (bot_number_eat_checker != -1)
		{
			return bot_eat_checker();//����� ����� ������
		}

		if (bot_number_eat_checker != -1) {
			bot_number_eat_checker = -1;
		}

		//�������� ��� ������������ ����� �����������
		x = checkers_on_board.get_checker(bot_choiseChecker).get_x();
		y = checkers_on_board.get_checker(bot_choiseChecker).get_y();
		if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0 && end_board(x + 1, y + 1) && computerColor == 1)
		{
			ofstream out("ligth.txt");
			out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
			out.close();
			checkers_on_board.get_board().get_all_squares(x, y).square_free();
			checkers_on_board.get_checker(bot_choiseChecker).set_position(x * 50 + 107, y * 50 + 107);
			checkers_on_board.get_board().get_all_squares((x * 50 + 50) / 50, (y * 50 + 50) / 50).square_employment(checkers_on_board.get_checker(bot_choiseChecker).get_color());
			who_can_move = !who_can_move;


			queenRequest = 1;
			x = checkers_on_board.get_checker(bot_choiseChecker).get_x();
			y = checkers_on_board.get_checker(bot_choiseChecker).get_y();
			make_queen();
			queenRequest = -1;
			Sleep(500);
			computerSteps += 1;
			return;
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment() == 0 && end_board(x - 1, y + 1) && computerColor == 1)
		{
			ofstream out("ligth.txt");
			out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
			out.close();
			checkers_on_board.get_board().get_all_squares(x, y).square_free();
			checkers_on_board.get_checker(bot_choiseChecker).set_position(x * 50 + 7, y * 50 + 107);
			checkers_on_board.get_board().get_all_squares((x * 50 - 50) / 50, (y * 50 + 50) / 50).square_employment(checkers_on_board.get_checker(bot_choiseChecker).get_color());
			who_can_move = !who_can_move;


			queenRequest = 1;
			x = checkers_on_board.get_checker(bot_choiseChecker).get_x();
			y = checkers_on_board.get_checker(bot_choiseChecker).get_y();
			make_queen();
			queenRequest = -1;
			Sleep(500);
			computerSteps += 1;
			return;
		}
		if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment() == 0 && end_board(x + 1, y - 1) && computerColor == 0)
		{
			ofstream out("ligth.txt");
			out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
			out.close();
			checkers_on_board.get_board().get_all_squares(x, y).square_free();
			checkers_on_board.get_checker(bot_choiseChecker).set_position(x * 50 + 107, y * 50 + 7);
			checkers_on_board.get_board().get_all_squares((x * 50 + 50) / 50, (y * 50 - 50) / 50).square_employment(checkers_on_board.get_checker(bot_choiseChecker).get_color());
			who_can_move = !who_can_move;


			queenRequest = 1;
			x = checkers_on_board.get_checker(bot_choiseChecker).get_x();
			y = checkers_on_board.get_checker(bot_choiseChecker).get_y();
			make_queen();
			queenRequest = -1;
			Sleep(500);
			computerSteps += 1;
			return;
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment() == 0 && end_board(x - 1, y - 1) && computerColor == 0)
		{
			ofstream out("ligth.txt");
			out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
			out.close();
			checkers_on_board.get_board().get_all_squares(x, y).square_free();
			checkers_on_board.get_checker(bot_choiseChecker).set_position(x * 50 + 7, y * 50 + 7);
			checkers_on_board.get_board().get_all_squares((x * 50 - 50) / 50, (y * 50 - 50) / 50).square_employment(checkers_on_board.get_checker(bot_choiseChecker).get_color());
			who_can_move = !who_can_move;

			queenRequest = 1;
			x = checkers_on_board.get_checker(bot_choiseChecker).get_x();
			y = checkers_on_board.get_checker(bot_choiseChecker).get_y();
			make_queen();
			queenRequest = -1;
			Sleep(500);
			computerSteps += 1;
			return;
		}

		queenRequest = 1;
		x = checkers_on_board.get_checker(bot_choiseChecker).get_x();
		y = checkers_on_board.get_checker(bot_choiseChecker).get_y();
		make_queen();
		queenRequest = -1;
	}

	// ������������ ����� ����������� � ������������� ������
	void bot_make_move_inter()
	{
		srand(time(NULL));
		comp_checker_can_move = bot_choise_chacker_inter();//������ �� ����� ���������, ������� ����� �������
		if (comp_checker_can_move.size() == 0)//���� ������ ����, �� ��������� _gme
			return;

		bot_choiseChecker = comp_checker_can_move[rand() % comp_checker_can_move.size()];//����� �����, ������� ����� ������ ���������
		bot_number_eat_checker = computerSteps == 0 ? -1 : bot_checker_which_eat(comp_checker_can_move);//�������� �����, ������� ����� �������
		if (bot_number_eat_checker != -1)
		{
			return bot_eat_checker_inter();//����� ����� ������
		}

		//�������� ��� ������������ ����� �����������
		x = checkers_on_board_inter.get_checker(bot_choiseChecker).get_x();
		y = checkers_on_board_inter.get_checker(bot_choiseChecker).get_y();
		if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0 && end_board(x + 1, y + 1) && computerColor == 1)
		{
			ofstream out("ligth.txt");
			out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
			out.close();
			checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();
			checkers_on_board_inter.get_checker(bot_choiseChecker).set_position(x * 50 + 107, y * 50 + 107);
			checkers_on_board_inter.get_board().get_all_squares((x * 50 + 50) / 50, (y * 50 + 50) / 50).square_employment(checkers_on_board_inter.get_checker(bot_choiseChecker).get_color());
			who_can_move = !who_can_move;
			Sleep(500);
			computerSteps += 1;
			return;
		}
		if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_employment() == 0 && end_board(x - 1, y + 1) && computerColor == 1)
		{
			ofstream out("ligth.txt");
			out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
			out.close();
			checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();
			checkers_on_board_inter.get_checker(bot_choiseChecker).set_position(x * 50 + 7, y * 50 + 107);
			checkers_on_board_inter.get_board().get_all_squares((x * 50 - 50) / 50, (y * 50 + 50) / 50).square_employment(checkers_on_board_inter.get_checker(bot_choiseChecker).get_color());
			who_can_move = !who_can_move;
			Sleep(500);
			computerSteps += 1;
			return;
		}
		if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_employment() == 0 && end_board(x + 1, y - 1) && computerColor == 0)
		{
			ofstream out("ligth.txt");
			out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
			out.close();
			checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();
			checkers_on_board_inter.get_checker(bot_choiseChecker).set_position(x * 50 + 107, y * 50 + 7);
			checkers_on_board_inter.get_board().get_all_squares((x * 50 + 50) / 50, (y * 50 - 50) / 50).square_employment(checkers_on_board_inter.get_checker(bot_choiseChecker).get_color());
			who_can_move = !who_can_move;
			Sleep(500);
			computerSteps += 1;
			return;
		}
		if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_employment() == 0 && end_board(x - 1, y - 1) && computerColor == 0)
		{
			ofstream out("ligth.txt");
			out << ++this->amountSteps << "|" << this->getColor() << "|" << this->getMode();
			out.close();
			checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();
			checkers_on_board_inter.get_checker(bot_choiseChecker).set_position(x * 50 + 7, y * 50 + 7);
			checkers_on_board_inter.get_board().get_all_squares((x * 50 - 50) / 50, (y * 50 - 50) / 50).square_employment(checkers_on_board_inter.get_checker(bot_choiseChecker).get_color());
			who_can_move = !who_can_move;
			Sleep(500);
			computerSteps += 1;
			return;
		}
	}

	//������� �������� ����� ����������� ��� ���������� �����
	void conditions_for_Chekers()
	{
		condition_first_dir = condition_first_dir && computerColor == 1;
		condition_sec_dir = condition_sec_dir && computerColor == 1;
		condition_third_dir = condition_third_dir && computerColor == 0;
		condition_four_dir = condition_four_dir && computerColor == 0;
	}

	//������� �������� ����� ����������� ��� ������������� �����
	void conditions_for_Inter()
	{
		condition_first_dir = checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_employment() == 1 &&
			checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != computerColor &&
			checkers_on_board_inter.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0 && end_board(x + 2, y + 2);
		condition_sec_dir = checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_employment() == 1 &&
			checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != computerColor &&
			checkers_on_board_inter.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0 && end_board(x - 2, y + 2);
		condition_third_dir = checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_employment() == 1 &&
			checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != computerColor &&
			checkers_on_board_inter.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0 && end_board(x + 2, y - 2);
		condition_four_dir = checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_employment() == 1 &&
			checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != computerColor &&
			checkers_on_board_inter.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0 && end_board(x - 2, y - 2);
	}

	//�������� �����, ������� ��������� ����� ������� ������������ ���������� �����, �� �� ����� ���� (���� �� ������� ����������� � msx=2 ����� ���� ���������� ����������
	int bot_checker_which_eat(vector<int> checkers)
	{
		map<int, size_t> checkers_who_can_eat;// ���� - ����� �����, �������� - ������� ����� ��� ����� ������ ������
		for(int number : checkers)
		{
			if(mode == "International")
			{
				x = checkers_on_board_inter.get_checker(number).get_x();
				y = checkers_on_board_inter.get_checker(number).get_y();
			}

			else
			{
				x = checkers_on_board.get_checker(number).get_x();
				y = checkers_on_board.get_checker(number).get_y();
			}
			
			if (checkers_on_board.get_checker(number).get_queen() == 1) {
				int count = 0; //���-�� �����, ������� ����� ������� ����� ����������
				int cond1index;
				int cond2index;
				int cond3index;
				int cond4index;
				condition_first_dir = 1;
				condition_sec_dir = 1;
				condition_third_dir = 1;
				condition_four_dir = 1;

				bool first_dir;
				bool sec_dir;
				bool third_dir;
				bool four_dir;
				while (condition_first_dir || condition_sec_dir || condition_third_dir || condition_four_dir) //���� ���� ����������� ������� ����� �����������
				{
					condition_first_dir = 1;
					condition_sec_dir = 1;
					condition_third_dir = 1;
					condition_four_dir = 1;
					for (int i = 1, j = 1; x + i < 7 && y + j < 7; i++, j++) {
						first_dir = checkers_on_board.get_board().get_all_squares(x + i, y + j).get_employment() == 1 &&
							checkers_on_board.get_board().get_all_squares(x + i, y + j).get_checker_color() != computerColor &&
							checkers_on_board.get_board().get_all_squares(x + i + 1, y + j + 1).get_employment() == 0 && end_board(x + i + 1, y + j + 1);

						if (first_dir) {
							condition_first_dir = false;
							cond1index = i;/////////////////////����������� �����
							break;
						}
					}

					for (int i = 1, j = 1; x - i > 0 && y + j < 7; i++, j++) {
						sec_dir = checkers_on_board.get_board().get_all_squares(x - i, y + j).get_employment() == 1 &&
							checkers_on_board.get_board().get_all_squares(x - i, y + j).get_checker_color() != computerColor &&
							checkers_on_board.get_board().get_all_squares(x - i - 1, y + j + 1).get_employment() == 0 && end_board(x - i - 1, y + j + 1);

						if (sec_dir) {
							condition_sec_dir = false;
							cond2index = i;
							break;
						}
					}

					for (int i = 1, j = 1; x + i < 7 && y - j > 0; i++, j++) {
						third_dir = checkers_on_board.get_board().get_all_squares(x + i, y - j).get_employment() == 1 &&
							checkers_on_board.get_board().get_all_squares(x + i, y - j).get_checker_color() != computerColor &&
							checkers_on_board.get_board().get_all_squares(x + i + 1, y - j - 1).get_employment() == 0 && end_board(x + i + 1, y - j - 1);

						if (third_dir) {
							condition_third_dir = false;
							cond3index = i;
							break;
						}
					}

					for (int i = 1, j = 1; x - i > 0 && y - j > 0; i++, j++) {
						four_dir = checkers_on_board.get_board().get_all_squares(x - i, y - j).get_employment() == 1 &&
							checkers_on_board.get_board().get_all_squares(x - i, y - j).get_checker_color() != computerColor &&
							checkers_on_board.get_board().get_all_squares(x - i - 1, y - j - 1).get_employment() == 0 && end_board(x - i - 1, y - j - 1);

						if (four_dir) {
							condition_four_dir = false;
							cond4index = i;
							break;
						}
					}

					if (mode == "Checkers")
						conditions_for_Chekers();

					if (mode == "International")
						conditions_for_Inter();

					if (!condition_first_dir)
					{
						if (count == 1)
							break;
						x = x + cond1index + 1;
						y = y + cond1index + 1;
						count += 1;
						continue;
					}

					if (!condition_sec_dir)
					{
						if (count == 1)
							break;
						x = x - cond2index - 1;
						y = y + cond2index + 1;
						count += 1;
						continue;
					}

					if (!condition_third_dir)
					{
						if (count == 1)
							break;
						x = x + cond3index + 1;
						y = y - cond3index - 1;
						count += 1;
						continue;
					}

					if (!condition_four_dir)
					{
						if (count == 1)
							break;
						x = x - cond4index - 1;
						y = y - cond4index - 1;
						count += 1;
						continue;
					}
					if (count == 1)
						break;
				}

				checkers_who_can_eat[number] = count;
			}
			else {
				int count = 0; //���-�� �����, ������� ����� ������� ����� ����������
				condition_first_dir = 1;
				condition_sec_dir = 1;
				condition_third_dir = 1;
				condition_four_dir = 1;
				while (condition_first_dir || condition_sec_dir || condition_third_dir || condition_four_dir) //���� ���� ����������� ������� ����� �����������
				{
					condition_first_dir = checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment() == 1 &&
					checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != computerColor &&
					checkers_on_board.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0 && end_board(x + 2, y + 2);
					condition_sec_dir = checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment() == 1 &&
					checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != computerColor &&
					checkers_on_board.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0 && end_board(x - 2, y + 2);
					condition_third_dir = checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment() == 1 &&
					checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != computerColor &&
					checkers_on_board.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0 && end_board(x + 2, y - 2);
					condition_four_dir = checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment() == 1 &&
					checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != computerColor &&
					checkers_on_board.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0 && end_board(x - 2, y - 2);

					if (mode == "Checkers")
						conditions_for_Chekers();

					if (mode == "International")
						conditions_for_Inter();

					if (condition_first_dir)
					{
						if (count == 2)
							break;
						x += 2;
						y += 2;
						count += 1;
						continue;
					}

					if (condition_sec_dir)
					{
						if (count == 2)
							break;
						x -= 2;
						y += 2;
						count += 1;
						continue;
					}

					if (condition_third_dir)
					{
						if (count == 2)
							break;
						x += 2;
						y -= 2;
						count += 1;
						continue;
					}

					if (condition_four_dir)
					{
						if (count == 2)
							break;
						x -= 2;
						y -= 2;
						count += 1;
						continue;
					}
				}

				checkers_who_can_eat[number] = count;
			}
		}

		//����� �����, ������� ����� ������
		int max_val_key = key_number_max_val(checkers_who_can_eat);
		int max_val = max_val_key > -1 ? checkers_who_can_eat[max_val_key] : 0;

		if(max_val > 0)
		{
			count_eat = max_val;
			return max_val_key;
		}

		return -1;
	}

	//���������� ����� �����, ������� ����� ������� ������������ ���-�� ����� ������
	int key_number_max_val(map<int, size_t> _checkers_can_eat)
	{
		int max_value = 0;
		int key_value = -1;
		for (const auto& item : _checkers_can_eat)
		{
			if (item.second > max_value)
			{
				max_value = item.second;
				key_value = item.first;
			}
		}
		return  key_value;
	}

	//������� ���������� ����������� �����
	void bot_del_eaten_checker()
	{
		if (mode == "International")
			return bot_del_eaten_checker_inter();

		for (int i = 0; i < checkers_on_board.get_size(); i++) {
			bool condition = ((checkers_on_board.get_checker(i).get_x() - 1 == x && checkers_on_board.get_checker(i).get_y() - 1 == y && direction == 1) ||
				(checkers_on_board.get_checker(i).get_x() + 1 == x && checkers_on_board.get_checker(i).get_y() - 1 == y && direction == 2 ) ||
				(checkers_on_board.get_checker(i).get_x() - 1 == x && checkers_on_board.get_checker(i).get_y() + 1 == y && direction == 3 ) ||
				(checkers_on_board.get_checker(i).get_x() + 1 == x && checkers_on_board.get_checker(i).get_y() + 1 == y && direction == 4 ) &&
				checkers_on_board.get_checker(i).get_color() != computerColor);
			if (condition)
			{
				int eaten_X = checkers_on_board.get_checker(i).get_x();
				int eaten_Y = checkers_on_board.get_checker(i).get_y();

				switch (direction)
				{
				case 1:
					{
					if (!end_board(eaten_X + 1, eaten_Y + 1) || checkers_on_board.get_board().get_all_squares(eaten_X + 1, eaten_Y + 1).get_employment() == 1)
						continue;
					break;
					}
				case 2:
					{
					if (!end_board(eaten_X - 1, eaten_Y + 1) || checkers_on_board.get_board().get_all_squares(eaten_X - 1, eaten_Y + 1).get_employment() == 1)
						continue;
					break;
					}
				case 3:
					{
					if (!end_board(eaten_X + 1, eaten_Y - 1) || checkers_on_board.get_board().get_all_squares(eaten_X + 1, eaten_Y - 1).get_employment() == 1)
						continue;
					break;
					}
				case 4:
					{
					if (!end_board(eaten_X - 1, eaten_Y - 1) || checkers_on_board.get_board().get_all_squares(eaten_X - 1, eaten_Y - 1).get_employment() == 1)
						continue;
					break;
					}
				}

				checkers_on_board.get_board().get_all_squares(eaten_X, eaten_Y).square_free();
				for (int j = i; j < checkers_on_board.get_size() - 1; j++)
				{
					checkers_on_board.get_checker(j) = checkers_on_board.get_checker(j + 1);
				}
				
				if (i < bot_number_eat_checker)
				{
					bot_number_eat_checker = bot_number_eat_checker - 1;
				}

				checkers_on_board.delete_checker();
				return;
			}
		}
	}


	void bot_del_eaten_checker_inter()
	{
		for (int i = 0; i < checkers_on_board_inter.get_size(); i++) {
			bool condition = ((checkers_on_board_inter.get_checker(i).get_x() - 1 == x && checkers_on_board_inter.get_checker(i).get_y() - 1 == y && direction == 1) ||
				(checkers_on_board_inter.get_checker(i).get_x() + 1 == x && checkers_on_board_inter.get_checker(i).get_y() - 1 == y && direction == 2) ||
				(checkers_on_board_inter.get_checker(i).get_x() - 1 == x && checkers_on_board_inter.get_checker(i).get_y() + 1 == y && direction == 3) ||
				(checkers_on_board_inter.get_checker(i).get_x() + 1 == x && checkers_on_board_inter.get_checker(i).get_y() + 1 == y && direction == 4) &&
				checkers_on_board_inter.get_checker(i).get_color() != computerColor);
			if (condition)
			{
				int eaten_X = checkers_on_board_inter.get_checker(i).get_x();
				int eaten_Y = checkers_on_board_inter.get_checker(i).get_y();

				switch (direction)
				{
				case 1:
				{
					if (!end_board(eaten_X + 1, eaten_Y + 1) || checkers_on_board_inter.get_board().get_all_squares(eaten_X + 1, eaten_Y + 1).get_employment() == 1)
						continue;
					break;
				}
				case 2:
				{
					if (!end_board(eaten_X - 1, eaten_Y + 1) || checkers_on_board_inter.get_board().get_all_squares(eaten_X - 1, eaten_Y + 1).get_employment() == 1)
						continue;
					break;
				}
				case 3:
				{
					if (!end_board(eaten_X + 1, eaten_Y - 1) || checkers_on_board_inter.get_board().get_all_squares(eaten_X + 1, eaten_Y - 1).get_employment() == 1)
						continue;
					break;
				}
				case 4:
				{
					if (!end_board(eaten_X - 1, eaten_Y - 1) || checkers_on_board_inter.get_board().get_all_squares(eaten_X - 1, eaten_Y - 1).get_employment() == 1)
						continue;
					break;
				}
				}

				checkers_on_board_inter.get_board().get_all_squares(eaten_X, eaten_Y).square_free();
				for (int j = i; j < checkers_on_board_inter.get_size() - 1; j++)
				{
					checkers_on_board_inter.get_checker(j) = checkers_on_board_inter.get_checker(j + 1);
				}

				if (i < bot_number_eat_checker)
				{
					bot_number_eat_checker = bot_number_eat_checker - 1;
				}

				checkers_on_board_inter.delete_checker();
				return;
			}
		}
	}

	//������� ��� ����������������� �������� ����� �����������
	void bot_eat_checker()
	{
		if (mode == "International")
			return bot_eat_checker_inter();

		while (count_eat != 0) {

			if (bot_number_eat_checker != -1) {
				x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
				y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
			}
			else {
				break;
			}

			bool cont = false;

			if (checkers_on_board.get_checker(bot_number_eat_checker).get_queen() == 1) {
				for (int i = 1, j = 1; x + i < 7 && y + j < 7; i++, j++) {//////////////////////////
					if (checkers_on_board.get_board().get_all_squares(x + i, y + j).get_employment() == 1 &&
						checkers_on_board.get_board().get_all_squares(x + i, y + j).get_checker_color() != computerColor &&
						checkers_on_board.get_board().get_all_squares(x + i + 1, y + j + 1).get_employment() == 0 && end_board(x + i + 1, y + j + 1))
					{
						direction = 1;

						checkers_on_board.get_checker(bot_number_eat_checker).set_position((x + i - 1) * 50 + 57, (y + j - 1) * 50 + 57);
						x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
						y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();

						bot_del_eaten_checker();
						count_eat -= 1;
						checkers_on_board.get_board().get_all_squares(x, y).square_free();
						checkers_on_board.get_checker(bot_number_eat_checker).set_position(x * 50 + 157, y * 50 + 157);
						checkers_on_board.get_board().get_all_squares((x * 50 + 100) / 50, (y * 50 + 100) / 50).square_employment(checkers_on_board.get_checker(bot_number_eat_checker).get_color());
						x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
						y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
						make_queen();
						Sleep(500);
						cont = true;
						break;
					}
				}

				if (cont) {
					cont = false;
					continue;
				}

				for (int i = 1, j = 1; x - i > 0 && y + j < 7; i++, j++) {
					if (checkers_on_board.get_board().get_all_squares(x - i, y + j).get_employment() == 1 &&
						checkers_on_board.get_board().get_all_squares(x - i, y + j).get_checker_color() != computerColor &&
						checkers_on_board.get_board().get_all_squares(x - i - 1, y + j + 1).get_employment() == 0 && end_board(x - i - 1, y + j + 1))
					{
						direction = 2;

						checkers_on_board.get_checker(bot_number_eat_checker).set_position((x - i + 1) * 50 + 57, (y + j - 1) * 50 + 57);
						x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
						y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();

						bot_del_eaten_checker();
						count_eat -= 1;
						checkers_on_board.get_board().get_all_squares(x, y).square_free();
						checkers_on_board.get_checker(bot_number_eat_checker).set_position(x * 50 - 43, y * 50 + 157);
						checkers_on_board.get_board().get_all_squares((x * 50 - 100) / 50, (y * 50 + 100) / 50).square_employment(checkers_on_board.get_checker(bot_number_eat_checker).get_color());
						x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
						y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
						make_queen();
						Sleep(500);
						cont = true;
						break;
					}
				}

				if (cont) {
					cont = false;
					continue;
				}

				for (int i = 1, j = 1; x + i < 7 && y - j > 0; i++, j++) {
					if (checkers_on_board.get_board().get_all_squares(x + i, y - j).get_employment() == 1 &&
						checkers_on_board.get_board().get_all_squares(x + i, y - j).get_checker_color() != computerColor &&
						checkers_on_board.get_board().get_all_squares(x + i + 1, y - j - 1).get_employment() == 0 && end_board(x + i + 1, y - j - 1))
					{
						direction = 3;


						checkers_on_board.get_checker(bot_number_eat_checker).set_position((x + i - 1) * 50 + 57, (y - j + 1) * 50 + 57);
						x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
						y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();

						bot_del_eaten_checker();
						count_eat -= 1;
						checkers_on_board.get_board().get_all_squares(x, y).square_free();
						checkers_on_board.get_checker(bot_number_eat_checker).set_position(x * 50 + 157, y * 50 - 43);
						checkers_on_board.get_board().get_all_squares((x * 50 + 100) / 50, (y * 50 - 100) / 50).square_employment(checkers_on_board.get_checker(bot_number_eat_checker).get_color());
						x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
						y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
						make_queen();
						Sleep(500);
						cont = true;
						break;
					}
				}

				if (cont) {
					cont = false;
					continue;
				}

				for (int i = 1, j = 1; x - i > 0 && y - j > 0; i++, j++) {
					if (checkers_on_board.get_board().get_all_squares(x - i, y - j).get_employment() == 1 &&
						checkers_on_board.get_board().get_all_squares(x - i, y - j).get_checker_color() != computerColor &&
						checkers_on_board.get_board().get_all_squares(x - i - 1, y - j - 1).get_employment() == 0 && end_board(x - i - 1, y - j - 1))
					{
						direction = 4;

						checkers_on_board.get_checker(bot_number_eat_checker).set_position((x - i + 1) * 50 + 57, (y - j + 1) * 50 + 57);
						x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
						y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();

						bot_del_eaten_checker();
						count_eat -= 1;
						checkers_on_board.get_board().get_all_squares(x, y).square_free();
						checkers_on_board.get_checker(bot_number_eat_checker).set_position(x * 50 - 43, y * 50 - 43);
						checkers_on_board.get_board().get_all_squares((x * 50 - 100) / 50, (y * 50 - 100) / 50).square_employment(checkers_on_board.get_checker(bot_number_eat_checker).get_color());
						x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
						y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
						make_queen();
						Sleep(500);
						cont = true;
						break;
					}
				}

				if (cont) {
					cont = false;
					continue;
				}

			}
			else {
				if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment() == 1 &&
					checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != computerColor &&
					checkers_on_board.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0 && end_board(x + 2, y + 2))
				{
					direction = 1;
					bot_del_eaten_checker();
					count_eat -= 1;
					checkers_on_board.get_board().get_all_squares(x, y).square_free();
					checkers_on_board.get_checker(bot_number_eat_checker).set_position(x * 50 + 157, y * 50 + 157);
					checkers_on_board.get_board().get_all_squares((x * 50 + 100) / 50, (y * 50 + 100) / 50).square_employment(checkers_on_board.get_checker(bot_number_eat_checker).get_color());
					x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
					y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
					make_queen();
					Sleep(500);
					continue;
				}

				if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment() == 1 &&
					checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != computerColor &&
					checkers_on_board.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0 && end_board(x - 2, y + 2))
				{
					direction = 2;
					bot_del_eaten_checker();
					count_eat -= 1;
					checkers_on_board.get_board().get_all_squares(x, y).square_free();
					checkers_on_board.get_checker(bot_number_eat_checker).set_position(x * 50 - 43, y * 50 + 157);
					checkers_on_board.get_board().get_all_squares((x * 50 - 100) / 50, (y * 50 + 100) / 50).square_employment(checkers_on_board.get_checker(bot_number_eat_checker).get_color());
					x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
					y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
					make_queen();
					Sleep(500);
					continue;
				}

				if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment() == 1 &&
					checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != computerColor &&
					checkers_on_board.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0 && end_board(x + 2, y - 2))
				{
					direction = 3;
					bot_del_eaten_checker();
					count_eat -= 1;
					checkers_on_board.get_board().get_all_squares(x, y).square_free();
					checkers_on_board.get_checker(bot_number_eat_checker).set_position(x * 50 + 157, y * 50 - 43);
					checkers_on_board.get_board().get_all_squares((x * 50 + 100) / 50, (y * 50 - 100) / 50).square_employment(checkers_on_board.get_checker(bot_number_eat_checker).get_color());
					x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
					y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
					make_queen();
					Sleep(500);
					continue;
				}

				if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment() == 1 &&
					checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != computerColor &&
					checkers_on_board.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0 && end_board(x - 2, y - 2))
				{
					direction = 4;
					bot_del_eaten_checker();
					count_eat -= 1;
					checkers_on_board.get_board().get_all_squares(x, y).square_free();
					checkers_on_board.get_checker(bot_number_eat_checker).set_position(x * 50 - 43, y * 50 - 43);
					checkers_on_board.get_board().get_all_squares((x * 50 - 100) / 50, (y * 50 - 100) / 50).square_employment(checkers_on_board.get_checker(bot_number_eat_checker).get_color());
					x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
					y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
					make_queen();
					Sleep(500);
					continue;
				}
			}
		}

		x = checkers_on_board.get_checker(bot_number_eat_checker).get_x();
		y = checkers_on_board.get_checker(bot_number_eat_checker).get_y();
		make_queen();

		who_can_move = !who_can_move;
	}

	//������� ��� ����������������� �������� ����� ����������� � ������������� ������
	void bot_eat_checker_inter()
	{
		while (count_eat != 0) //���� ������������, ���� ���� ����������� ������� ����� ������ 
		{
			x = checkers_on_board_inter.get_checker(bot_number_eat_checker).get_x();
			y = checkers_on_board_inter.get_checker(bot_number_eat_checker).get_y();
			if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_employment() == 1 &&
				checkers_on_board_inter.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != computerColor &&
				checkers_on_board_inter.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0 && end_board(x + 2, y + 2))
			{
				direction = 1;
				bot_del_eaten_checker();
				count_eat -= 1;
				checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();
				checkers_on_board_inter.get_checker(bot_number_eat_checker).set_position(x * 50 + 157, y * 50 + 157);
				checkers_on_board_inter.get_board().get_all_squares((x * 50 + 100) / 50, (y * 50 + 100) / 50).square_employment(checkers_on_board_inter.get_checker(bot_number_eat_checker).get_color());
				Sleep(500);
				continue;
			}

			if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_employment() == 1 &&
				checkers_on_board_inter.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != computerColor &&
				checkers_on_board_inter.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0 && end_board(x - 2, y + 2))
			{
				direction = 2;
				bot_del_eaten_checker();
				count_eat -= 1;
				checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();

				checkers_on_board_inter.get_checker(bot_number_eat_checker).set_position(x * 50 - 43, y * 50 + 157);
				checkers_on_board_inter.get_board().get_all_squares((x * 50 - 100) / 50, (y * 50 + 100) / 50).square_employment(checkers_on_board_inter.get_checker(bot_number_eat_checker).get_color());
				Sleep(500);
				continue;
			}

			if (checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_employment() == 1 &&
				checkers_on_board_inter.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != computerColor &&
				checkers_on_board_inter.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0 && end_board(x + 2, y - 2))
			{
				direction = 3;
				bot_del_eaten_checker();
				count_eat -= 1;
				checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();

				checkers_on_board_inter.get_checker(bot_number_eat_checker).set_position(x * 50 + 157, y * 50 - 43);
				checkers_on_board_inter.get_board().get_all_squares((x * 50 + 100) / 50, (y * 50 - 100) / 50).square_employment(checkers_on_board_inter.get_checker(bot_number_eat_checker).get_color());
				Sleep(500);
				continue;
			}

			if (checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_employment() == 1 &&
				checkers_on_board_inter.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != computerColor &&
				checkers_on_board_inter.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0 && end_board(x - 2, y - 2))
			{
				direction = 4;
				bot_del_eaten_checker();
				count_eat -= 1;
				checkers_on_board_inter.get_board().get_all_squares(x, y).square_free();

				checkers_on_board_inter.get_checker(bot_number_eat_checker).set_position(x * 50 - 43, y * 50 - 43);
				checkers_on_board_inter.get_board().get_all_squares((x * 50 - 100) / 50, (y * 50 - 100) / 50).square_employment(checkers_on_board_inter.get_checker(bot_number_eat_checker).get_color());
				Sleep(500);
				continue;
			}
		}
		who_can_move = !who_can_move;
	}

	void make_move(RenderWindow& _window, Event _event)
	{
		choise_of_chacker(_window, _event);
		change_position(_window, _event);
	}

	void square_for_move() {//�������� ����
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
		if (mode == "Russian" || mode == "Giveaway")
			return chance_eat_checker_Russian(_color);

		if (mode == "Checkers")
			return chance_eat_checker_Checkers(_color);

		return chance_eat_checker_Inter(_color);
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

	//�������� �����
	bool eat_checker()
	{
		if (mode == "International")
			return eat_checker_inter();

		if ((centre_on_square().x - 57) / 50 - x == 2 || (centre_on_square().x - 57) / 50 - x == -2 &&
			(centre_on_square().y - 57) / 50 - y == 2 || (centre_on_square().y - 57) / 50 - y == -2) {
			for (int i = 0; i < checkers_on_board.get_size(); i++) {
				if (checkers_on_board.get_checker(i).get_x() == x + (checkers_on_board.get_checker(choiseChecker).get_x() - x) / 2 &&
					checkers_on_board.get_checker(i).get_y() == y + (checkers_on_board.get_checker(choiseChecker).get_y() - y) / 2) 
				{
					checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(i).get_x(), checkers_on_board.get_checker(i).get_y()).square_free();
					for (int j = i; j < checkers_on_board.get_size() - 1; j++) 
					{
						checkers_on_board.get_checker(j) = checkers_on_board.get_checker(j + 1);
					}

					checkers_on_board.delete_checker();
					if (i < choiseChecker) 
					{
						choiseChecker = choiseChecker - 1;
					}
					return 1;
				}
			}
		}
		return 0;
	}

	//�������� ����� � ������������� ������
	bool eat_checker_inter()
	{
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

	//��������, ����� �� ����� ����� ������
	void make_queen()
	{
		if (mode == "International")
			make_queen_inter();
		else
		{
			if (regime == "Computer" && (bot_number_eat_checker != -1 || queenRequest == 1)) {
				
				
				if (bot_number_eat_checker != -1) {
					if (checkers_on_board.get_checker(bot_number_eat_checker).get_color() == 0) {
						if (checkers_on_board.get_checker(bot_number_eat_checker).get_y() == 0) {
							checkers_on_board.get_checker(bot_number_eat_checker).make_queen();
						}
					}
					if (checkers_on_board.get_checker(bot_number_eat_checker).get_color() == 1) {
						if (checkers_on_board.get_checker(bot_number_eat_checker).get_y() == 7) {
							checkers_on_board.get_checker(bot_number_eat_checker).make_queen();
						}
					}
				}
				else
				{
					if (checkers_on_board.get_checker(bot_choiseChecker).get_color() == 0) {
						if (checkers_on_board.get_checker(bot_choiseChecker).get_y() == 0) {
							checkers_on_board.get_checker(bot_choiseChecker).make_queen();
						}
					}
					if (checkers_on_board.get_checker(bot_choiseChecker).get_color() == 1) {
						if (checkers_on_board.get_checker(bot_choiseChecker).get_y() == 7) {
							checkers_on_board.get_checker(bot_choiseChecker).make_queen();
						}
					}
				}
			}
			else {
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
	}

	//��������, ����� �� ����� ����� ������ � ������������� ������
	void make_queen_inter()
	{
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

	//�������� ���� �����
	bool queen_square_for_move(bool _color, int _i1, int _i2, int _i3, int _i4) {
		if (mode == "Russian" || mode == "Giveaway")
			return queen_square_for_move_Russian(_color, _i1, _i2, _i3, _i4);

		if (mode == "Checkers")
			return queen_square_for_move_Checkers(_color, _i1, _i2, _i3, _i4);
		return queen_square_for_move_Inter(_color, _i1, _i2, _i3, _i4);
	}

	//�������� ���� ����� � ������������� ������
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

	//�������� ���� ����� � ���������� ������
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

	//�������� ���� ����� � ������� ������
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

	//�������� ����� ������
	bool queen_eat_checker()
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

	//�������� ����� ������ � ������������ ������
	bool queen_eat_checker_inter() 
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

	//�������� ������ �� ������� ����
	bool end_board(float _x, float _y)
	{
		int maxSize = mode == "International" ? 10 : 8;
		if (_x >= 0 && _x < maxSize && _y >= 0 && _y < maxSize)
			return 1;

		return 0;
	}

	//�������� ������� �������, ��� ������� ����������� �������
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
		if (who_must_eat.size() != 0) 
			return 1;
		else 
			return 0;
	}

	//�������� ������� �������, ��� ������� ����������� ������� � ������������� ������
	bool if_you_can_eat_you_must_eat_inter(bool _color)
	{
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

	//���� ��������������, ��� ���� ����������� �������
	void error_choise_checker(RenderWindow& _window, Event _event)
	{
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

	//��������� ������ ������ ����
	void start_game(RenderWindow& _window, Event _event, bool& _start) {
		while (1) {
			_start = 0;
			return;
		}
	}

	//��������� ������ ����� ����
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
			for (int i = 0; i < checkers_on_board_inter.get_size(); i++) {
				if (checkers_on_board_inter.get_checker(i).get_color() == 0) {
					white++;
				}
				if (checkers_on_board_inter.get_checker(i).get_color() == 1) {
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
		if (comp_checker_can_move.size() == 0 && computerColor == 0 && computerSteps > 0)
			white = 0;
		if (comp_checker_can_move.size() == 0 && computerColor == 1 && computerSteps > 0)
			black = 0;

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
				return 1;
				
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
				return 1;
				
			}

			return 0;
		}
		return 1;
	}
};
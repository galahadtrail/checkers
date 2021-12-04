#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Checker.h"
#include "game.h"
#include "Board_International.h"
using namespace sf;

class Checkers_on_board_Inter {
private:
	vector <Checker> checkers;//светлые шашки
	Board_International board;
public:
	Board_International& get_board() { return this->board; }

	Checker& get_checker(int _i) {
		return this->checkers[_i];
	}

	int get_size() {
		return this->checkers.size();
	}

	void start_game()//Создание шашек соотвветствующих цветов
	{
		for (int i = 0; i < 40; i++) 
		{
			if (i < 5) {
				checkers.push_back(Checker((float)i * 100 + 107, (float)57, 1));
				board.get_all_squares(i * 2 + 1, 0).square_employment(1);
			}
			if (i >= 5 && i < 10) {
				checkers.push_back(Checker((float)(i - 5) * 100 + 57, (float)107, 1));
				board.get_all_squares((i - 5) * 2, 1).square_employment(1);
			}

			if (i >= 10 && i < 15) {
				checkers.push_back(Checker((float)(i - 10) * 100 + 107, (float)157, 1));
				board.get_all_squares((i - 10) * 2 + 1, 2).square_employment(1);
			}

			if (i >= 15 && i < 20) {
				checkers.push_back(Checker((float)(i - 15) * 100 + 57, (float)207, 1));
				board.get_all_squares((i - 15) * 2, 3).square_employment(1);
			}

			if (i >= 20 && i < 25) {
				checkers.push_back(Checker((float)(i - 20) * 100 + 107, (float)357, 0));
				board.get_all_squares((i - 20) * 2 + 1, 6).square_employment(0);
			}

			if (i >= 25 && i < 30) {
				checkers.push_back(Checker((float)(i - 25) * 100 + 57, (float)407, 0));
				board.get_all_squares((i - 25) * 2, 7).square_employment(0);
			}

			if (i >= 30 && i < 35) {
				checkers.push_back(Checker((float)(i - 30) * 100 + 107, (float)457, 0));
				board.get_all_squares((i - 30) * 2 + 1, 8).square_employment(0);
			}

			if (i >= 35 && i < 40) {
				checkers.push_back(Checker((float)(i - 35) * 100 + 57, (float)507, 0));
				board.get_all_squares((i - 35) * 2, 9).square_employment(0);
			}
		}
	}

	void delete_checker() { checkers.pop_back(); }

	Checkers_on_board_Inter() { start_game(); };//Расстановка шашек на поле

	void draw_checkers(RenderWindow& _window, int time, bool master)//функция рисования поля с фигурами
	{
		board.draw_board(_window, time, master);//рисую доску
		for (int i = 0; i < checkers.size(); i++)//цикл для рисования каждой шашки
			checkers[i].draw_checker(_window);
	}

	void delete_backlight()//Удаление подсвеченных клеток (клеток возможного хода)
	{
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				this->board.get_all_squares(i, j).off_backlight();
		}
	}
};
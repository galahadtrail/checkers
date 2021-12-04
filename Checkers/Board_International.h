#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include <iostream>
using namespace sf;
using namespace std;

class Board_International {
private:
	Square all_squares[10][10];
public:
	Board_International() {}
	Square& get_all_squares(int _i, int _j) { return this->all_squares[_i][_j]; }

	void draw_board(RenderWindow& _window) {
		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++) {
				all_squares[i - 1][j - 1].set_position(i * 50.0, j * 50);
				if ((i + j) % 2 == 1) all_squares[i - 1][j - 1].set_color(Color(85, 52, 14));
				else all_squares[i - 1][j - 1].set_color(Color(255, 210, 117));
				_window.draw(all_squares[i - 1][j - 1].get_square());
			}
		}
		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++) {
				if (all_squares[i - 1][j - 1].get_backlight() == 1) {
					RectangleShape square_light(Vector2f(50, 50));
					square_light.setPosition(i * 50, j * 50);
					all_squares[i - 1][j - 1].set_color(Color(150, 120, 90));
				}
				_window.draw(all_squares[i - 1][j - 1].get_square());
			}
		}
		Font font;
		font.loadFromFile("Font//bahnschrift.ttf");
		Text* t[20];
		for (int i = 0; i < 20; i++) {
			t[i] = new Text("", font, 35);

		}
		t[0]->setString(L"1");
		t[1]->setString(L"2");
		t[2]->setString(L"3");
		t[3]->setString(L"4");
		t[4]->setString(L"5");
		t[5]->setString(L"6");
		t[6]->setString(L"7");
		t[7]->setString(L"8");
		t[8]->setString(L"9");
		t[9]->setString(L"10");
		t[10]->setString(L"À");
		t[11]->setString(L"B");
		t[12]->setString(L"C");
		t[13]->setString(L"D");
		t[14]->setString(L"E");
		t[15]->setString(L"F");
		t[16]->setString(L"G");
		t[17]->setString(L"H");
		t[18]->setString(L"J");
		t[19]->setString(L"K");
		for (int i = 0; i < 10; i++) {
			t[i]->setFillColor(Color::Black);
			t[i]->setPosition(15, i * 50 + 55);
			_window.draw(*t[i]);
			t[i]->setPosition(565, i * 50 + 55);
			_window.draw(*t[i]);
		}
		for (int i = 10; i < 20; i++) {
			t[i]->setFillColor(Color::Black);
			t[i]->setPosition((i - 10) * 50 + 60, 5);
			_window.draw(*t[i]);
			t[i]->setPosition((i - 10) * 50 + 60, 555);
			_window.draw(*t[i]);
		}
	}
};
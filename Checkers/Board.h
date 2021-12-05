#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include <ctime>
#include <time.h>
#include <fstream>
#include <iostream>
using namespace sf;
using namespace std;

class Board {
private:
	Square all_squares[8][8];
public:
	Board(){}
	Square &get_all_squares(int _i, int _j) {
		return this->all_squares[_i][_j];
	}

	void draw_board(RenderWindow &_window, int timex, bool master) {
		locale::global(locale(""));
		int theme;

		wifstream input("user.txt");
		wstring bulk;
		getline(input, bulk);

		input.close();

		int index = bulk.rfind(':') + 1;
		if (bulk[index] == 'D') {
			theme = 0;
		}
		else {
			theme = 1;
		}

		Texture fon;

		if (theme == 0) {
			fon.loadFromFile("images/fon6.jpg");
		}
		else {
			fon.loadFromFile("images/fon7.jpg");
		}
		Sprite fons(fon);
		_window.draw(fons);

		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				all_squares[i - 1][j - 1].set_position(i * 50.0, j * 50);
				if ((i + j) % 2 == 1) {
					if (theme == 0) {
						all_squares[i - 1][j - 1].set_color(Color(101, 61, 16));
					}
					else {
						all_squares[i - 1][j - 1].set_color(Color(80, 80, 80));
					}
				}  
				else { 
					if (theme == 0) {
						all_squares[i - 1][j - 1].set_color(Color(255, 178, 115));   //белые клетки
					}
					else {
						all_squares[i - 1][j - 1].set_color(Color(255, 255, 255));
					}
				} //белые клетки
				_window.draw(all_squares[i - 1][j - 1].get_square());
			}
		}
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (all_squares[i - 1][j - 1].get_backlight() == 1) {
					RectangleShape square_light(Vector2f(50, 50));
					square_light.setPosition(i * 50, j * 50);
					if (theme == 0) {
						all_squares[i - 1][j - 1].set_color(Color(150, 120, 90));
					}
					else {
						all_squares[i - 1][j - 1].set_color(Color(180, 180, 180));
					}
				}
				_window.draw(all_squares[i - 1][j - 1].get_square());
			}
		}
		Font font1;
		font1.loadFromFile("Font//Deutsch Gothic.ttf");
		Font font2;
		font2.loadFromFile("Font//bahnschrift.ttf");
		Text *t[16];
		for (int i = 0; i < 16; i++) {
			t[i] = new Text("", font2, 35);

		}
		t[0]->setString(L"1");
		t[1]->setString(L"2");
		t[2]->setString(L"3");
		t[3]->setString(L"4");
		t[4]->setString(L"5");
		t[5]->setString(L"6");
		t[6]->setString(L"7");
		t[7]->setString(L"8");
		t[8]->setString(L"А");
		t[9]->setString(L"B");
		t[10]->setString(L"C");
		t[11]->setString(L"D");
		t[12]->setString(L"E");
		t[13]->setString(L"F");
		t[14]->setString(L"G");
		t[15]->setString(L"H");
		for (int i = 0; i < 8; i++) {
			t[i]->setFillColor(Color::White);
			t[i]->setOutlineColor(sf::Color::Black);
			t[i]->setOutlineThickness(1);
			t[i]->setPosition(15, i * 50 + 55);
			_window.draw(*t[i]);
			t[i]->setPosition(465, i * 50 + 55);
			_window.draw(*t[i]);
		}
		for (int i = 8; i < 16; i++) {
			t[i]->setFillColor(Color::White);
			t[i]->setOutlineColor(sf::Color::Black);
			t[i]->setOutlineThickness(1);
			t[i]->setPosition((i - 8) * 50 + 60, 5);
			_window.draw(*t[i]);
			t[i]->setPosition((i - 8) * 50 + 60, 455);
			_window.draw(*t[i]);
		}

		
		Text time(L"Время:   ", font1, 23);
		time.setPosition(650, 20);
		time.setFillColor(sf::Color::Black);
		time.setOutlineColor(sf::Color::White);
		time.setOutlineThickness(1);

		int timeIntVal = (clock() - timex) / 1000;
		

		time.setString(L"Время:   " + to_string(timeIntVal));

		_window.draw(time);

		Text name(L"Имя:   ", font1, 23);
		name.setPosition(650, 70);
		name.setOutlineColor(sf::Color::White);
		name.setOutlineThickness(1);
		name.setFillColor(sf::Color::Black);
		
		Text nameGuest(L"Имя гостя:   \n", font1, 23);
		nameGuest.setPosition(650, 120);
		nameGuest.setOutlineColor(sf::Color::White);
		nameGuest.setOutlineThickness(1);
		nameGuest.setFillColor(sf::Color::Black);

		if (master) {
			name.setFillColor(Color::Yellow);
		}
		else {
			nameGuest.setFillColor(Color::Yellow);
		}

		wifstream nameInput("user.txt");
		wstring buffer;
		wstring semi;
		do {
			buffer += nameInput.get();
		} while (buffer[buffer.size() - 1] != '|');

		buffer.resize(buffer.size() - 1);
		bool stopFlag = false;
		for (int i = 0; i < buffer.size(); i = i++) {
			while (buffer[i] != ':' && !stopFlag) {
				i++;
			}

			if (!stopFlag) {
				stopFlag = true;
				i++;
			}
			
			semi += buffer[i];
			
		}
		nameInput.close();
		
		

		name.setString(L"Имя:   " + semi);
		nameGuest.setString(L"Имя гостя:   \n" + assignRegimeFromFile("regime.txt"));

		_window.draw(name);
		_window.draw(nameGuest);
	}
};
#include "menu.h"

int main() {
	setlocale(LC_ALL, "rus");

	Game game;
	bool start = 1;
	

	RenderWindow gameWindow(VideoMode(800, 500), "Checkers");
	menu(gameWindow);

	return 0;
}


#include "menu.h"

int main() {
	setlocale(LC_ALL, "rus");

	Game game;
	bool start = 1;
	bool emo = false;

	RenderWindow gameWindow(VideoMode(800, 500), "Checkers");
	emo = menu(gameWindow);

	while (emo) {
		gameWindow.close();
		RenderWindow gameWindow(VideoMode(800, 500), "Checkers");
		emo = menu(gameWindow);
	}



	/*do { 
		gameWindow.close();
		RenderWindow gameWindow(VideoMode(800, 500), "Checkers"); 
		emo = menu(gameWindow);
	} while (emo);*/

	return 0;
}


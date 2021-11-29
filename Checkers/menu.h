#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

void InstructionSettings(sf::RenderWindow& window);
void UserSettings(sf::RenderWindow& window);
void ExitFunc(sf::RenderWindow& window);
void menu(sf::RenderWindow& window);
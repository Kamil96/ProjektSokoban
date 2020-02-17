#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "SceneManager.h"
#include "Teksturowanie.h"

class Gra
{
public:
	Gra();
	void start();
private:

	sf::Font font;

	stan::StanyGry StanGry;
	sf::RenderWindow window;

	Teksturowanie texture;

	SceneManager sceneManager;

	void processEvents();
	void render();
};

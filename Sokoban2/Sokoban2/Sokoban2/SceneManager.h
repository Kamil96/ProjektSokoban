#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <map>
#include <experimental/filesystem>
#include <sstream>
#include "Enums.h"
#include "Teksturowanie.h"
#include "Tile.h"
#include "Player.h"
#include "Licznik.h"

class SceneManager : public sf::Drawable
{
public:
	SceneManager(Teksturowanie* texture, const sf::Font& font);

	void next();
	void update(const sf::Event& event);
private:
	Teksturowanie* texture;

	std::map<unsigned int, std::map<unsigned int, Tile>> tiles;

	Player player;

	Licznik pushesCounter;		//licznik pchniec
	Licznik movesCounter;		//licznik ruchow
	Licznik currentLevel;		//licznik poziomow

	void loadLevelFromFile(const std::string& filename);
	bool processEvents(const sf::Event& event);
	void detectCollisions();
	bool isEnd();
	void reset();
	void changeLevelToNext();
	void resetCurrentLevel();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

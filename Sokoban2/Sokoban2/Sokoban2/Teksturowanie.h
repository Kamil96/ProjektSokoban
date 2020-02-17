#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>


class Teksturowanie
{
public:
	Teksturowanie() {
		loadTextures();
	}
	bool add(const std::string& name, const std::string& filename);

	sf::Texture& get(const std::string& name);

private:
	std::map<std::string, sf::Texture> textures;
	std::vector<std::string> paths;

	void loadTextures();
};
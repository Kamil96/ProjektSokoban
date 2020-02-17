#include "Teksturowanie.h"

bool Teksturowanie::add(const std::string& name, const std::string & filename)
{
	sf::Texture tmpTexture;
	tmpTexture.loadFromFile(filename);

	for (const auto& texture : textures)
	{
		if (texture.first == name)
		{
			std::cout << "ERROR - Konflikt nazw dla tekstur o nazwie: " << name << std::endl;
			return false;
		}
	}

	textures[name] = tmpTexture;

	for (const auto& path : paths)
	{
		if (path == filename)
		{
			std::cout << "ERROR - Plik o nazwie: " << filename << " zawierajacy teksture, zostal juz wczesniej dododany" << std::endl;
			return false;
		}
	}
	paths.push_back(filename);

	return true;
}

sf::Texture & Teksturowanie::get(const std::string& name)
{
	if (textures.find(name) == textures.end())   //sprawdzenie czy dany element istnieje
	{
		std::cout << "ERROR - Plik tekstury o nazwie: " << name << " nie istnieje!" << std::endl;
	}
	else
		return textures[name];
}

void Teksturowanie::loadTextures()
{
	add("sciana", "data/textures/sciana.png");
	add("skrzynia", "data/textures/skrzynia.png");
	add("skrzynia_cel", "data/textures/skrzynia_cel.png");
	add("cel", "data/textures/cel.png");
	add("puste", "data/textures/puste.png");
	add("playerLeft", "data/textures/playerLeft.png");
	add("playerRight", "data/textures/playerRight.png");
	add("playerUp", "data/textures/playerUp.png");
	add("playerDown", "data/textures/playerDown.png");
}

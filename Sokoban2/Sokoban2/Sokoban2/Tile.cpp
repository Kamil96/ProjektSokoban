#include "Tile.h"

Teksturowanie* Tile::texture = nullptr;
const int Tile::Size = 64;		//staly rozmiar dla kazdego kwadratowego tile'a uzytego w programie

Tile::Tile(const po::Pola& type, const sf::Vector2i& positionInTiles)
{
	sprite.setPosition(positionInTiles.x * Size, positionInTiles.y * Size);
	setType(type);
}

void Tile::setType(const po::Pola & newType)
{
	type = newType;
	switch (newType)
	{
	case po::Pola::PUSTE:
		sprite.setTexture(texture->get("puste"));
		break;
	case po::Pola::SCIANA:
		sprite.setTexture(texture->get("sciana"));
		break;
	case po::Pola::SKRZYNIA:
		sprite.setTexture(texture->get("skrzynia"));
		break;
	case po::Pola::CEL:
		sprite.setTexture(texture->get("cel"));
		break;
	case po::Pola::SKRZYNIA_CEL:
		sprite.setTexture(texture->get("skrzynia_cel"));
	}
}
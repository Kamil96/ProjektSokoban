#pragma once

#include <SFML/Graphics.hpp>
#include "Teksturowanie.h"
#include "Enums.h"

class Tile : public sf::Drawable
{
public:
	static Teksturowanie* texture;
	static const int Size;

	Tile(const po::Pola& type, const sf::Vector2i& positionInTiles);
	Tile() {}

	sf::Vector2i getPositionInTiles() const 
	{
		return sf::Vector2i(sprite.getPosition().x / Size, sprite.getPosition().y / Size);
	}
	po::Pola getType() const 
	{
		return type;
	}
	void setType(const po::Pola& newType);

private:
	sf::Sprite sprite;
	po::Pola type;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		target.draw(sprite);		
	}
};
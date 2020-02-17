#pragma once

#include "Enums.h"
#include "Teksturowanie.h"
#include "Licznik.h"

class Player : public sf::Drawable
{
public:
	Player(Teksturowanie* texture, const int TileSize, Licznik* movesCounter);

	void move(const kier::Kierunki& newDirection);
	void undoMove();

	void setPositionInTiles(const sf::Vector2i& position) 
	{
		sprite.setPosition(position.x * TileSize, position.y * TileSize);		
	}
	sf::Vector2i getPositionInTiles() 
	{
		return sf::Vector2i(sprite.getPosition().x / TileSize, sprite.getPosition().y / TileSize);
	}
	kier::Kierunki getCurrentDirection() const
	{
		return currentDirection;
	}
private:
	const int TileSize;
	sf::Sprite sprite;
	Teksturowanie* texture;

	Licznik* movesCounter;

	kier::Kierunki currentDirection;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		target.draw(sprite);
	}
};
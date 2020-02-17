#include "Player.h"

Player::Player(Teksturowanie* texture, const int TileSize, Licznik* movesCounter) :
	texture(texture),
	TileSize(TileSize),
	movesCounter(movesCounter)
{
	sprite.setTexture(texture->get("playerDown"));		//player zwrocony twarza w dol na poczatku poziomu
	currentDirection = kier::Kierunki::DOL;
}

void Player::move(const kier::Kierunki & newDirection)
{
	(*movesCounter)++;
	currentDirection = newDirection;		
	std::string textureNameToSet;
	switch (newDirection)
	{
	case kier::Kierunki::LEWO:
		textureNameToSet = "playerLeft";	//poruszanie sie o 1 tile w lewo, obrocenie playera w lewo
		sprite.move(-TileSize, 0);
		break;
	case kier::Kierunki::PRAWO:
		textureNameToSet = "playerRight";	//poruszanie sie o 1 tile w prawo, obrocenie playera w prawo
		sprite.move(TileSize, 0);
		break;
	case kier::Kierunki::GORA:
		textureNameToSet = "playerUp";		//poruszanie sie o 1 tile w gore, obrocenie playera w gore
		sprite.move(0, -TileSize);
		break;
	case kier::Kierunki::DOL:
		textureNameToSet = "playerDown";	//poruszanie sie o 1 tile w dol, obrocenie playera w dol
		sprite.move(0, TileSize);
		break;
	}
	sprite.setTexture(texture->get(textureNameToSet));
}

void Player::undoMove()		//niwelowanie ruchu przy kolizji
{
	(*movesCounter)--;
	std::string textureNameToSet;
	switch (currentDirection)
	{
	case kier::Kierunki::LEWO:
		sprite.move(TileSize, 0);
		textureNameToSet = "playerLeft";
		break;
	case kier::Kierunki::PRAWO:
		sprite.move(-TileSize, 0);
		textureNameToSet = "playerRight";
		break;
	case kier::Kierunki::GORA:
		sprite.move(0, TileSize);
		textureNameToSet = "playerUp";
		break;
	case kier::Kierunki::DOL:
		sprite.move(0, -TileSize);
		textureNameToSet = "playerDown";
		break;
	}
	sprite.setTexture(texture->get(textureNameToSet));
}

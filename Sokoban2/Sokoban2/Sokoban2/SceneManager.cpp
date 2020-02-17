#include "SceneManager.h"
#include "PlayerStatus.h"
#include <iostream>
#include <string>


SceneManager::SceneManager(Teksturowanie* texture, const sf::Font& font) :

	texture(texture),								
	player(texture, Tile::Size, &movesCounter),
	pushesCounter("PCHNIECIA: ", sf::Vector2f(510, 530), font),
	movesCounter("RUCHY: ", sf::Vector2f(80, 530), font),
	currentLevel("POZIOM: ", sf::Vector2f(300, 530), font)

{

}

void SceneManager::next()
{
	changeLevelToNext();
}

void SceneManager::update(const sf::Event& event)
{
	if (processEvents(event))
	{
		detectCollisions();
		if (isEnd())
		{
			reset();
			changeLevelToNext();			//reset i przejscie do metody wywolujacej kolejny poziom w grze
		}
	}
}

void SceneManager::loadLevelFromFile(const std::string & filename)
{
	std::ifstream file(filename);

	std::string x, y;
	file >> x >> y;
	player.setPositionInTiles(sf::Vector2i(std::stoi(x), std::stoi(y)));	//stoi - funkcja wbudowana, ktora zamienia string w int

	sf::Vector2i loadCounter;
	while (!file.eof())
	{
		int tileType;		
		file >> tileType;	//wczytywanie obiektow na mape (0-puste pole, 1-sciana, 2-skrzynia, 3-cel)

		tiles[loadCounter.x][loadCounter.y] = Tile(static_cast<po::Pola>(tileType), loadCounter); //static_cast - konwersja danych zapisanych w zmiennych ró¿nych typów
		loadCounter.x++;
		if (file.peek() == '\n')			//file.peek() -  odczytuje nastêpny znak bez jego pobierania
		{
			loadCounter.x = 0;
			loadCounter.y++;
		}
	}
}

void SceneManager::changeLevelToNext()  //nastepny poziom w grze
{
	currentLevel++;
	std::string filePath = "data/levels/poziom" + currentLevel.toString() + ".lvl";
	if (!std::experimental::filesystem::exists(filePath))  //sprawdzenie czy  œcie¿ka odpowiada istniej¹cemu plikowi
	{
		currentLevel.reset();
		changeLevelToNext();
	}
	else
		loadLevelFromFile(filePath);
}

void SceneManager::resetCurrentLevel()	//resetowanie biezacego poziomu w grze
{
	std::string filePath = "data/levels/poziom" + currentLevel.toString() + ".lvl";
	if (!std::experimental::filesystem::exists(filePath))  
	{
		currentLevel.reset();
		changeLevelToNext();
	}
	else
		loadLevelFromFile(filePath);
}

bool SceneManager::processEvents(const sf::Event& event)	//reagowanie na input z klawiatury
{
	PlayerStatus* wgore = new RuchGora;
	PlayerStatus* wlewo = new RuchLewo;
	PlayerStatus* wprawo = new RuchPrawo;
	PlayerStatus* wdol = new RuchDol;
	PlayerStatus* resetuj = new ResetPoziomu;

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			player.move(kier::Kierunki::LEWO);
			wlewo->interakcja();
			return true;
		case sf::Keyboard::Right:
			player.move(kier::Kierunki::PRAWO);
			wprawo->interakcja();
			return true;
		case sf::Keyboard::Up:
			player.move(kier::Kierunki::GORA);
			wgore->interakcja();
			return true;
		case sf::Keyboard::Down:
			player.move(kier::Kierunki::DOL);
			wdol->interakcja();
			return true;
		case sf::Keyboard::Space:
			resetCurrentLevel();
			pushesCounter.reset();
			movesCounter.reset();
			resetuj->interakcja();
			return true;
		}
	}
	delete wlewo;
	delete wprawo;
	delete wgore;
	delete wdol;
	delete resetuj;
	return false;
}

void SceneManager::detectCollisions()
{
	Tile *tileUnderPlayer = &tiles[player.getPositionInTiles().x][player.getPositionInTiles().y];	//pobieranie pozycji tile'a na ktorym znajduje sie postac
	
	if (tileUnderPlayer->getType() == po::Pola::SCIANA)		//inicjowanie metody undoMove() jezeli gracz trafi na sciane
		player.undoMove();									

	Tile *nextTile = nullptr;					//wskaznik niewskazujacy chwilowo na zadne pole
	
	switch (player.getCurrentDirection())		//obsluga kolizji w przypadkach przemieszczania sie po pustych polach
	{											
	case kier::Kierunki::LEWO:
		nextTile = &tiles[tileUnderPlayer->getPositionInTiles().x - 1][tileUnderPlayer->getPositionInTiles().y];
		break;		//jezeli kolizja wystepuje z lewej strony to nastepuje przemieszczenie postaci o jedno pole w lewo
	case kier::Kierunki::PRAWO:
		nextTile = &tiles[tileUnderPlayer->getPositionInTiles().x + 1][tileUnderPlayer->getPositionInTiles().y];
		break;		
	case kier::Kierunki::GORA:
		nextTile = &tiles[tileUnderPlayer->getPositionInTiles().x][tileUnderPlayer->getPositionInTiles().y - 1];
		break;		
	case kier::Kierunki::DOL:
		nextTile = &tiles[tileUnderPlayer->getPositionInTiles().x][tileUnderPlayer->getPositionInTiles().y + 1];
		break;		
	}

	if (tileUnderPlayer->getType() == po::Pola::SKRZYNIA)		//wykrywanie kolizji ze skrzynia, gdy jest kolejnym polem na drodze postaci
	{
		if (nextTile->getType() == po::Pola::PUSTE)			//jezeli postac pcha skrzynie na puste pole
		{
			tileUnderPlayer->setType(po::Pola::PUSTE);		//jezeli pod postacia jest puste pole
			nextTile->setType(po::Pola::SKRZYNIA);			//przemieszczenie skrzyni w kierunku ruchu postaci 
			pushesCounter++;								//zwiekszenie ilosci wykonanych pchniec
		}
		else if (nextTile->getType() == po::Pola::CEL)		//jezeli skrzynia zostanie wepchnieta na pole CEL
		{
			tileUnderPlayer->setType(po::Pola::PUSTE);		//jezeli pod postacia jest puste pole
			nextTile->setType(po::Pola::SKRZYNIA_CEL);		//zmiana typu pola na SKRZYNIA_CEL
			pushesCounter++;								//zwiekszenie ilosci wykonanych pchniec
		}
		else
			player.undoMove();
	}
	else if (tileUnderPlayer->getType() == po::Pola::SKRZYNIA_CEL)		//jezeli pod postacia znajduje sie pole SKRZYNIA_CEL
	{
		if (nextTile->getType() == po::Pola::PUSTE)			//jezeli postac pcha skrzynie na puste pole
		{
			tileUnderPlayer->setType(po::Pola::CEL);		//zmiana typu pola na CEL
			nextTile->setType(po::Pola::SKRZYNIA);			//zmiana kolejnego pola na SKRZYNIA
			pushesCounter++;								//zwiekszenie ilosci wykonanych pchniec
		}
		else if (nextTile->getType() == po::Pola::CEL)		//jezeli skrzynia zostanie wepchnieta na pole CEL
		{
			tileUnderPlayer->setType(po::Pola::CEL);		
			nextTile->setType(po::Pola::SKRZYNIA_CEL);		
			pushesCounter++;										
		}
		else
			player.undoMove();
	}
}

bool SceneManager::isEnd()		//sprawdzenie czy poziom zostal zaliczony
{
	for (auto const& column : tiles)
	{
		for (auto const& tile : column.second)
		{
			if (tile.second.getType() == po::Pola::CEL)
				return false;
		}
	}
	return true;
}

void SceneManager::reset()
{
	tiles.clear();
	movesCounter.reset();
	pushesCounter.reset();
}

void SceneManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto const& column : tiles)					
	{
		for (auto const& tile : column.second)
		{
			target.draw(tile.second);					//wywo³anie metody draw
		}
	} 
	target.draw(player);
	target.draw(movesCounter);
	target.draw(pushesCounter);
	target.draw(currentLevel);
}

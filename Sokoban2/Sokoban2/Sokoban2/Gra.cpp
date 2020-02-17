#include "Gra.h" 

Gra::Gra() : window(sf::VideoMode(770, 600), "Sokoban - KamilGlembin", sf::Style::Close | sf::Style::Titlebar),  
StanGry(stan::StanyGry::PLAY),
sceneManager(&texture, font)
{
	window.setFramerateLimit(60);

	font.loadFromFile("data/font.ttf");
	Tile::texture = &texture;

	sceneManager.next();
}

void Gra::start()
{
	while (StanGry != stan::StanyGry::EXIT)  //jezeli stanem gry nie jest EXIT to wykonywane jest processEvents i renderowanie grafiki
	{
		processEvents();
		render();
	}
	window.close();
}

void Gra::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))	//nacisniecie ESC konczy gre
		{
			StanGry = stan::StanyGry::EXIT;
			window.close();
		}
		else if (StanGry == stan::StanyGry::PLAY)		
			sceneManager.update(event);					//wykonanie update'u gry w scene managerze
	}
}

void Gra::render()			//renderowanie
{

	window.clear();
	window.draw(sceneManager);
	window.display();
}
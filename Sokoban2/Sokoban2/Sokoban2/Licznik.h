#pragma once

#include <SFML/Graphics.hpp>

class Licznik : public sf::Drawable 
{
public:
	Licznik(const std::string& prefixText, const sf::Vector2f& position, const sf::Font& font);

	Licznik operator++(int);
	Licznik operator--(int);

	void reset();
	
	std::string toString() 
	{
		return std::to_string(liczba);
	}

private:
	int liczba;

	sf::Text text;
	std::string prefixText;

	void update() 
	{
		text.setString(prefixText + std::to_string(liczba));  //update wartosci w wyswietlanym w grze tekscie
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const		 
	{			//dziedziczenie metody draw() po klasie sf::Rendertarget
		target.draw(text);
	}
};
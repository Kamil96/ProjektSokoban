#include "Licznik.h"

Licznik::Licznik(const std::string & prefixText, const sf::Vector2f & position, const sf::Font & font) :
	prefixText(prefixText), liczba(0)
{
	text.setPosition(position);
	text.setFont(font);
	update();
}

Licznik Licznik::operator++(int)
{
	Licznik copy(*this);		//tworzenie kopii wartosci
	liczba++;
	update();
	return copy;				//zwracanie starej kopii wartosci
}

Licznik Licznik::operator--(int)
{
	Licznik copy(*this);
	liczba--;
	update();
	return copy;
}

void Licznik::reset()
{
	liczba = 0;
	update();
}

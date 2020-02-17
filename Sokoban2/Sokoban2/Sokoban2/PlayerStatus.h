#pragma once
#include <iostream>

class PlayerStatus
{
public:
	virtual void interakcja() = 0;
};

class RuchLewo
	:public PlayerStatus
{
	void interakcja()
	{
		std::cout << "Ruch w lewo." << std::endl;
	};
};

class RuchPrawo
	:public PlayerStatus
{
	void interakcja() 
	{
		std::cout << "Ruch w prawo." << std::endl;
	};
};

class RuchGora
	:public PlayerStatus
{
	void interakcja()
	{
		std::cout << "Ruch w gore." << std::endl;
	};
};

class RuchDol
	:public PlayerStatus
{
	void interakcja()
	{
		std::cout << "Ruch w dol." << std::endl;
	};
};

class ResetPoziomu
	:public PlayerStatus
{
	void interakcja()
	{
		std::cout << "Zresetowano pozycje skrzyn i gracza." << std::endl;
	};
};
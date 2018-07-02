#pragma once
#include <vector>//#include "CPhysical_obj.h"
#include "Headers.h"
#include "CAutomobile.h"

enum smnm
{
	LEFT_UPPER_CORNER = 0,
	RIGHT_UPPER_CORNER = 1,
	LEFT_BOTTOM_CORNER = 2,
	RIGHT_BOTTOM_CORNER = 3
};

class CBoar
{
	bool launchedstate; // check it during event handling in main to avoid 
	int posX;
	int posY;
	int dimX;
	int dimY;
	SDL_Texture* boartexture;
	SDL_Rect Hitbox;
	int velocity;
	double angle;
	SDL_Point* center;
	int points;
public:
	void eventhandler(const Uint8 * currkstates);
	bool settexture(std::string path);
	std::vector<std::pair<int, int>>* rotatedcoordinates();
	void render();
	bool iscollisiondetected(CAutomobile cauto);
	//bool iscollisiondetected(CWall smwall);
	// sprawdzic tutaj z jakim
	// obiektem wystapila kolizja tzn jesli auto to destroy auto i wyswietl jakas tam 
	//grafike, jesli kolizja ze sciana to odbij 
	// jesli kolizja z car to increase points / mozna tez sprawdzic jaki to obiekt 
	// w source 
	int free(); // function will destroy already launched boar and return 
	// amount of points it gained
	void increasepoints(int apoints); // stworzyc points gettera dla car
	void move();
	void setvelocity(int vel);
	bool stategetter();
	//void checkif(CAutomobile smc);
	CBoar();
	~CBoar();
};


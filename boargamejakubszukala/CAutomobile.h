#pragma once
#include"Headers.h"

//#include <SDL.h>
//#include <SDL_image.h>
#include <string>

class CAutomobile
{
protected:
	int posX;
	int posY;
	int dimX;
	int dimY;
	SDL_Texture* automobiletexture;
	SDL_Rect Hitbox; 
	int velocity;
	int points;

	// kierunek bedzie jeden wiec bedzie sie zwiekszac tylko wspolrzedna x
public:
	void render();
	void setvelocity(int new_vel);
	bool settexture(std::string path); // this function will be used in constructor so it has to has passed a path variable. Uzyjemy dla kazdego typu innej sciezki czyli konstruktor bedzie prostszy
	void free();
	CAutomobile(int new_ypos, std::string path);
	~CAutomobile(); 
	void move();
	int dimXgetter();
	int dimYgetter();
	int posXgetter();
	int posYgetter();
};


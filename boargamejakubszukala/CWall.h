#pragma once

#include <SDL.h>
class CWall
{
	int posX;
	int posY;
	int dimX;
	int dimY;
	SDL_Rect Hitbox;
	double normal; // for collision
public:
	void render();
	CWall(int xpos, int ypos, int xdim, int ydim, double _normal);
	~CWall();
};


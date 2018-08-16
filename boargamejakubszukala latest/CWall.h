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
	int posXgetter();
	int posYgetter();
	int dimXgetter();
	int dimYgetter();
	void render();
	CWall(int xpos, int ypos, int xdim, int ydim, double _normal);
	~CWall();
};


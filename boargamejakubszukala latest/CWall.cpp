#include "CWall.h"
#include "Headers.h"
#include <SDL.h>


int CWall::posXgetter()
{
	return posX;
}

int CWall::posYgetter()
{
	return posY;
}

int CWall::dimXgetter()
{
	return dimX;
}

int CWall::dimYgetter()
{
	return dimY;
}

void CWall::render()
{
	SDL_RenderFillRect(gRenderer, &Hitbox);
}

CWall::CWall(int xpos, int ypos, int xdim, int ydim, double _normal)
{
	posX = xpos;
	posY = ypos;
	dimX = xdim;
	dimY = ydim;
	Hitbox.x = xpos;
	Hitbox.y = ypos;
	Hitbox.w = xdim;
	Hitbox.h = ydim;
	normal = _normal;
}


CWall::~CWall()
{
}

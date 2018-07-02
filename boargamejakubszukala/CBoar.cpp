#include "CBoar.h"
#include "Headers.h"
#include <iostream>
#include <SDL_image.h>
#include "CAutomobile.h"

int CBoar::free()
{
	SDL_DestroyTexture(boartexture);
	boartexture = NULL;
	return points;
}

void CBoar::increasepoints(int apoints)
{
	points += apoints;
}

void CBoar::move()
{
	double rad = (3.14 * angle) / 180;
	
	posX = int(posX + velocity * cos(rad));
	Hitbox.x = posX;
	posY = int(posY + velocity * sin(rad));
	Hitbox.y = posY;
}

void CBoar::setvelocity(int vel)
{
	velocity = vel;
}

bool CBoar::stategetter()
{
	return launchedstate;
}



CBoar::CBoar()
{
	if (settexture("boar1.png") == false)
	{
		std::cout << "error boar texture" << std::endl;
	}
	else
	{
		launchedstate = false;
		posX = 500;
		posY = 600;
		Hitbox.w = dimX;
		Hitbox.h = dimY;
		Hitbox.x = posX;
		Hitbox.y = posY;
		velocity = 0;
		angle = 0;
		center = NULL;
		points = 0;
	}
}


CBoar::~CBoar()
{
	free();
}

void CBoar::eventhandler(const Uint8 * currkstates)
{
	// 
	if (currkstates[SDL_SCANCODE_A])
	{
		angle -= 10.0;
	}
	else if (currkstates[SDL_SCANCODE_D])
	{
		angle += 10.0;
	}
	else if (currkstates[SDL_SCANCODE_W])
	{
		launchedstate = true;
		velocity = 5;
	}
}

bool CBoar::settexture(std::string path)
{
	
	boartexture = NULL;
	SDL_Surface* loadedsurface = IMG_Load(path.c_str());
	if (loadedsurface == NULL)
	{
		std::cout << "error loading boar surface" << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedsurface, SDL_TRUE, SDL_MapRGB(loadedsurface->format, 0, 0, 0));
		boartexture = SDL_CreateTextureFromSurface(gRenderer, loadedsurface);
		if (boartexture == NULL)
		{
			std::cout << "error boar texutre "<<SDL_Error << std::endl;
		}
		else
		{
			dimX = loadedsurface->w;
			dimY = loadedsurface->h;
		}
	}

	return boartexture != NULL;
}

std::vector<std::pair<int, int>>* CBoar::rotatedcoordinates()
{
	//angle in radians 
	double rad = (3.14 * angle) / 180;
	int x, y;
	std::vector<std::pair<int, int>> asd;
	std::pair<int, int > supppair;


	// left upper corner is just posX, posY
	x = posX;
	y = posY;
	supppair.first = x * cos(rad) - y * sin(rad);
	supppair.second = x * sin(rad) + y * sin(rad);
	asd.push_back(supppair);

	//upper right
	
	x = posX + dimX;
	y = posY;
	supppair.first = x * cos(rad) - y * sin(rad);
	supppair.second = x * sin(rad) + y * sin(rad);
	asd.push_back(supppair);

	//bottom left
	x = posX;
	y = posY + dimY;
	supppair.first = x * cos(rad) - y * sin(rad);
	supppair.second = x * sin(rad) + y * sin(rad);
	asd.push_back(supppair);

	//bottom right
	x = posX + dimX;
	y = posY + dimY;
	supppair.first = x * cos(rad) - y * sin(rad);
	supppair.second = x * sin(rad) + y * sin(rad);
	asd.push_back(supppair);
	
	std::vector<std::pair<int, int>>* r = &asd;

	return r;
}

void CBoar::render()
{
	SDL_RenderCopyEx(gRenderer, boartexture, NULL, &Hitbox, angle, center, SDL_FLIP_NONE);
}

bool CBoar::iscollisiondetected(CAutomobile cauto)
{
	std::vector<std::pair<int, int>> *r;
	r = rotatedcoordinates();
	
	// chceck whether any of corners is inside a car 
	if ((r->at(LEFT_UPPER_CORNER).first > cauto.posXgetter()) && (r->at(LEFT_UPPER_CORNER).first < cauto.posXgetter() + cauto.dimXgetter()))
	{
		return true;
	}
	else if (r->at(LEFT_UPPER_CORNER).second > cauto.posYgetter() && r->at(LEFT_UPPER_CORNER).second < cauto.posYgetter() + cauto.dimYgetter())
	{
		return true;
	}

	else if (r->at(RIGHT_UPPER_CORNER).first > cauto.posXgetter() && r->at(RIGHT_UPPER_CORNER).first < cauto.posXgetter() + cauto.dimXgetter())
	{
		return true;
	}
	else if (r->at(RIGHT_UPPER_CORNER).second > cauto.posYgetter() && r->at(RIGHT_UPPER_CORNER).second < cauto.posYgetter() + cauto.dimYgetter())
	{
		return true;
	}

	else if (r->at(LEFT_BOTTOM_CORNER).first > cauto.posXgetter() && r->at(LEFT_BOTTOM_CORNER).first < cauto.posXgetter() + cauto.dimXgetter())
	{
		return true;
	}
	else if (r->at(LEFT_BOTTOM_CORNER).second > cauto.posYgetter() && r->at(LEFT_BOTTOM_CORNER).second < cauto.posYgetter() + cauto.dimYgetter())
	{
		return true;
	}

	else if (r->at(RIGHT_BOTTOM_CORNER).first > cauto.posXgetter() && r->at(RIGHT_BOTTOM_CORNER).first < cauto.posXgetter() + cauto.dimXgetter())
	{
		return true;
	}
	else if (r->at(RIGHT_BOTTOM_CORNER).second > cauto.posYgetter() && r->at(RIGHT_BOTTOM_CORNER).second < cauto.posYgetter() + cauto.dimYgetter())
	{
		return true;
	}

		return false;
}

//bool CBoar::iscollisiondetected(CWall smwall)
//{
//	// check if collision occured with wall and then call call 
//	// a function rebound(Cwall smwall)
//	return false;
//}

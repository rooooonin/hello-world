#include "CAutomobile.h"
#include "Headers.h"
#include <iostream>
#include <SDL_image.h>
void CAutomobile::render()
{
	SDL_RenderCopy(gRenderer, automobiletexture, NULL, &Hitbox);
}

void CAutomobile::setvelocity(int new_vel)
{
	velocity = new_vel;
}

bool CAutomobile::settexture(std::string path)
{
	SDL_Texture* newtexture = NULL;

	if (automobiletexture != NULL)
	{
		//		SDL_DestroyTexture(automobiletexture);
	}

	SDL_Surface* loadedsurface = IMG_Load(path.c_str());
	if (loadedsurface == NULL)
	{
		std::cout << "error, surface "<< path << " couldnt be loaded" << SDL_Error << std::endl;
	}

	else
	{
		// slightly different from tut here
		// optional color key image here
		// remember to set make all the graphics / textures on white background
		// so i wont have to set color keying for each separately :/
		SDL_SetColorKey(loadedsurface, SDL_TRUE, SDL_MapRGB(loadedsurface->format, 255, 255, 255));
		newtexture = SDL_CreateTextureFromSurface(gRenderer, loadedsurface);
		dimX = loadedsurface->w;
		dimY = loadedsurface->h;
		SDL_FreeSurface(loadedsurface);
	}
	automobiletexture = newtexture;
	return automobiletexture != NULL;
}

void CAutomobile::free()
{
	//if texture exists
	if (automobiletexture != NULL)
	{
		SDL_DestroyTexture(automobiletexture);
		posX = 0;
		posY = 0;
		dimX = 0;
		dimY = 0;
		velocity = 0;
		points = 0;
	}
}

CAutomobile::CAutomobile(int new_ypos, std::string path)
{

	if (settexture(path) == false) std::cout << "error setting texture " << std::endl;
	//sprawdziic wczesniejszy car constructor wrazie bledu
	posX = 0;
	posY = new_ypos;
	Hitbox.h = dimY;// nie ustawia sie kurwa nmac 
	Hitbox.w = dimX;
	Hitbox.x = posX;
	Hitbox.y = posY;
	velocity = 1;
	//points = 50;
}

CAutomobile::~CAutomobile()
{
	free();
}

void CAutomobile::move()
{
	// we use hit box to render so we gotta change its position
	posX = posX + velocity;
	Hitbox.x += velocity;
}

int CAutomobile::dimXgetter()
{
	return dimX;
}

int CAutomobile::dimYgetter()
{
	return dimY;
}

int CAutomobile::posXgetter()
{
	return posX;
}

int CAutomobile::posYgetter()
{
	return posY;
}

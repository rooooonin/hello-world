#include "CCar.h"


//bool CCar::settexture()
//{
//	SDL_Texture* newtexture = NULL;
//	
//	if (automobiletexture != NULL)
//	{
////		SDL_DestroyTexture(automobiletexture);
//	}
//
//	SDL_Surface* loadedsurface = IMG_Load("Batmobile.png");
//	if (loadedsurface == NULL)
//	{
//		std::cout << "error, surface Batmobile.png couldnt be loaded" << SDL_Error << std::endl;
//	}
//
//	else
//	{
//		// slightly different from tut here
//		// optional color key image here
//		newtexture = SDL_CreateTextureFromSurface(gRenderer, loadedsurface);
//		dimX = loadedsurface->w;
//		dimY = loadedsurface->h;
//		SDL_FreeSurface(loadedsurface);
//	}
//	automobiletexture = newtexture;
//	return automobiletexture != NULL;
//}

CCar::CCar(int new_ypos):CAutomobile(new_ypos, "car.png")
{
	points = 50;
	//nwm co jest wywolane pierwsze jesli najpierw ten a potem drugi to luz a na odwrot to katastrofa
	//if (!settexture()) std::cout << "car texture loading error!" << std::endl;
}

CCar::~CCar()
{
	free();
	// gotta define destructor here !!!!!
}

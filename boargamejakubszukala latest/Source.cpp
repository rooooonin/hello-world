#include "Headers.h"
#include "CCar.h"
#include "CTrashcar.h"
#include "CTir.h"
#include <ctime>
#include <cstdlib>
#include "CTraffic.h"
#include "CBoar.h"
#include "CWall.h"
#include <iostream>
#include <SDL_image.h>
#include<list>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Texture* background = NULL;
SDL_Texture* endgame_background = NULL;

CTraffic firstlane = { 0 };
CTraffic secondlane = { 1 };
CTraffic thirdlane = { 2 };


// callbacl is suppose to set traffic.wait = false after some random time 
// prawdopodobnie to nie zadziala wiec szuukac tu bledu

Uint32 callback(Uint32 interval, void* param)
{
	CTraffic* k = static_cast<CTraffic*>(param);
	k->setwaitstate(false);
	
	return 0;
}


// 75 / 225 / 375
void addingcars(CTraffic &t, int trand)
{
	int pos;
	if (t.getlane() == 0)
	{
		//pos = 75;
		pos = 10;
	}
	else if(t.getlane() == 1)
	{
		pos = 160;
		//pos = 225;
	}
	else if (t.getlane() == 2)
	{
		pos = 310;
		//pos = 375;
	}
	// --------------------------------------------------------------------
	if (trand == 0)
	{
		CAutomobile* r = new CCar(pos);
		t.addcar(r);
	}
	else if (trand == 1)
	{
		CAutomobile* r = new CTrashcar(pos);
		t.addcar(r);
	}
	else if (trand == 2)
	{
		CAutomobile* r = new CTir(pos);
		t.addcar(r);
	}
	/*if (trand == 0)
	{
		if (t.getlane() == 0)
		{
			CAutomobile* r = new CCar(75);
		}
		
	}*/
}

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		std::cout << "init error!" << std::endl;
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "filtering nonlinear!" << std::endl;
			success = false;
		}
		else
		{
			gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			if (gWindow == NULL || gScreenSurface == NULL)
			{
				std::cout << "error" << std::endl;
				success = false;
			}
			else
			{
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
				if (gRenderer == NULL)
				{
					std::cout << "error" << std::endl;
					success = false;
				}
				else
				{
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						std::cout << "error" << std::endl;
						success = false;
					}
					
				}
			}
		}
	}
	return success;
}

SDL_Texture* loadbackground(std::string path)
{
	SDL_Texture* newtexture = NULL;
	SDL_Surface* optimizedsurface;
	SDL_Surface* loadedsurface = IMG_Load(path.c_str());
	if (loadedsurface == NULL)
	{
		std::cout << " error while loading surface" << SDL_Error << std::endl;
		return NULL;
	}
	else
	{
		optimizedsurface = SDL_ConvertSurface(loadedsurface, gScreenSurface->format, NULL);
		if (optimizedsurface != NULL)
		{
			newtexture = SDL_CreateTextureFromSurface(gRenderer, optimizedsurface);
		}
	}
	return newtexture;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	// free textures here 


	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
// addfunction loadmedia and use it during initialization proccess in main 
int main(int argc, char* args[])
{
	int all_points = 0;
	srand(time(NULL));
	CWall wallleft = {0, 0, 10,800, 0 };
	CWall wallright = { 1009, 0, 20,1024, 180 };
	CWall* pointer_walleft = &wallleft;
	CWall* pointer_wallright = &wallright;
	int antiloop_counter = 0;
	
	if (!init())
	{
		std::cout << " error with initialization! " << SDL_Error << std::endl;
	}
	else
	{
		background = loadbackground("Road.png");
		endgame_background = loadbackground("endgamebackground.png");
		bool quit = false;

		SDL_Event e;
		std::list<CBoar> allboars(10);

		//CCar asd = { 1 };
		//CTrashcar asd = { 1 };
		//CTir asd = { 1 };
		//asd.setvelocity(5);

		while (!quit)
		{
			while (SDL_PollEvent(&e)!=0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			//asd.move();

			// for first lane 
			
			// wywala blad poniewaz moja callback jest funkkcja widoczna DLA INNYCH 
			// FUNKCJI tylko w obrebie jednego pliku wiec sdl addtimer nie widzi tej funkcji 
			// poniewaz jest ona statyczna 
			if (firstlane.getwaitstate() == false)
			{
				int randomizer = (rand() * 7) % 3;
				addingcars(firstlane, randomizer); // in adding cars wait is set to true
				int time = ((rand() % 40) + 40) * 100;
				CTraffic* c = &firstlane;
				SDL_TimerID timerid = SDL_AddTimer(time, callback, c);
			}

			if (secondlane.getwaitstate() == false)
			{
				int randomizer = (rand() * 7) % 3;
				addingcars(secondlane, randomizer);
				int time = ((rand() % 40) + 40) * 100;
				CTraffic* c = &secondlane;
				SDL_TimerID timerid = SDL_AddTimer(time, callback, c);
			}

			if (thirdlane.getwaitstate() == false)
			{
				int randomizer = (rand() * 7) % 3;
				addingcars(thirdlane, randomizer);
				int time = ((rand() % 40) + 40) * 100;
				CTraffic* c = &thirdlane;
				SDL_TimerID timerid = SDL_AddTimer(time, callback, c);
			}
			
			// checking whether a car is out of a screen

			// ill put here rendering shit but gotta check whether its position 
			// afffects game's performance 
			// czyli czy to ze najpierw jest np renderowany a potem update pozyucji
			
			// state checking
			// returns pointer to array consisted of all keys states
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			// allows to control boar only before launch



			//for (auto itr = allboars.begin(); itr != allboars.end(); itr++)
			//{
			//	if (!(itr->stategetter()))
			//	{
			//		itr->eventhandler(currentKeyStates);
			//	}
			//	//if(!ad.stategetter()) ad.eventhandler(currentKeyStates);
			//}
			// so ill work only on first boar and then at the end of a loop 
			// ill update state of list 


			if (allboars.size() == 0)
			{
				SDL_Rect endgamequad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 3); // XDDD
				SDL_RenderFillRect(gRenderer, NULL);
				SDL_RenderPresent(gRenderer);
				continue;
			}
			auto itr = allboars.begin();
			bool toremove = false;
			

			if (!(itr->stategetter()))
			{
				itr->eventhandler(currentKeyStates);
			}

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//background
			SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			SDL_RenderCopy(gRenderer, background, NULL, &renderQuad);

			//walls
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 0xFF);

			wallleft.render();
			wallright.render();

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			// boar
			
			if (itr->stategetter())
			{
				int this_points = 0;
				int counter = 0;
				
				// cars which status should be updated

				std::vector<int> carshit;

				
				auto firstvector = firstlane.lanecarsgetter(); // vector of pointers
				for (auto itr1 = firstvector->begin(); itr1 != firstvector->end(); itr1++)
				{
					if (itr->iscollisiondetected(*itr1)) // in iscollisiondetected i compute position everytime function is called which is ppretty big mistake and waste of computing power
					{
						if ((*itr1)->points_getter() == -100)
						{
							toremove = true;
						}
						carshit.push_back(counter);
					}
					counter++;
				}
				// przeniesc do funkcji te inty ktore maja zostac usuniete
				this_points = this_points + firstlane.carshitten(carshit); // it can return points
				carshit.clear();


				counter = 0;
				auto secondvector = secondlane.lanecarsgetter();
				for (auto itr2 = secondvector->begin(); itr2 != secondvector->end(); itr2++)
				{
					if (itr->iscollisiondetected(*itr2))
					{
						if ((*itr2)->points_getter() == -100)
						{
							toremove = true;
						}
						carshit.push_back(counter);
					}
					counter++;
				}
				this_points = this_points + secondlane.carshitten(carshit);
				carshit.clear();


				counter = 0;
				auto thirdvector = thirdlane.lanecarsgetter();
				for (auto itr3 = thirdvector->begin(); itr3 != thirdvector->end(); itr3++)
				{
					if (itr->iscollisiondetected(*itr3))
					{
						if ((*itr3)->points_getter() == -100)
						{
							toremove = true;
						}
						carshit.push_back(counter);
					}
					counter++;
				}
				this_points = this_points + thirdlane.carshitten(carshit);
				carshit.clear();

				all_points += this_points;

				itr -> move();
			}

			if (itr->posYgetter() < 0 || itr->posYgetter() > 768)
			{
				toremove = true;
			}

			if (itr->iscollisiondetected(pointer_walleft))
			{
				antiloop_counter++;
				if (antiloop_counter > 3)
				{
					toremove = true;
					antiloop_counter = 0;
				}
				itr->rebound(0.0);
			}
			if (itr->iscollisiondetected(pointer_wallright))
			{
				antiloop_counter++;
				if (antiloop_counter > 3)
				{
					toremove = true;
					antiloop_counter = 0;
				}
				itr->rebound(180.0);
			}

			itr -> render();
			if (toremove == true)
			{
				allboars.erase(itr);
				toremove = false;
			}
			
			
			std::cout << "all points" << all_points << std::endl;

			//lanes
			firstlane.updateposition();
			secondlane.updateposition();
			thirdlane.updateposition();
			
			SDL_RenderPresent(gRenderer);
		}
	}

	return 0;
}
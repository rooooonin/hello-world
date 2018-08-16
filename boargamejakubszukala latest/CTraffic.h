#pragma once
#include <vector>
//#include "CBoar.h"
//#include "Headers.h"
//#include <vector>
//#include "CAutomobile.h"
#include "CBoar.h"
//#include"CPhysical_obj.h"
class CTraffic
{
	//stworzyc flagi ktore beda sprawdzane za kazdym razem 
	// kiedy main loop bedzie sie wykonywala, polegac beda na tym ze jesli 
	// flaga np wait == true tzn ze jest wezwana callback function ktora oczekuje na
	//wygenerowanie samochodu, po wykonaniu tej funkcji bool wait== false 
	// i wtedy moze wykona
	bool wait;
	std::vector<CAutomobile*> lanecars;
	int lane;
public:
	//void delay(int time); 
	void addcar(CAutomobile* smcar);// after adding car 
	void destroycar();
	int getlane();
	bool getwaitstate();
	CTraffic(int _lane);
	~CTraffic();
	//Uint32 callback(Uint32 interval, void* param); // posible mistake here 
	// i dunno whether it will work as a call back when called in sdl timer 0-0 
	void updateposition();
	void setwaitstate(bool state);
	void crashdetection(CBoar s);
	std::vector<CAutomobile*> * lanecarsgetter();
	int carshitten(std::vector<int> hit);
};
#include "CTraffic.h"
#include "CAutomobile.h"
#include "CCar.h"
//#include"CBoar.h"

void CTraffic::addcar(CAutomobile * smcar)
{
	lanecars.push_back(smcar);
	wait = true;
	// at the end set wait = true;
}


int CTraffic::getlane()
{
	return lane;
}

bool CTraffic::getwaitstate()
{
	return wait;
}

CTraffic::CTraffic(int _lane)
{
	lane = _lane;
	wait = false;
}

CTraffic::~CTraffic()
{
}

//Uint32 CTraffic::callback(Uint32 interval, void * param)
//{
//	wait = false;
//	return 0;
//}

void CTraffic::updateposition()
{
	for (int i = 0 ; i < lanecars.size(); i++)
	{
		lanecars[i]->move();
		lanecars[i]->render(); 
	}
}

void CTraffic::setwaitstate(bool state)
{
	wait = state;
}

void CTraffic::crashdetection(CBoar s)
{

}

std::vector<CAutomobile*>* CTraffic::lanecarsgetter()
{
	std::vector<CAutomobile*> * cars = &lanecars;
	return cars;
}

int CTraffic::carshitten(std::vector<int> hit)
{
	int points = 0;
	for (int i = 0; i < lanecars.size(); i++)
	{
		for (int k = 0; k < hit.size(); k++)
		{
			if (i == hit[k])
			{
				points = lanecars[i]->points_getter();
				lanecars[i]->free();
			}
		}
	}
	return points;
}



//void CTraffic::checkforcollision(CBoar b)
//{
//
//}



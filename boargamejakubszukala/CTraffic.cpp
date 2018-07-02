#include "CTraffic.h"
#include "CAutomobile.h"
//#include"CBoar.h"

void CTraffic::addcar(CAutomobile * smcar)
{
	lanecars.push_back(smcar);
	wait = true;
	// at the end set wait = true;
}

void CTraffic::destroycar()
{

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

//void CTraffic::checkforcollision(CBoar b)
//{
//
//}



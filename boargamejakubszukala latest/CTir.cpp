#include "CTir.h"
//#include "CAutomobile.h"

CTir::CTir(int new_ypos):CAutomobile(new_ypos, "truck.png")
{
	points = -100;
}

CTir::~CTir()
{
	free();
}

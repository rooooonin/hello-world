#include "CTrashcar.h"




CTrashcar::CTrashcar(int new_ypos):CAutomobile(new_ypos,"trashtruck.jpg")
{
	points = 100;
}

CTrashcar::~CTrashcar()
{
	free();
}

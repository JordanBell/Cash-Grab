#include "RoomHallways_Lower.h"


RoomHallways_Lower::RoomHallways_Lower(void)
	: Room(0, -2*screen->h, Dimensions(screen->w, screen->h), RoomElement::NORMAL, LAYER_ENV_LOWER)
{
}


RoomHallways_Lower::~RoomHallways_Lower(void)
{
}

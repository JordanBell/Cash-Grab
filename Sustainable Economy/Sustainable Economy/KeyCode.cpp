#include "KeyCode.h"
#include "Machine.h"

//void KeyCode::up(void)
//{
//	player->face_direction(Player::UP);
//}
//
//void KeyCode::down(void)
//{
//	//Call code from all objects to respond
//}
//
//void KeyCode::left(void)
//{
//	//Call code from all objects to respond
//}
//
//void KeyCode::right(void)
//{
//	//Call code from all objects to respond
//}
//
void KeyCode::enter(void)
{
    machine->dispense();
}

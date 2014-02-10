#ifndef KeyCode_h
#define KeyCode_h

#include "Player.h"
#include "Machine.h"

class KeyCode
{
public:
	KeyCode(Player* player, Machine* machine) : player(player), machine(machine) { }
	KeyCode(void) {}
	~KeyCode(void) {}

	void up()		{player->face_direction(Player::UP);}
	void down()		{player->face_direction(Player::DOWN);}
	void left()		{player->face_direction(Player::LEFT);}
	void right()	{player->face_direction(Player::RIGHT);}
	void enter()	{machine->dispense();}
private:
	Player*  player;
	Machine* machine;
};

#endif
#ifndef keycode_h
#define keycode_h

#include "Player.h"

class Machine;

struct KeyCode
{
	KeyCode(Player* _player, Machine* _machine) : player(_player), machine(_machine) { }
	KeyCode(void) {}
	~KeyCode(void) {}

	void up()			{player->move(Player::UP);}
	void down()			{player->move(Player::DOWN);}
	void left()			{player->move(Player::LEFT);}
	void right()		{player->move(Player::RIGHT);}
	void no_direction()	{player->stop_moving();}
	void enter();
private:
	Player*  player;
	Machine* machine;
};

#endif
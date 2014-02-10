#include "Player.h"

class KeyCode
{
public:
	KeyCode(Player* player, Machine* machine) : player(player), machine(machine) { }
	KeyCode(void) {}
	~KeyCode(void) {}

	void up()			{player->face_direction(Player::UP);}
	void down()			{player->face_direction(Player::DOWN);}
	void left()			{player->face_direction(Player::LEFT);}
	void right()		{player->face_direction(Player::RIGHT);}
	void no_direction()	{player->stop_moving();}
	void enter()		{machine->dispense();}
private:
	Player*  player;
	Machine* machine;
};


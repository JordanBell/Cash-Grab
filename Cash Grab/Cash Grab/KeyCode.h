#ifndef keycode_h
#define keycode_h

#include "Player.h"

class Machine;

struct KeyCode
{
	KeyCode(void) {}
	~KeyCode(void) {}

	void up()			{ g_player->SetDirection(Player::UP); }
	void down()			{ g_player->SetDirection(Player::DOWN); }
	void left()			{ g_player->SetDirection(Player::LEFT); }
	void right()		{ g_player->SetDirection(Player::RIGHT); }
	void f()			{ g_player->Interact(); }
	void no_direction()	{ g_player->StopMoving();}
	void _1();

	static void ToggleBool1(void) { bool1 = !bool1; }
private:
	static bool bool1;
};

#endif
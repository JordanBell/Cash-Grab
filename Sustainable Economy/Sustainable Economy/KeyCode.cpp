#include "KeyCode.h"
#include "Machine.h"
#include "Player.h"

void KeyCode::enter(void)
{
    machine->dispense();
	for (Coin* c : g_coins)
	{
		if (!c->moving) {
			int xChange = g_player->x - c->x;
			int yChange = g_player->y - c->y;
			c->LaunchTo(c->x+xChange, c->y+yChange, true);
		}
	}

}

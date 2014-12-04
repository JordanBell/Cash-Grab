#include "KeyCode.h"
#include "Machine.h"
#include "Player.h"

bool KeyCode::bool1 = false;

void KeyCode::_1(void)
{
	if (bool1)
	{
		// Pull (code originally taken from SEConsole)
		//int suppression = 0; // Change this based on what we feel is most effective
		int suppression = 0;

		for (Throwable* t : g_throwables)
		{
			if (!t->IsAirborne()) {
				t->LaunchTo(g_player->x, g_player->y, suppression);
			}
		}
	}
}

void KeyCode::enter(void)
{
    machine->dispense();
}
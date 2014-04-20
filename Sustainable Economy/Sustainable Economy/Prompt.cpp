#include "Prompt.h"
#include "Resources.h"
#include "Game.h"
Prompt::Prompt(Machine* _machine) : Entity((SCREEN_WIDTH - 472) / 2, 5*TILE_SIZE), visible(false), timeSinceFlash(0), machine(_machine)
{
	sprite_sheet = g_resources->GetPromptImage();
}

void Prompt::update(int delta)
{
    //bool shouldFlash = true;
    bool shouldFlash = g_game->wallet >= machine->coinCost;

	if (shouldFlash)
	{
		if (timeSinceFlash >= MS_OF_FLASH) 
		{
			visible = !visible;
			timeSinceFlash = 0;
		}

		timeSinceFlash += delta;
	}
	else visible = false;
}
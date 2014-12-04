#include "Prompt.h"
#include "Resources.h"
#include "Game.h"
#include "Wallet.h"

Prompt::Prompt(Machine* _machine) : GameObject((SCREEN_WIDTH - 472) / 2, 5*TILE_SIZE), visible(false), timeSinceFlash(0), machine(_machine)
{
	m_image = g_resources->GetPromptImage();
}

void Prompt::Update(int delta)
{
    bool shouldFlash = Wallet::GetCoins() >= machine->coinCost;

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
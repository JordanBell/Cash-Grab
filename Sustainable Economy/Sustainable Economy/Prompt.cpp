#include "Prompt.h"
#include "Resources.h"

Prompt::Prompt(int x, int y) : Entity(x, y), visible(false), timeSinceFlash(0)
{
	sprite_sheet = g_resources->GetPromptImage();
}

void Prompt::update(int delta)
{
    bool shouldFlash = true;
    //bool shouldFlash = checkForCoinsOnScreen();

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
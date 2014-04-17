#include "Prompt.h"
#include "Resources.h"

Prompt::Prompt(int x, int y) : Entity(x, y)
{
	sprite_sheet = g_resources->GetPromptImage();
}


Prompt::~Prompt(void)
{
}

void Prompt::update(int delta)
{
    
}

void Prompt::set_skin()
{
    
}
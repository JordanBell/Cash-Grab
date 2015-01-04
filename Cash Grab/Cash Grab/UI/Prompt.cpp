#include "Prompt.h"
#include "Resources.h"
#include "Game.h"
#include "Player.h"

Prompt::Prompt(Player* player) : Sprite(player->x-8, player->y-TILE_SIZE+4), m_Visible(false), m_Source(player)
{
	m_imageSurface = g_resources->GetPromptImage();

	m_animationSpeed = 10;
	m_maxCycles = 4*m_animationSpeed;

	m_renderPriority = LAYER_UI;

	InitSprites();
}

void Prompt::Update(int delta)
{
	Sprite::Update(delta);
	//IncCycle(); UpdateImageRect();
	
	// Follow its source (the player)
	x = m_Source->x-3;
	y = m_Source->y - TILE_SIZE + 4;

	//printf("%f, %f, %f, %f\n", m_imageRect->x, m_imageRect->y, m_imageRect->w, m_imageRect->h);
	//printf("%f, %f, %f, %f\n", sprites[m_cycle]->x, sprites[m_cycle]->y, sprites[m_cycle]->w, sprites[m_cycle]->h);
}


void Prompt::InitSprites(void)
{
	//Initialise the clips of the m_imageSurface

    for (int i = 0; i < 4; i++)
    {
        SDL_Rect* clip = new SDL_Rect();
            
        clip->x = i * TILE_SIZE;
        clip->y = 0,
            
        clip->w = TILE_SIZE;
        clip->h = TILE_SIZE;
            
        sprites[i] = clip;
    }
}

//void Prompt::Update(int delta)
//{
//    bool shouldFlash = Inventory::GetCoins() >= machine->coinCost;
//
//	if (shouldFlash)
//	{
//		if (timeSinceFlash >= MS_OF_FLASH) 
//		{
//			visible = !visible;
//			timeSinceFlash = 0;
//		}
//
//		timeSinceFlash += delta;
//	}
//	else visible = false;
//}
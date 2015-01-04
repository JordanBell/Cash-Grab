#include "Key.h"
#include "Inventory.h"

Key::Key(const int x1, const int y1, const int x2, const int y2, const int id)
	: Throwable(x1, y1, x2, y2), m_ID(id)
{
	m_imageSurface = g_resources->GetKeySheet();

	// Set the element based on the door it opens
	if (id == DOOR_ID_TOICE) m_Element = Element::ICE;
	else if (id == DOOR_ID_TOFIRE) m_Element = Element::FIRE;
	else m_Element = Element::NORMAL;

	// Initialise the sprites with that information
	InitSprites();
}

void Key::OnCollect(void) 
{ 
	g_player->Say("I got a key!"); 
	Inventory::GetInstance().AddKeyID(m_ID); 
}

void Key::InitSprites(void)
	{
		for (int i = 0; i < 8; i++)
		{
			SDL_Rect* clip = new SDL_Rect();
		
			clip->x = TILE_SIZE * i;
			clip->w = clip->h = TILE_SIZE;
			clip->y = m_Element * TILE_SIZE;
        
			m_Sprites[i] = clip;
		}
	}
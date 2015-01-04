#include "CoinGold.h"
#include "Game.h"
#include "Resources.h"
#include "Inventory.h"

int CoinGold::value = 10;

void CoinGold::OnCollect(void)
{ 
	// Play the basic coin sound
	Mix_PlayChannel(-1, g_resources->GetCoinSound_Gold(), 0);
    
	Inventory::GetCoinWallet(m_Element)->Add(value);
	g_player->IncSpeed(SPEED_GAIN*value);
}

void CoinGold::InitSprites(void)
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = new SDL_Rect();
		
		clip->x = TILE_SIZE * i;
		clip->y = (2 + m_Element*4) * TILE_SIZE; // Change with the element along the possible gold coin rows in the sheet
		clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
	}
}
#include "CoinSilver.h"
#include "Game.h"
#include "Resources.h"
#include "Inventory.h"
#include "EffectSmash.h"

int CoinSilver::value = 5;

void CoinSilver::OnCollect(void)
{ 
	// Play the basic coin sound
    Mix_PlayChannel(-1, g_resources->GetCoinSound_Silver(), 0);
    
	Inventory::GetCoinWallet(m_Element)->Add(value);
	g_player->IncreaseSpeed(SPEED_GAIN*value);
}

void CoinSilver::InitSprites(void)
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = new SDL_Rect();
		
		clip->x = TILE_SIZE * i;
		clip->y = (1 + m_Element*4) * TILE_SIZE; // Change with the element along the possible silver coin rows in the sheet
		clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
	}
}
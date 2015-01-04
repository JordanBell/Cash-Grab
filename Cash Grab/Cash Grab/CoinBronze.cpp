#include "CoinBronze.h"
#include "Game.h"
#include "Resources.h"
#include "Inventory.h"
#include "EffectMagnetism.h"

int CoinBronze::value = 1;

void CoinBronze::OnCollect(void)
{ 
    Mix_PlayChannel(-1, g_resources->GetCoinSound(0), 0);
//    Mix_FadeInChannel(-1, g_resources->GetCoinSound_Bronze(), 0, rand() % 300);
    
	Inventory::GetCoinWallet(m_Element)->Add(value); 
	g_player->IncSpeed(SPEED_GAIN*value);
}

void CoinBronze::InitSprites(void)
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = new SDL_Rect();
		
		clip->x = TILE_SIZE * i;
		clip->y = (m_Element*4) * TILE_SIZE; // Change with the element along the possible gold coin rows in the sheet
		clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
	}
}
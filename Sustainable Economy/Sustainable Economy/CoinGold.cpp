#include "CoinGold.h"
#include "Game.h"
#include "Resources.h"

void CoinGold::OnCollect(void)
{ 
	// Play the basic coin sound
    Mix_PlayMusic(g_resources->GetCoinSound_Gold(), 0);
	g_game->IncWalletBy(10); 
}

void CoinGold::InitSheet(void)
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = new SDL_Rect();
		
		clip->x = TILE_SIZE * i;
		clip->y = 2*TILE_SIZE;
		clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
	}
}
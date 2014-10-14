#include "CoinFive.h"
#include "Game.h"

void CoinFive::OnCollect(void)
{ 
	g_game->IncWalletBy(5); 
}

void CoinFive::InitSheet(void)
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = new SDL_Rect();
		
		clip->x = TILE_SIZE * i;
		clip->y = TILE_SIZE;
		clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
	}
}
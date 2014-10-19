#include "CoinSilver.h"
#include "Game.h"
#include "Resources.h"

void CoinSilver::OnCollect(void)
{ 
	// Play the basic coin sound
    if (!g_game->IsMuted())
        Mix_PlayChannel(-1, g_resources->GetCoinSound_Silver(), 0);
//		Mix_PlayMusic(g_resources->GetCoinSound_Silver(), 0);
	g_game->IncWalletBy(5);
}

void CoinSilver::InitSheet(void)
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
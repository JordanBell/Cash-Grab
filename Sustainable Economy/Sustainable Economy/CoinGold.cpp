#include "CoinGold.h"
#include "Game.h"
#include "Resources.h"
#include "Wallet.h"

int CoinGold::value = 10;

void CoinGold::OnCollect(void)
{ 
	// Play the basic coin sound
    if (!g_game->IsMuted())
		Mix_PlayChannel(-1, g_resources->GetCoinSound_Gold(), 0);
    
	Wallet::IncCoinsBy(value);
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
#include "CoinSilver.h"
#include "Game.h"
#include "Resources.h"

#include "MagnetismEffect.h"

void CoinBronze::OnCollect(void)
{ 
	// Play the basic coin sound
	if (!g_game->IsMuted())
        Mix_PlayChannel(-1, g_resources->GetCoinSound(0), 0);
    
    g_game->AddEffect(new MagnetismEffect());
    
	// Base Coins do not have special collection effects, just increase money
	g_game->IncWallet(); 
}

void CoinBronze::InitSheet(void)
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = new SDL_Rect();
		
		clip->x = TILE_SIZE * i;
		clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
	}
}
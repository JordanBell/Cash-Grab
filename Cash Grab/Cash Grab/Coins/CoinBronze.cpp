#include "CoinBronze.h"
#include "Game.h"
#include "Resources.h"
#include "Wallet.h"
#include "EffectMagnetism.h"

int CoinBronze::value = 1;

void CoinBronze::OnCollect(void)
{ 
	// Play the basic coin sound
    if (!g_game->IsMuted()) {
        Mix_PlayChannel(-1, g_resources->GetCoinSound(0), 0);
//        Mix_FadeInChannel(-1, g_resources->GetCoinSound_Bronze(), 0, rand() % 300);
    }
    
	Wallet::IncCoinsBy(value); 
	Coin::OnCollect();
}

void CoinBronze::InitSprites(void)
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = new SDL_Rect();
		
		clip->x = TILE_SIZE * i;
		clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
	}
}
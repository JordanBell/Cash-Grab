#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#define NUM_COIN_SOUNDS 3

class Resources
{
private:
	SDL_Surface* m_PlayerSheet, *m_CoinSheet, *m_EnvironmentImage, *m_MoneyMachineSheet, *m_Prompt, *m_Square;
	TTF_Font* m_Font;
    Mix_Music* m_CoinSounds[NUM_COIN_SOUNDS];

public:
	Resources(void);
	~Resources(void);

	SDL_Surface* GetPlayerSheet() { return m_PlayerSheet; }
	SDL_Surface* GetCoinSheet() { return m_CoinSheet; }
	SDL_Surface* GetEnvironmentImage() { return m_EnvironmentImage; }
	SDL_Surface* GetMoneyMachineSheet() { return m_MoneyMachineSheet; }
	SDL_Surface* GetPromptImage() { return m_Prompt; }
    SDL_Surface* GetTestImage() { return m_Square; }
    
    TTF_Font* GetFont() { return m_Font; }
    
    // Get a random coin sound
    Mix_Music* GetCoinSound(int index) { return m_CoinSounds[index]; }
    Mix_Music* GetCoinSound_Bronze(void) { return GetCoinSound(0); }
    Mix_Music* GetCoinSound_Silver(void) { return GetCoinSound(1); }
	Mix_Music* GetCoinSound_Gold(void)   { return GetCoinSound(2); }
};

extern Resources* g_resources;


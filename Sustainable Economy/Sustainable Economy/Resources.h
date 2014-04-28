#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#define NUM_COIN_SOUNDS 3

class Resources
{
private:
	SDL_Surface* m_PlayerSheet, *m_CoinSheet, *m_EnvironmentImage, *m_MoneyMachineSheet, *m_Prompt;
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
    
    TTF_Font* GetFont() { return m_Font; }
    
    // Get a random coin sound
    Mix_Music* GetCoinSound() { return m_CoinSounds[0/*rand() % NUM_COIN_SOUNDS*/]; }
};

extern Resources* g_resources;


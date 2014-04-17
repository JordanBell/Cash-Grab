#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Resources
{
private:
	SDL_Surface* m_PlayerSheet, *m_CoinSheet, *m_EnvironmentImage, *m_MoneyMachineSheet, *m_Prompt;
	TTF_Font* m_Font;

public:
	Resources(void);
	~Resources(void);

	SDL_Surface* GetPlayerSheet() { return m_PlayerSheet; }
	SDL_Surface* GetCoinSheet() { return m_CoinSheet; }
	SDL_Surface* GetEnvironmentImage() { return m_EnvironmentImage; }
	SDL_Surface* GetMoneyMachineSheet() { return m_MoneyMachineSheet; }
	SDL_Surface* GetPromptImage() { return m_Prompt; }
};

extern Resources* g_resources;


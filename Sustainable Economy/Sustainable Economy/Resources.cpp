#include "Resources.h"
#include "toolkit.h"
#include "Player.h"
#include "Coin.h"
#include "Environment.h"
#include "Machine.h"
#include "Prompt.h"

#include <stdexcept>
Resources* g_resources = NULL;

Resources::Resources(void)
{
	// Load the resouce files using SDL
	m_PlayerSheet =			load_image("playerSheet.png");
	m_CoinSheet =			load_image("coinSheet.png");
	m_EnvironmentImage =	load_image("environment.png");
	m_MoneyMachineSheet =	load_image("moneyMachine.png");
	m_Prompt =				load_image("Press Enter.png");
	m_Font =				TTF_OpenFont("joystix monospace.ttf", 28); //Custom font import; size 28

	// Check for failures.
	if ((m_PlayerSheet		  == NULL)	||
		(m_CoinSheet		  == NULL)	||
		(m_EnvironmentImage   == NULL)	||
		(m_MoneyMachineSheet  == NULL)	||
		(m_Prompt			  == NULL)	||
		(m_Font				  == NULL)) 
		{
			throw std::runtime_error("Some of the resources failed to initialise");
		}
}

Resources::~Resources(void)
{
	// Free that shit
	SDL_FreeSurface(m_PlayerSheet);
	SDL_FreeSurface(m_CoinSheet);
	SDL_FreeSurface(m_EnvironmentImage);
	SDL_FreeSurface(m_MoneyMachineSheet);
	SDL_FreeSurface(m_Prompt);
	TTF_CloseFont(m_Font);
}
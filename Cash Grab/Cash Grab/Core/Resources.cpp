#include "Resources.h"
#include "toolkit.h"
#include "Player.h"
#include "Coin.h"
#include "Machine.h"

#include <stdexcept>
// TODO: Make resources a namespace? Replace constructor and destructor with Init()/Load() and Deinit()/Free() respectively?
Resources* g_resources = nullptr;

#define CHECK_NULL(x) x ? "false" : "true"

Resources::Resources(void)
{
	// Load the resouce files using SDL
	m_PlayerSheet =			load_image("playerSheet.png");
	m_CoinSheet =			load_image("coinSheet.png");
	m_EnvironmentImage =	load_image("environment.png");
	m_MoneyMachineSheet =	load_image("moneyMachine.png");
    m_PowerupSheet =        load_image("powerupSheet.png");
	m_Prompt =				load_image("promptSignSheet.png");
    m_Sinkhole =			load_image("sinkhole.png");
    m_ButtonSheet =         load_image("buttons.png");
    m_Speech =			    load_image("speechBubble.png");
    m_KeySheet=			    load_image("keySheet.png");
	m_Font =				TTF_OpenFont("joystix monospace.ttf", 14); //Custom font import; size set
    
    m_Music = Mix_LoadMUS("Main2.wav");
    
    m_CoinSounds[0] = Mix_LoadWAV("Coin1.wav");
    m_CoinSounds[1] = Mix_LoadWAV("Coin2.wav");
    m_CoinSounds[2] = Mix_LoadWAV("Coin3.wav");
    
    Mix_Volume(-1, 10);
    
    
	// Check for failures.
	if (!m_PlayerSheet          ||
		!m_CoinSheet            ||
		!m_EnvironmentImage     ||
		!m_MoneyMachineSheet	||
        !m_PowerupSheet         ||
		!m_Prompt               ||
		!m_Font                 ||
        !m_Sinkhole				||
		!m_ButtonSheet			||
        !m_Speech				||
        !m_KeySheet				||
        !m_Music)
		{

            printf("Player: %s\n", CHECK_NULL(m_PlayerSheet));
            printf("Coin: %s\n", CHECK_NULL(m_CoinSheet));
            printf("Environment: %s\n", CHECK_NULL(m_EnvironmentImage));
            printf("Money machine: %s\n", CHECK_NULL(m_MoneyMachineSheet));
            printf("Powerup: %s\n", CHECK_NULL(m_PowerupSheet));
            printf("Prompt: %s\n", CHECK_NULL(m_Prompt));
            printf("Font: %s\n", CHECK_NULL(m_Font));
            printf("Sinkhole: %s\n", CHECK_NULL(m_Sinkhole));
            printf("Buttons: %s\n", CHECK_NULL(m_ButtonSheet));
            printf("Speech Bubble: %s\n", CHECK_NULL(m_Speech));
            printf("Key: %s\n", CHECK_NULL(m_KeySheet));
            printf("music: %s\n", CHECK_NULL(m_Music));

			// Let me see!!
			SDL_Delay(2000);

			throw std::runtime_error("Some of the resources failed to initialise");
		}
    
    for (int i = 0; i < NUM_COIN_SOUNDS; i++) {
        if (!m_CoinSounds[i]) {
            char *err = nullptr;
            sprintf(err, "Coin sound %d failed to initialise.", i);
            throw std::runtime_error(err);
        }
    }
}

Resources::~Resources(void)
{
	SDL_FreeSurface(m_PlayerSheet);
	SDL_FreeSurface(m_CoinSheet);
	SDL_FreeSurface(m_EnvironmentImage);
	SDL_FreeSurface(m_MoneyMachineSheet);
	SDL_FreeSurface(m_PowerupSheet);
	SDL_FreeSurface(m_Prompt);
    SDL_FreeSurface(m_Sinkhole);
    SDL_FreeSurface(m_ButtonSheet);
    SDL_FreeSurface(m_Speech);
    SDL_FreeSurface(m_KeySheet);
	TTF_CloseFont(m_Font);
    
    Mix_FreeMusic(m_Music);
    
    for (int i = 0; i < NUM_COIN_SOUNDS; i++)
    {
        Mix_FreeChunk(m_CoinSounds[i]);
    }
}

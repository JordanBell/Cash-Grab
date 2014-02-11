#include "toolkit.h"
#include "Game.h"

SDL_Surface* player_sheet, *coin_sheet, *environment, *money_machine, *prompt;

bool load_files() //Load files, and check for the success of each one
{
	player_sheet =	load_image("playerSheet.png");
	coin_sheet =	load_image("coinSheet.png");
	environment =	load_image("environment.png");
	money_machine =	load_image("moneyMachine.png");
	prompt =		load_image("Press Enter.png");
	font =			TTF_OpenFont("joystix monospace.ttf", 28); //Custom font import; size 28

		 if (player_sheet  == NULL)	return false;
	else if (coin_sheet    == NULL)	return false;
	else if (environment   == NULL)	return false;
	else if (money_machine == NULL)	return false;
	else if (prompt		   == NULL)	return false;
	else if (font		   == NULL)	return false;
	else return true;
}

void SDL_deinit()
{
	//Free all of this
	SDL_FreeSurface(player_sheet);
	SDL_FreeSurface(coin_sheet);
	SDL_FreeSurface(environment);
	SDL_FreeSurface(money_machine);
	SDL_FreeSurface(prompt);
	TTF_CloseFont(font);

	//Quit all of that
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!SDL_init()) return 1;

	//Stuff
	//Game game(player_sheet, coin_sheet, environment, money_machine, prompt);
	//game.run();

	Coin test_coin(200, 100, 200, 200);
	
	SDL_deinit();

	return 0;
}
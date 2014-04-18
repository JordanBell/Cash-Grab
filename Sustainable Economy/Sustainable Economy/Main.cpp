#include "toolkit.h"
#include "Coin.h"
#include "Machine.h"
#include "Game.h"
#include <stdexcept>

int main(int argc, char* args[])
{
	if (!SDL_init()) return 1;
	// Get the output lubed up
//	freopen("CON", "wt", stdout);
//	freopen("CON", "wt", stderr);
	 
	//Game Running
	g_game = new Game();
	g_game->run();

	//Machine testMachine(5, 6);
    //testMachine.test_stuff();
	
	SDL_deinit();

	return 0;
}
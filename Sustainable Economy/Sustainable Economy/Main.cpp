#include "toolkit.h"
#include "Coin.h"
#include "Machine.h"
#include "Game.h"
#include <stdexcept>

int main(int argc, char* args[])
{
	if (!SDL_init()) return 1;
    
#ifdef _WIN32
	// Get the output lubed up
	freopen("CON", "wt", stdout);
	freopen("CON", "wt", stderr);
#endif
	 
	//Game Running
	g_game = new Game();
	printf("Hey!");
	g_game->run();
	
	SDL_deinit();

	return 0;
}
#include "SEConsole.h"
#include "Coin.h"
#include "Player.h"
#include "Game.h"

/* Launch all coins at the player */
void Pull(vector<int> args)
{
	for (Coin* c : g_coins)
	{
		if (!c->moving) {
			int xChange = g_player->x - c->x;
			int yChange = g_player->y - c->y;
			c->LaunchTo(c->x+xChange, c->y+yChange, true);
		}
	}
}

/* Forces a player's smash with specified argument */
void Smash(vector<int> args)
	{ g_player->Smash(args.front()); }

/* Turn off all sounds */
void Mute(vector<int> args)
	{ g_game->Mute(); }

/* Turn on all sounds */
void Unmute(vector<int> args)
	{ g_game->Unmute(); }

void AddCoins(vector<int> args)
{
	int numCoins = args.front();
	g_game->IncWalletBy(numCoins);
}


/* Doubles the player's coins */
void DoubleCoins(vector<int> args)
	{ g_game->IncWalletBy(g_game->wallet); }


SEConsole::SEConsole(void)
{
	// All recognised commands
	commands.push_back( 
		Command("pull", "Pulling all coins toward the player.", Pull)
	);

	commands.push_back( 
		Command("mute", "Muted all sounds.", Mute)
	);

	commands.push_back( 
		Command("unmute", "Restored all sounds.", Unmute)
	);

	commands.push_back( 
		Command("add_coins", "Coins added.", AddCoins)
	);

	commands.push_back( 
		Command("smash", "Smashing", Smash)
	);

	commands.push_back( 
		Command("double_coins", "Coins have been doubled", DoubleCoins)
	);
}

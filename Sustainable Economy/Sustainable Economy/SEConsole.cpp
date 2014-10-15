#include "SEConsole.h"
#include "Coin.h"
#include "Player.h"
#include "Game.h"

/* Launch all coins at the player */
void Pull(void)
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

/* Turn off all sounds */
void Mute(void)
	{ g_game->Mute(); }

/* Turn on all sounds */
void Unmute(void)
	{ g_game->Unmute(); }

/* Increase the amount of money by 100 */
void Add100(void)
	{ g_game->IncWalletBy(100); }

/* Increase the amount of money by 1000 */
void Add1000(void)
	{ g_game->IncWalletBy(1000); }

/* Doubles the player's coins */
void DoubleCoins(void)
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
		Command("add_100", "+100 Coins", Add100)
	);

	commands.push_back( 
		Command("add_1000", "+1000 Coins", Add1000)
	);

	commands.push_back( 
		Command("double_coins", "Coins have been doubled", DoubleCoins)
	);
}

#include "SEConsole.h"
#include "Coin.h"
#include "Player.h"
#include "Game.h"

// HAX

/* Launch all coins at the player */
void Pull(vector<int> args)
{
	int suppression = args.empty() ? 0 : args.front();

	for (Throwable* t : g_throwables)
	{
		if (!t->moving) {
			t->LaunchTo(g_player->x, g_player->y, suppression);
		}
	}
}

/* Home coins toward the player */
void HomeIn(vector<int> args)
{
	int distance = args.size() > 0 ? args.at(0) : 400;
	int speed    = args.size() > 1 ? args.at(1) : 10;

	list<Throwable*> closeThrowables = Throwable::ThrowablesAroundPlayer(distance);
	for (Throwable* t : closeThrowables)
	{
		if (!t->moving) {
			t->SetHoming(distance, speed);
		}
	}
}

/* Forces Abilty: Smash. Specifies radius. */
void Smash(vector<int> args)
	{ g_player->Smash(args.front()); }

/* Forces Ability: Smash Wave */
void SmashWave(vector<int> args)
	{ g_player->SmashWave(); }


/* Toggles coin magnetism */
void ToggleMagnetism(vector<int> args)
	{ g_player->SetMagnetic( !g_player->IsMagnetic() ); }



/* Turn off all sounds */
void Mute(vector<int> args)
	{ g_game->Mute(); }

/* Turn on all sounds */
void Unmute(vector<int> args)
	{ g_game->Unmute(); }



/* Add any number of coins to the wallet */
void AddCoins(vector<int> args)
{
	int numCoins = args.front();
	g_game->IncWalletBy(numCoins);
}

/* Add a ludicrous number of coins to the wallet */
void AddCoins_Large(vector<int> args)
{
	g_game->IncWalletBy(999999999);
}

/* Doubles the player's coins */
void DoubleCoins(vector<int> args)
	{ g_game->IncWalletBy(g_game->wallet); }



/* Dispense Coins */
void Dispense(vector<int> args)
	{ g_machine->ForceDispense(args.front()); }




SEConsole::SEConsole(void)
{
	// All recognised commands
	commands.push_back( 
		Command("pull", 
		"Pulling all coins toward the player.", 
		"Launches all coins to the player.", 
		Pull)
	);

	commands.push_back( 
		Command("mag", 
		"Magnetism Toggled", 
		"Toggles player magnetism, making it easier to collect coins.",
		ToggleMagnetism)
	);

	commands.push_back( 
		Command("smash", 
		"Smash Activated.", 
		"Simulates the 'Smash' Ability.",
		Smash)
	);

	commands.push_back( 
		Command("smash_wave", 
		"Wave Smash activated.", 
		"Simulates the 'Smash Wave' Ability.",
		SmashWave)
	);

	commands.push_back( 
		Command("mute", 
		"Muted all sounds.", 
		"Mutes coin collection sound effects.",
		Mute)
	);

	commands.push_back( 
		Command("unmute", 
		"Restored all sounds.", 
		"Restores all coin collection sound effects.",
		Unmute)
	);

	commands.push_back( 
		Command("add_coins", 
		"Coins added.", 
		"Adds a specified number of coins to the player's wallet.",
		AddCoins)
	);

	commands.push_back( 
		Command("max", 
		"Coins added. So many coins.", 
		"Adds 999999999 coins to the player's wallet.",
		AddCoins_Large)
	);

	commands.push_back( 
		Command("double_coins", 
		"Coins have been doubled", 
		"Doubles the player's coins in their wallet.",
		DoubleCoins)
	);

	commands.push_back( 
		Command("dispense", 
		"Dispensing...", 
		"Dispenses a specified number of coins directly into the game. May be unstable.",
		Dispense)
	);

	commands.push_back( 
		Command("home", 
		"Homing in on player.", 
		"Sets all collectables' homing property to true.",
		HomeIn)
	);
}

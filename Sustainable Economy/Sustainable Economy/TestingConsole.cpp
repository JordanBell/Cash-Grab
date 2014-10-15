#include "TestingConsole.h"
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

void Mute(void)
	{ g_game->Mute(); }

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




TestingConsole::TestingConsole(void) : m_active(false), PROMPT("~: ")
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

void TestingConsole::Open(void)  
{ 
	m_active = true;  
	printf("Console Active"); 
	//SDL_EnableUNICODE( SDL_ENABLE );
}

void TestingConsole::Close(void) 
{ 
	m_active = false;  
	printf("\nConsole Inactive\n"); 
	//SDL_EnableUNICODE( SDL_DISABLE );
}

void TestingConsole::Toggle(void) 
{ 
	m_active ? Close() : Open(); 
	if (m_active) NewLine();
}

void TestingConsole::KeyIn(SDL_keysym& keysym)
{
	if (keysym.sym == SDLK_BACKSPACE)
	{ // Backspace pops the last element of the string	
		if (m_line.size() > 0) {
			m_line.pop_back();
		printf("\b \b"); // Backspace on output
		}
	}
	else if ((keysym.sym == SDLK_RETURN))
	{ // Enter enters the code into the console
		printf("\n");
		Enter();
		NewLine();
	}
	else 
	{ // Otherwise, just input the character
		if (ValidationInput(keysym))
			printf("%c", (char)(keysym.unicode));
	}
}


/* Enter the current m_line into the console, invoking any corresponding functions. */
void TestingConsole::Enter(void)
{ 
	//m_line = "pull";
	//m_line = "add_100";
	//m_line = "add_1000";
	//m_line = "double_coins";
	//m_line = "mute";
	//m_line = "unmute";
	for (Command possibleCommand : commands)
	{
		if (m_line == possibleCommand.code)
		{
			// Execute the function
			possibleCommand.func();
			// Output the command's message, ie "Pull activated."
			printf("%s", possibleCommand.message.c_str());
			// Reset the m_line
			m_line.clear();
			// No point to continue searching
			return;
		}
	}

	// If no commands are recognised by now
	printf("Command [%s] not recognised.", m_line.c_str());
	m_line.clear();
}

bool TestingConsole::ValidationInput(SDL_keysym keysym)
{
	bool isMisc = ((keysym.unicode == (Uint16)' ') || (keysym.unicode == (Uint16)'_'));
	bool isNumber = ((keysym.unicode >= (Uint16)'0') && (keysym.unicode <= (Uint16)'9'));
	bool isLowercase = ((keysym.unicode >= (Uint16)'a') && (keysym.unicode <= (Uint16)'z'));
	bool isUppercase = ((keysym.unicode >= (Uint16)'A') && (keysym.unicode <= (Uint16)'Z'));

	// Add the character if it 
    if (isMisc || isNumber || isLowercase || isUppercase)
    {
        //Append the character
        m_line += (char)keysym.unicode;
    }

	return (isMisc || isNumber || isLowercase || isUppercase);
}
#include "TestingConsole.h"

void TestingConsole::Open(void)  
{ 
	m_active = true;  
	printf("Console Active"); 
	SDL_EnableUNICODE( SDL_ENABLE );
}

void TestingConsole::Close(void) 
{ 
	m_active = false;  
	printf("\nConsole Inactive\n"); 
	SDL_EnableUNICODE( SDL_DISABLE );
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
		printf("\b \b"); // Backspace
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
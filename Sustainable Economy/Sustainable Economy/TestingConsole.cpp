#include "TestingConsole.h"
#include <iostream>

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
	// Separate the activation command from its arguments, if any
	pair<string, string> codeArgumentsPair = SplitCommandCode(m_line);
	string activationCode = codeArgumentsPair.first;
	vector<int> arguments = ExtractArguments(codeArgumentsPair.second);

	for (Command possibleCommand : commands)
	{
		if (activationCode == possibleCommand.code)
		{
			// Execute the function
			possibleCommand.func(arguments);
			// Output the command's message, ie "Pull activated."
			printf("%s", possibleCommand.message.c_str());
			// Reset the m_line
			m_line.clear();
			// No point to continue searching
			return;
		}
	}

	// If no commands are recognised by now
	printf("Command [%s] not recognised.", activationCode.c_str());
	m_line.clear();
}

pair<string, string> TestingConsole::SplitCommandCode(string line)
{
	pair<string, string> codeArgumentsPair; // Return
	string head = "";
	string tail = line;

	for (int i = 0; i < line.size(); i++)
	{
		char c = line.at(i);
		tail.erase(0, 1);

		if (c == ' ') {
			// End of command code, beginning of arguments
			codeArgumentsPair.first  = head;
			codeArgumentsPair.second = tail;
			return codeArgumentsPair;
		}
		else
			head.push_back(c);

	}

	codeArgumentsPair.first = line;
	codeArgumentsPair.second = "";
	return codeArgumentsPair;
}

vector<int> TestingConsole::ExtractArguments(string argumentsString)
{
	vector<int> r_args;

	string head = "";
	string tail = argumentsString;

	for (int i = 0; i < argumentsString.size(); i++)
	{
		char c = argumentsString.at(i);
		tail.erase(0, 1);

		if (c == ' ') {
			r_args.push_back(strToInt(head));
			head = "";
		}
		else
		{
			head.push_back(c);
		}

	}

	// Add the last argument
	r_args.push_back(strToInt(head));

	return r_args;
}


int TestingConsole::charToInt(char c)
{
	switch (c)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}

	throw runtime_error("Character given in charToInt is not a number.");
	return -1;
}

int TestingConsole::strToInt(string str)
{
	int digit = pow(10, (str.size()-1)); // A multiplier for the selected digit
	int r_int = 0;

	for (char c : str)
	{
		try {
			// Get the integer for that character
			r_int += digit * charToInt(c);

			// Move to the next digit
			digit /= 10;
		}
		catch (runtime_error) {
			throw runtime_error("The string passed to strToInt does not contain a valid number. All characters must be numerical digits.");
		}
	}

	return r_int;
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
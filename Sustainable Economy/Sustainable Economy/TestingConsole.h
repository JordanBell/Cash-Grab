#pragma once
#include <string>
#include <list>
#include <functional>
#include <type_traits>
#include <vector>
#include "SDL.h"
using namespace std;

class TestingConsole
{
public:
	TestingConsole(void) : m_active(false), PROMPT("~: ") {}
	~TestingConsole(void) {}
	
	void Toggle(void);
	bool IsActive(void) { return m_active; }

	void Enter(void);
	void KeyIn(SDL_keysym& keysym); // Enter the keysym, which contains information on the SDLKey and unicode values

protected:
	struct Command
	{
		Command(string _code, string _message, void (*_func)(vector<int>))
			: code(_code), message(_message), func(_func) {}

		string code;		// The string that invokes a console response
		string message;		// The response that is printed to acknowledge its activation
		void (*func)(vector<int>);	// The function that is run when the string is called
	};

	list<Command> commands; // All commands recognised by the testing console

private:
	void Open(void);
	void Close(void);
	void NewLine(void) { m_line.clear(); printf("\n%s", PROMPT.c_str()); }
	bool ValidationInput(SDL_keysym keysym);
	static pair<string, string> SplitCommandCode(string line); // Return a pair of strings. The first being the activation code, the second being the arguments
	static vector<int> ExtractArguments(string argumentsString); // Returns a vector of arguments from a string of suppose arguments
	
	// nobody told me about atoi
	static int charToInt(char c);
	// forgive me
	static int strToInt(string str);
	
	string PROMPT;
	string m_line;
	bool m_active;
};


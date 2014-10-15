#pragma once
#include <string>
#include <list>
#include <functional>
#include <type_traits>
#include "SDL.h"
using namespace std;

class TestingConsole
{
public:
	TestingConsole(void);
	~TestingConsole(void) {}
	
	void Toggle(void);
	bool IsActive(void) { return m_active; }

	void Enter(void);
	void KeyIn(SDL_keysym& keysym); // Enter the keysym, which contains information on the SDLKey and unicode values

private:
	void Open(void);
	void Close(void);
	void NewLine(void) { m_line.clear(); printf("\n%s", PROMPT.c_str()); }
	bool ValidationInput(SDL_keysym keysym);

	struct Command
	{
		Command(string _code, string _message, void (*_func)(void))
			: code(_code), message(_message), func(_func) {}

		string code;		// The string that invokes a console response
		string message;		// The response that is printed to acknowledge its activation
		void (*func)(void);	// The function that is run when the string is called
	};

	string PROMPT;
	list<Command> commands; // All commands recognised by the testing console
	bool m_active;
	string m_line;
};


#pragma once
#include "GameObject.h"
#include <string>
#include <list>
#include "XY.h"
using namespace std;

#define MAX_WIDTH 3
#define TEXT_SIZE 10
#define OFFSET_X (4)
#define OFFSET_Y (-40)

class SpeechBubble : public GameObject
{
public:
	// Construct based on a game object source.
	SpeechBubble(GameObject* source, const string phrase, const int timeout = 100) 
	: GameObject(source->x + OFFSET_X, source->y + OFFSET_Y), m_Phrase(phrase), m_Source(source), m_Timeout(timeout)
	{ Init(phrase); }


	// Construct independently
	SpeechBubble(const int _x, const int _y, const string phrase, const int timeout = 100) 
	: GameObject(_x + OFFSET_X, _y + OFFSET_Y), m_Phrase(phrase), m_Source(nullptr), m_Timeout(timeout)
	{ Init(phrase); }

	void Render(void) override final;
	void Update(int delta) override final;

private:
	SDL_Surface* m_TextSurface;
	Position m_TextPosition;
	TTF_Font* m_Font;
	string m_Phrase;

	// The game object that this speech bubble appears over, if any.
	GameObject* m_Source;

	// The time at which this deletes itself and disappears
	int m_Timeout;
	

	// Initialise (construct)
	void Init(const string phrase);

	// Used to render the bubble segments: Pairs of render rects and their rendering positions
	list< pair<SDL_Rect*, Position> > m_RenderPairs;

	// Initialise the text surface
	void InitText(string phrase);
};


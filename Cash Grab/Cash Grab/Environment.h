#ifndef environment_h
#define environment_h

#include "gameObject.h"
#define SHEET_WIDTH 27
#define SHEET_HEIGHT 4

class Environment :
	public GameObject
{
public:
	Environment(int x, int y);
	~Environment(void);

	virtual void Render(void) override;

protected:
	SDL_Rect* sprites[SHEET_WIDTH][SHEET_HEIGHT]; //All of the clip positions

	// Build a station object starting at a given top left position
	void BuildStationWalls(const int x, const int y);
	virtual void BuildStationRest(const int x, const int y);
	virtual void BuildWalls(void); // Different implementations for subclasses

	inline SDL_Rect* GetEnvironmentRect(int featureIndex, int elementIndex)
		{ return sprites[featureIndex][elementIndex]; }
};

extern Environment* g_environment;

#endif
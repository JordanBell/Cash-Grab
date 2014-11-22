#ifndef environment_h
#define environment_h

#include "gameObject.h"
#define SHEET_WIDTH 8
#define SHEET_HEIGHT 8

class Environment :
	public GameObject
{
public:
	Environment(int x, int y);
	~Environment(void);

	virtual void Render(void) override;

protected:
	SDL_Rect* sprites[SHEET_WIDTH][SHEET_HEIGHT]; //All of the clip positions
	// Sprite identifiers for certain objects' clips.
	SDL_Rect* rect_floor;
	SDL_Rect* rect_floorBrown;
	SDL_Rect* rect_wall;
	SDL_Rect* rect_wallBottom;
	SDL_Rect* rect_wallDoorShadow;
	SDL_Rect* rect_wallDoor_Left;
	SDL_Rect* rect_wallDoor_Right;
	SDL_Rect* rect_wallTopOpen_Left;
	SDL_Rect* rect_wallTopOpen_Right;
	SDL_Rect* rect_clock1;
	SDL_Rect* rect_clock2;
	SDL_Rect* rect_paper1;
	SDL_Rect* rect_paper2;

	// Different wall tops
	SDL_Rect* rect_wallTop;
	SDL_Rect* rect_wallTop_Top;
	SDL_Rect* rect_wallTop_Bottom;
	SDL_Rect* rect_wallTop_Left;
	SDL_Rect* rect_wallTop_Right;
	SDL_Rect* rect_wallTop_BRCorner;
	SDL_Rect* rect_wallTop_BLCorner;
	SDL_Rect* rect_wallTop_TRCorner;
	SDL_Rect* rect_wallTop_TLCorner;

	// Build a station object starting at a given top left position
	void BuildStationWalls(const int x, const int y);
	virtual void BuildStationRest(const int x, const int y);
	virtual void BuildWalls(void); // Different implementations for subclasses
};

extern Environment* g_environment;

#endif
#ifndef environment_h
#define environment_h

#include "entity.h"

class Environment :
	public Entity
{
public:
	Environment(int x, int y);
	~Environment(void);

	void update(int delta) {}
	void render();

private:
	SDL_Rect* sprites[4][3]; //All of the clip positions
	// Sprite identifiers for certain objects' clips.
	SDL_Rect* rect_floor;
	SDL_Rect* rect_floorBrown;
	SDL_Rect* rect_wall;
	SDL_Rect* rect_wallBottom;
	SDL_Rect* rect_wallDoor;
	SDL_Rect* rect_wallTop;
	SDL_Rect* rect_clock1;
	SDL_Rect* rect_clock2;
	SDL_Rect* rect_paper1;
	SDL_Rect* rect_paper2;

	//SDL_Surface* entire_image; //The culmination of the total image made by the code in the constructor.

	void set_skin() { skin = nullptr; };
};

extern Environment* g_environment;

#endif
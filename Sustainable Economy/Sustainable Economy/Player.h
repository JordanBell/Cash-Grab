#ifndef player_h
#define player_h

#include "Entity.h"

class Player : public Entity {
public:
	static const int UP		= 0;
	static const int RIGHT	= 1;
	static const int DOWN	= 2;
	static const int LEFT	= 3;

	static const int STILL	= 1;
	
	//De/Constructors
	Player(void);
	~Player() { }
	
	void face_direction (int direction) {moving = true; direction = direction;};
	void stop_moving () {moving = false;};

	void update();

private:
	int direction; //The direction being faced by the player
	bool moving;
	SDL_Rect* sprites[ 4 ][ 3 ]; //The 12 sprite locations in the sprite sheet

	void set_skin() { skin = sprites[direction][cycle]; };
};

#endif
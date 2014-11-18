#ifndef player_h
#define player_h
#include "Collidable.h"
#include <math.h>

#define SPEED 0.3 // The movement speed (independent of framerate)
#define WALK_SPEED 10 // The number of frames between cycle changes
#define WALK_CYCLE_LENGTH 4
#define STILL 1
#define SMASH_LIMIT 500
#define SMASH_INTERVAL 50

class Player : public Collidable {
public:
	
	//De/Constructors
	Player(int x, int y);
	~Player(void);
    
    // For collision detection
    bool m_CanMove;
	
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NULLDIR
	} Directions;

	void move(int direction);
	void stop_moving(void);
    void SetCanMove(bool canMove);
	void update(int delta);
    void render();
    void DoMove();
	void Smash(int radius);
	void SmashWave() { smashCount = 0; }

protected:
	void IncCycle(void);
    void SnapToGrid(void);

private:
	bool m_evasion1;
	bool m_evasion2;
	int direction; //The direction being faced by the player
	int smashCount;
	bool moving;
	SDL_Rect* sprites[ 4 ][ 4 ]; //The 16 sprite locations in the sprite sheet

	void set_skin() { skin = (moving) ? sprites[direction][cycle/WALK_SPEED] : sprites[direction][STILL]; };
	void SmashUpdate(void);
};

extern Player *g_player;

#endif
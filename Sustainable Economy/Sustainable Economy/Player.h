#ifndef player_h
#define player_h
#include "Collidable.h"
#include <math.h>

#define SPEED 0.3 // The movement speed (independent of framerate)
#define WALK_SPEED 5 // The number of frames between cycle changes
#define PLAYER_WIDTH 16 // Width of 16px on screen
#define STILL 1

class Player : public Collidable {
public:
	enum {
		UP,
		RIGHT,
		DOWN,
		LEFT
	} Directions;
    
    // For collision detection
    bool m_CanMove;
	
	//De/Constructors
	Player(int x, int y);
    // TODO: move into .cpp
	~Player()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                delete sprites[i][j];
            }
        }
    }
	
	void move(int direction);
	void stop_moving(void);
    void SetCanMove(bool canMove);
	void update(int delta);
    void render();
    void DoMove();

protected:
	void IncCycle(void);
    void SnapToGrid(void);

private:
	int direction; //The direction being faced by the player
	bool moving;
	SDL_Rect* sprites[ 4 ][ 3 ]; //The 12 sprite locations in the sprite sheet

	void set_skin() { skin = (moving) ? sprites[direction][cycle/WALK_SPEED] : sprites[direction][STILL]; };
};

#endif
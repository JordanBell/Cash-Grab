#ifndef player_h
#define player_h
#include "Collidable.h"
#include <math.h>

#define MAX_SPEED 0.50 // The max movement speed cap
#define MIN_SPEED 0.10 // The minimum (base) movement speed
#define DECAY_FACTOR 0.020 // Linearly controls the severity of player movement decay at higher speeds
#define DECAY_MINIMUM 0.0002 // A base speed decay, that persists even at smaller speeds
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
	void IncSpeed(const float amount);

protected:
	void IncCycle(void);
    void SnapToGrid(void);

private:
	bool m_evasion1;
	bool m_evasion2;
	float m_speed;
	int direction; //The direction being faced by the player
	int smashCount;
	bool moving;
	SDL_Rect* sprites[ 4 ][ 4 ]; //The 16 sprite locations in the sprite sheet

	void set_skin(void) { skin = (moving) ? sprites[direction][cycle/WALK_SPEED] : sprites[direction][STILL]; };
	void SmashUpdate(void);
	void AddDirtParticles(void);
	const float ComputeDecay(void);
	const float ComputeSpeedPercentage(void) { return m_speed/MAX_SPEED; }
	void DecaySpeed(void) { IncSpeed(-ComputeDecay()); }
};

extern Player *g_player;

#endif
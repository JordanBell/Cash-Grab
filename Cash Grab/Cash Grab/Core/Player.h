#ifndef player_h
#define player_h
#include "Collidable.h"
#include <math.h>
#include <string>
#include "SpeechBubble.h"
#include "Prompt.h"

#define MAX_SPEED 0.50f // The max movement speed cap
#define MIN_SPEED 0.1f // The minimum (base) movement speed
#define DECAY_FACTOR 0.020 // Linearly controls the severity of player movement decay at higher speeds
#define DECAY_MINIMUM 0.0002 // A base speed decay, that persists even at smaller speeds
#define WALK_SPEED 8 // The number of frames between cycle changes
#define WALK_CYCLE_LENGTH 4
#define STILL 1
#define SMASH_LIMIT 500
#define SMASH_INTERVAL 50

using namespace std;

class InteractZone;

class Player : public Collidable, public Sprite {
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

	void Interact(void);
	void move(int direction);
	void stop_moving(void);
    void SetCanMove(bool canMove);
    void DoMove(void);
	void Smash(int radius);
	void SmashWave() { smashCount = 0; }
	void IncSpeed(const float amount);

	void SetSpeed(const float newSpeed);

	void Update(int delta) override final;
	void Render(void) override final;

	// Create a speech bubble above the player saying the given string phrase. No timeout.
	//void SayIndef(const string phrase);
	// Create a speech bubble above the player saying the given string phrase. Optionally sets the timeout proportionally to the length of the message.
	void Say(const string phrase, bool useProportionalTimeout = false);

protected:
    void SnapToGrid(void);
	void UpdateImageRect(void) override { m_imageRect = (moving) ? sprites[direction][m_cycle/WALK_SPEED] : sprites[direction][STILL]; };

private:
	SpeechBubble* m_Speech;
	InteractZone* m_Interaction;
	float m_Friction;
	bool m_evasion1;
	bool m_evasion2;
	float m_speed;
	int direction; //The direction being faced by the player
	int smashCount;
	bool moving;
	SDL_Rect* sprites[ 4 ][ 4 ]; //The 16 sprite locations in the sprite sheet
	XY m_TargetVelocities; // Pushing force in a given frame, for movement
	Prompt* m_Prompt;
	int m_DamageImmunityCounter;

	void InitSprites(void) override;
	void ReplaceSpeech(SpeechBubble* sPtr);
	void SmashUpdate(void);
	void UpdateDamageDetection(void);
	void AddDirtParticles(void);
	void ApproachTargetVelocity(void);
	const float ComputeDecay(void);
	const float ComputeSpeedPercentage(void) { return m_speed/MAX_SPEED; }
	void DecaySpeed(void) { IncSpeed(-ComputeDecay()); }
	void SetImmunityCounter(const int newCount);

	// Respond to taking damage
	void OnDamage(const float damagePercentage);
};

extern Player *g_player;

#endif
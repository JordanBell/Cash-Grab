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
	// Construct the player
	Player(int x, int y);

	// Destroy the player
	~Player(void);
    
    // For collision detection
    bool m_CanMove;
    
    // For debugging
    bool m_Debug;
	
	// Directions of player movement. 
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NULLDIR
	};

	// Update the player
	void Update(int delta) override final;

	// Render the player
	void Render(void) override final;

	// If interactZone is non-null, activate it. Otherwise, do nothing. If something goes wrong and the function returns a string, have the palyer Say that string.
	void Interact(void);

	// Create a speech bubble above the player saying the given string phrase. Optionally sets the timeout proportionally to the length of the message.
	void Say(const string phrase, bool useProportionalTimeout = false);

	// Activate the smash effect
	void Smash(int radius) const;

	// Set a new direction if possible.
	void SetDirection(int direction);

	// Alter the x and y position based on the m_Velocities
    void DoMove(void);

	// Stop the player from moving, letting him slide to a stop.
	void StopMoving(void);

	// Set whether or not the player can move. If not, set m_Move to false
    void SetCanMove(bool canMove);

	// Increase the speed by a certain amount
	void IncreaseSpeed(const float amount);
	
	// Toggle the debug variable, which reveals the player's hitboxes when rendering.
    inline void ToggleDebug(void) { m_Debug = !m_Debug; }

	// Used in debug, calls OnDamage for 100% coin loss.
	void OnDamage_Debug()
		{ OnDamage(1); }

protected:
	// Update the image rect from the 4x4 sprite array based on the player's direction and walk cycle.
	inline void UpdateImageRect(void) override final;

private:
	// The speech bubble object that holds a phrase that the player is saying. Is always non-null, but remains invisible when inactive.
	SpeechBubble* m_Speech;

	// A pointer to the interact zone that this is currently. If null, does nothing on Interact(). Otherwise, calls the function of the interact zone.
	InteractZone* m_Interaction;

	//The 16 sprite locations in the sprite sheet
	SDL_Rect* sprites[ 4 ][ 4 ]; 

	// The velocity which is approached by m_Velocities each frame. Is either 0 or +-m_Speed at any given time.
	XY m_TargetVelocities;

	// The Prompt GameObject that floats above the player's head when they can interact with something.
	Prompt* m_Prompt;

	// The friction of the current room, which affects the acceleration and decelertion of movement
	float m_Friction;

	// The general speed of the player. The exact value that alters the position is held in m_Velocities; this is the speed limit of the acceleration.
	float m_speed;

	//The direction being faced by the player
	int m_Direction; 

	// A counter that counts down the time until the player is no longer immune to damage. If 0, player is vulnerable.
	int m_DamageImmunityCounter;

	// Whether or not the player is currently moving
	bool m_Moving;

	// (deprecated) Boolean used for the evasion effect
	bool m_evasion1, m_evasion2;

	// Initialise the array of player sprites
	inline void InitSprites(void) override final;

	// Damage Detection done during the update. Calls OnDamage if damage was detected.
	inline void UpdateDamageDetection(void);

	// Respond to taking damage
	void OnDamage(const float damagePercentage);

	// Get a random point around the player, given the value of the defined radius. Used when throwing coins around the player after damage.
	const Position ComputeRandPosAroundPlayer(void) const;

	// Add dirt particles based on the currently travelled speed
	void AddDirtParticles(void) const;

	// Set immunity for a certain number of frames
	inline void SetImmunityCounter(const int newCount);

	// Set a player's speed, velocities and targetVelocities to a new value. Overrides all acceleration mechanics.
	inline void SetSpeed(const float newSpeed);

	// Change the actual velocity to accelerate toward the target velocity
	void ApproachTargetVelocity(void);

	// Compute the amount of decay for the max_speed
	inline const float ComputeDecay(void) const;

	// Compute the percentage that the current speed limit has approached the defined max speed
	inline const float ComputeSpeedPercentage(void) const { return m_speed/MAX_SPEED; }

	// Decrease the current speed by the decay computed by ComputeDecay
	inline void DecaySpeed(void) { IncreaseSpeed(-ComputeDecay()); }
};

extern Player *g_player;

#endif
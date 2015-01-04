#pragma once
#include "sprite.h"
#include "Collidable.h"
#include <list>

// TODO: Make this a collidable that has a simple onCollision effect that only follows through if this is erupting
class FirePit :
	public Sprite
{
public:
	FirePit(const int x, const int y);
	~FirePit(void);

	// Update differently depending on the state (see UpdateIdle, UpdateCharging and UpdateEruption accordingly)
	void Update(int delta) override final;

	// Return whether or not the state is ERUPTING
	const bool IsErupting(void);

	// Check if a rect overlaps with this one
	const bool OverlapsWith(const SDL_Rect* rect);

	const float GetDamagePercentage(void) { return m_DamagePercentage; }

protected:
	// Initial fire pit sprites
	void InitSprites(void) override final;

	// Increment the animation cycle, only if charging.
	void IncCycle(void) override final;

	// Update rect based on the cycle
	void UpdateImageRect(void) override final { m_imageRect = m_Sprites[m_cycle]; }

private:
	enum State {
		IDLE, CHARGING, ERUPTING
	} m_State;

	int m_ChargeCounter;
	int m_EruptCounter;

	SDL_Rect* m_Sprites[ 8 ];

	// The area of effect while erupting. Used in collision.
	SDL_Rect* m_Area;

	// The percentage of coins that the player loses when hit by a fire pit
	float m_DamagePercentage;

	void SetState(State s) { m_State = s; }

	// Update, when Idle
	void UpdateIdle(void);

	// Update, when Charging
	void UpdateCharging(void);

	// Update, when Erupting
	void UpdateErupting(void);

	// Create particles, when charging
	void EmitCharge(void);

	// Create particles, when erupting
	void EmitEruption(void);

	// The chance, per frame, of an eruption triggering
	float m_EruptChance;
};

extern std::list<FirePit*> g_firePits;
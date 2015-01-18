#pragma once
#include "sprite.h"
#include "hazard.h"
#include "Game.h"
#include "Collidable.h"
#include <list>

class FirePit :
	public Sprite, public Hazard
{
public:
	FirePit(const int x, const int y);

	// Update differently depending on the state (see UpdateIdle, UpdateCharging and UpdateEruption accordingly)
	void Update(int delta) override final;

	// Return whether or not the state is ERUPTING
	const bool IsErupting(void);

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

	// A counter for when how long the firepit should charge for
	int m_ChargeCounter;

	// A counter for when an eruption should end
	int m_EruptCounter;

	// Chance of eruption per frame
	static const float k_EruptChance;
	
	// Number of frames spent erupting
	static const unsigned int k_TimeErupt = 200;

	// Number of frames spent charging
	static const unsigned int k_TimeCharge = 300;


	// The size of the fiery eruption particles
	static const Dimensions k_ParticleSize_Eruption;

	// The size of the charge emission particles
	static const Dimensions k_ParticleSize_Charge;

	// The number of particles per frame emitted in the charging effect.
	static const unsigned int k_ParticleNum_Charge = 1;

	// The number of particles per frame emitted in the eruption effect. Changes the density of the flame column's look.
	static const unsigned int k_ParticleNum_Eruption = 6;

	// The higher the fraction (up to 1.0) the lower the lava from the edge in the radius of eruption
	static const float k_TipCurve;

	// The height of the highest point in the eruption
	static const unsigned int k_TipHeight = 13;

	// The radius of the eruption
	static const unsigned int k_EruptionRadius = TILE_SIZE;

	// The radius of the bubbling charge emission
	static const unsigned int k_EmitRadius = TILE_SIZE*3/4;

	SDL_Rect* m_Sprites[ 8 ];

	// Set a new state, and activate/deactivate this hazard accordingly.
	void SetState(State s);

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
};

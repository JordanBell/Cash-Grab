//
//  Effect.h
//  CashGrab
//
//  Base class for effects, such as coin magnetism, icy floor, etc.
//  Contains member functions which are called by EffectManager to
//  implement the effects of powerups.
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __CashGrab__Effect__
#define __CashGrab__Effect__

#include "Sprite.h"

#define MAGNETISM_DISTANCE_DEFAULT 25
#define MAGNETISM_DISTANCE_SHORT 50
#define MAGNETISM_DISTANCE_LONG 100
#define MAGNETISM_SPEED_DEFAULT 5
#define MAGNETISM_SPEED_LONG 1

class Effect {
protected:
    /* Powerup that owns this effect */
    GameObject* m_Parent;
    
    /* Duration of this effect, in ms */
    int m_Duration;
    /* Time elapsed while running: to know when to stop effect */
    int m_ElapsedTime;

	
	/* Static, Passive Effect Booleans */
	// Positive Effects
	// Pull
	// Smash
	static bool s_magnetismLong;
	static bool s_magnetismShort;
	static bool s_frameRateIncrease;

	// Negative Effects
	static bool s_icyFloor;
	static bool s_reversedDirections;
	static bool s_evasive1;
	static bool s_evasive2;
	static bool s_bouncyCoins;

	// Neutral Effects
	static bool s_musicChange;
	static bool s_coinSFXChange;
	static bool s_coinColorsChange;

	/*

	Note: These can be publicly read, but only overwritten in subclass implmentations

	*/
public:
    bool m_IsDone;
    
	Effect(GameObject* parent) : m_Parent(parent), m_Duration(0), m_ElapsedTime(0), m_IsDone(false)  {}
    virtual ~Effect() { }
    
    /**
     * Called when an effect is created. Should perform
     * initialisation, and should be used for one-off
     * effects such as toggling magnetism.
     */
    virtual void OnStart() = 0;
    
    /**
     * Used for continuous effects. Called every update
     * of the game loop.
     */
    virtual void OnUpdate(int delta)
    {
        m_ElapsedTime += delta;
        
        if (m_Duration != -1 && m_ElapsedTime >= m_Duration) {
            m_ElapsedTime = 0;
            m_IsDone = true;
        }
    }
    
    /**
     * Called when an effect is finished. Should perform
     * any required cleanup at the end of a continuous
     * effect.
     */
    virtual void OnEnd() = 0;
    
	// Get Positive Effect Bool
	static bool GetMagnetismLong(void) { return s_magnetismLong; }
	static bool GetMagnetismShort(void) { return s_magnetismShort; }
	static bool GetFrameRateIncrease(void) { return s_frameRateIncrease; }

	// Get Negative Effects Bool
	static bool GetIcyFloor(void) { return s_icyFloor; }
	static bool GetReversedDirections(void) { return s_reversedDirections; }
	static bool GetEvasive1(void) { return s_evasive1; }
	static bool GetEvasive2(void) { return s_evasive2; }
	static bool GetBouncyCoins(void) { return s_bouncyCoins; }

	// Get Neutral Effects Bool
	static bool GetMusicChange(void) { return s_musicChange; }
	static bool GetCoinSFXChange(void) { return s_coinSFXChange; }
	static bool GetCoinColorsChange(void) { return s_coinColorsChange; }
};

#endif /* defined(__CashGrab__Effect__) */

// Could this next block be moved to their corresponding Effect classes?
//	if (m_evasion1)
//	{
//		// Evasion Effect 1 -- Bounce around the player
//		list<Coin*> closeCoins = Coin::CoinsAroundPlayer(MAGNETISM_DISTANCE);
//
//		for (Coin* c : closeCoins)
//			c->LaunchTo(x + (rand()%50 - 25), y + (rand()%50 - 25), 0);
//	}
//	else if (m_evasion2)
//	{
//		// Evasion Effect 2 -- Bounce around the map
//		list<Coin*> closeCoins = Coin::CoinsAroundPlayer(MAGNETISM_DISTANCE);
//
//		for (Coin* c : closeCoins) 
//		{
//			int coinX = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
//			int coinY = rand() % (screen->h - 7*TILE_SIZE) + 4*TILE_SIZE;
//			c->LaunchTo(coinX, coinY, 2);
//		}
//	}

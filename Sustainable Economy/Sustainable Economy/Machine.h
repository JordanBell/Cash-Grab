#ifndef machine_h
#define machine_h

#include "Collidable.h"
#include "CoinSilver.h"
#include "CoinGold.h"
#include "Game.h"

#include <vector>
#include <iostream>

using namespace std;

#define NUM_SLOTS 6
#define COIN_INCREASE 1.2
#define DISPENSING_STUTTER 35
#define BURST_DELAY 5
#define QUANTITY_THRESHOLD 20

class Machine :
	public Collidable
{
public:
	int coinCost;

	Machine(int x, int y);
	~Machine(void) {}
	
	void update(int delta);
	void dispense();

	SDL_Rect CoinLaunchInfo(int slotNum);

private:    
	struct XY { float x, y; };
	
	enum DispenseType {
		NORM, POINT, CORNERS, LINES_H, LINES_V, LEFT, RIGHT, BOTH
	};
	enum DispensePattern{
		BURST, SERPENTINE, SPUTTER, DUMP
	};
	DispenseType m_dispenseType;
	DispensePattern m_dispensePattern;

    pair<int, int> dispenser_pos;
    pair<int, int> coin_slots[NUM_SLOTS];
	bool m_dispensing;
	int m_numDispensed;
	int m_timeElapsed;
	int m_ticker;
    vector<Coin*> coins;
	
	XY getLeftCircleCoords(bool addRightCoords = false);
	XY getRightCircleCoords() { return getLeftCircleCoords(true); }
	
	DispenseType RandomDispenseType(void);
	DispensePattern RandomDispensePattern(void);
	bool ValidLandingPosition(int _x, int _y);
	void ShootCoinFrom(int slotNum) { ShootCoinsFrom(slotNum, 1, false); }
	void ShootCoinsFrom(int slotNum, int totalValue) { ShootCoinsFrom(slotNum, totalValue, true); }
	void ShootCoinsFrom(int slotNum, int totalValue, bool intervalCoins);
	void FinishDispensing();
	bool canAfford();
};

#endif
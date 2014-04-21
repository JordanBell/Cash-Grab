#ifndef machine_h
#define machine_h

#include "entity.h"
#include "Coin.h"
#include "Game.h"

#include <vector>
#include <iostream>

using namespace std;

#define NUM_SLOTS 6
#define COIN_INCREASE 1.2
#define DISPENSING_STUTTER 35
#define QUANTITY_THRESHOLD 50

class Machine :
	public Entity
{
public:
	int coinCost;

	Machine(int x, int y);
	~Machine(void) {}
	
	void update(int delta);
	void dispense();

private:    
	struct XY { float x, y; };

	enum DispenseType {
		NORM, POINT, CORNERS, LINES_H, LINES_V, LEFT, RIGHT, BOTH
	};
	DispenseType m_dispenseType;

    pair<int, int> dispenser_pos;
    pair<int, int> coin_slots[NUM_SLOTS];
	bool m_dispensing;
	int m_numDispensed;
	int m_timeElapsed;
    vector<Coin*> coins;
	
	XY getLeftCircleCoords(bool addRightCoords = false);
	XY getRightCircleCoords() { return getLeftCircleCoords(true); }

	DispenseType RandomDispenseType(void);
	bool ValidLandingPosition(int _x, int _y);
	void ShootCoinFrom(int slotNum);
	void FinishDispensing();
	bool canAfford();
};

#endif
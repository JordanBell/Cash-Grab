#ifndef machine_h
#define machine_h

#include "Collidable.h"
#include "CoinBronze.h"
#include "CoinSilver.h"
#include "CoinGold.h"
#include "Game.h"
#include "LaunchData.h"

#include <vector>
#include <iostream>

using namespace std;

#define NUM_SLOTS 6
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

	void ForceDispense(int coinNum);

	SDL_Rect CoinLaunchInfo(int slotNum);

private:    
	struct XY { float x, y; };
	
	LaunchData::CoinType m_coinType;
	LaunchData::DispenseStyle m_dispenseStyle;
	LaunchData::DispensePattern m_dispensePattern;

    pair<int, int> dispenser_pos;
    pair<int, int> coin_slots[NUM_SLOTS];
	bool m_dispensing;
	int m_numDispensed;
	int m_timeElapsed;
	int m_ticker;
    vector<Coin*> coins;
	
	XY GetLeftCircleCoords(bool addRightCoords = false);
	XY GetRightCircleCoords() { return GetLeftCircleCoords(true); }

	void ShootCoinFrom(int slotNum) { ShootCoinsFrom(slotNum, 1, false); }
	void ShootCoinsFrom(int slotNum, int totalValue) { ShootCoinsFrom(slotNum, totalValue, true); }
	void ShootCoinsFrom(int slotNum, int totalValue, bool intervalCoins);
	void FinishDispensing();

	// Launch a particular type of coin
	template <class Coin_Type>
	void LaunchCoin(int count, int slotNum);
	
	bool ValidLandingPosition(int _x, int _y);
	bool canAfford();
};

extern Machine* g_machine;

#endif
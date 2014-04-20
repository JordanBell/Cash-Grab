#ifndef machine_h
#define machine_h

#include "entity.h"
#include "Coin.h"

#include <vector>
#include <iostream>

using namespace std;

#define NUM_SLOTS 6
#define COIN_INCREASE 0.2

class Machine :
	public Entity
{
public:
	Machine(int x, int y);
	~Machine(void) {}
	
	void update(int delta);
	void dispense();

private:
	void set_skin();
	int coinCost;
    
    pair<int, int> dispenser_pos;
    pair<int, int> coin_slots[NUM_SLOTS];
	bool m_dispensing;
	int m_numDispensed;
    vector<Coin*> coins;

	bool ValidLandingPosition(int _x, int _y);
	void ShootCoinFrom(int slotNum);
	void FinishDispensing();
	bool canAfford() { return (g_game->wallet >= coinCost); }
};

#endif
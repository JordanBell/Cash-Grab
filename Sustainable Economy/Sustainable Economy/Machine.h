#ifndef machine_h
#define machine_h

#include "entity.h"
#include "Coin.h"

#include <vector>
#include <iostream>

using namespace std;

#define NUM_SLOTS 6

class Machine :
	public Entity
{
public:
	Machine(int x, int y);
	~Machine(void);
	
	void update(int delta);
	void dispense();

private:
	void set_skin();
    
    pair<int, int> dispenser_pos;
    pair<int, int> coin_slots[NUM_SLOTS];
    vector<Coin*> coins;

	bool ValidLandingPosition(int _x, int _y);
};

#endif
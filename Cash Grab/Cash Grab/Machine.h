#ifndef machine_h
#define machine_h

#include "Dispenser.h"
#include "Collidable.h"
#include "Game.h"
#include "LevelProgress.h"
#include "TruthSwitch.h"
#include "XY.h"

#include <vector>
#include <iostream>

using namespace std;

#define NUM_SLOTS 6

class Machine :
	public Collidable, public Dispenser
{
public:
	Machine(const int x, const int y);

protected:
	// Return a position to be launched to.
	const Position GetLaunchTo(void) const override final;

	void OnDump(DispenseList& dispenseList) override final;
	void OnBurst(DispenseList& dispenseList) override final;
	void OnSputter(DispenseList& dispenseList) override final;
	void OnSerpentine(DispenseList& dispenseList) override final;

private:    
	TruthSwitch m_LaunchKey;
	bool m_KeyLaunched;

    Position CoinSlots[NUM_SLOTS];
	
	const XY GetLeftCircleCoords(const bool addRightCoords = false) const;
	const XY GetRightCircleCoords(void) const { return GetLeftCircleCoords(true); }
};

#endif
#pragma once
#include "Dispenser.h"
#include "XY.h"

class Sinkhole_Top :
	public Dispenser
{
	// The rect within which this will dispense its contents
	const SDL_Rect* m_TargetBounds;

public:
	Sinkhole_Top(const SDL_Rect* targetBounds);
	~Sinkhole_Top(void) { delete m_TargetBounds; }

protected:
	// Return a position to be launched to.
	const Position GetLaunchTo(void) override final;

	void OnDump(DispenseList& dispenseList) override final;
	void OnBurst(DispenseList& dispenseList) override final;
	void OnSputter(DispenseList& dispenseList) override final;
	void OnSerpentine(DispenseList& dispenseList) override final;

private:
	// Whether or not a position intersects with the sinkhole's area
	const bool InSinkhole(const Position& pos);

	const Position GetLeftPitCoords(void) const;
	const Position GetRightPitCoords(void) const;
};

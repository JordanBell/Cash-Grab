#pragma once
#include "Dispenser.h"
#include "XY.h"

class RoomFire_Lower;

class Sinkhole_Top :
	public Dispenser
{
	// The rect within which this will dispense its contents
	const SDL_Rect* m_TargetBounds;

public:
	Sinkhole_Top(const SDL_Rect* targetBounds, RoomFire_Lower* roomPointer);
	~Sinkhole_Top(void) { delete m_TargetBounds; }

protected:
	// Return a position to be launched to.
	const Position GetLaunchTo(void) const override final;

	void OnDump(DispenseList& dispenseList) override final;
	void OnBurst(DispenseList& dispenseList) override final;
	void OnSputter(DispenseList& dispenseList) override final;
	void OnSerpentine(DispenseList& dispenseList) override final;

private:
	// Points to the parent fire room, from which information about the fire pit positions can be taken.
	RoomFire_Lower* m_RoomPointer;

	// Whether or not a position intersects with the sinkhole's area
	const bool InSinkhole(const Position& pos) const;
};

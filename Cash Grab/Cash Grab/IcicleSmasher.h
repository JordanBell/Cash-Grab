#pragma once
#include "dispenser.h"

class IcicleSmasher :
	public Dispenser
{
public:
	IcicleSmasher(void);
	~IcicleSmasher(void) {}

	void Update(int delta) override final { if (m_HammerTicker > 0) m_HammerTicker--; Dispenser::Update(delta); }
	void Render(void) override final;

protected:
	// Return a position to be launched to.
	const Position GetLaunchTo(void) const override final;

	void OnDump(DispenseList& dispenseList) override final;
	void OnBurst(DispenseList& dispenseList) override final;
	void OnSputter(DispenseList& dispenseList) override final;
	void OnSerpentine(DispenseList& dispenseList) override final;

	void OnDispense(void);

private:
	int m_RemainingIcicles;
	int m_ThrowablesPerIcicle;
	int m_HammerTicker; // The number of frames the hammer spends down

	static const unsigned int k_HammerTimeSpentDown = 15;
	static const unsigned int k_MaxIciclesPerDispense = 12;

	// Get a position in the blast radius for a throwable to go, in a serpentine pattern
	const Position GetSerpentineLaunchTo(void);
	
	// Drop a number of icicle, keeping to the limits of m_RemainingIcicles
	void DropIcicles(DispenseList& dispenseList, const int maxNumIcicles, const bool isSerpentine = false);

	// Determine the number of throwables to be added to the icicle.
	DispenseList* IcicleSmasher::ComputeIcicleDispenseList(DispenseList& dispenseList);

};


#pragma once
#include "dispenser.h"
class IcicleSmasher :
	public Dispenser
{
public:
	IcicleSmasher(void);
	~IcicleSmasher(void) {}

	void Update(int delta) { Dispenser::Update(delta); }

protected:
	// Return a position to be launched to.
	const Position GetLaunchTo(void) override final;

	void OnDump(DispenseList& dispenseList) override final;
	void OnBurst(DispenseList& dispenseList) override final;
	void OnSputter(DispenseList& dispenseList) override final;
	void OnSerpentine(DispenseList& dispenseList) override final;

	void OnDispense(void);

private:
	int m_RemainingIcicles;
	int m_ThrowablesPerIcicle;
	
	// Drop a number of icicle, keeping to the limits of m_RemainingIcicles
	void DropIcicles(DispenseList& dispenseList, const int maxNumIcicles);

	// Determine the number of throwables to be added to the icicle.
	DispenseList* IcicleSmasher::GetIcicleDispenseList(DispenseList& dispenseList);

};


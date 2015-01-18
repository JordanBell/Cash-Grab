#pragma once
#include "GameObject.h"
#include "LevelProgress.h"
#include <list>

#include "CoinBronze.h"
#include "CoinSilver.h"
#include "CoinGold.h"
#include "PowerupMagnetism.h"
#include "PowerupPull.h"
#include "PowerupSmash.h"
#include "ThrowableQuantity.h"

class Dispenser :
	public GameObject
{
public:
	virtual ~Dispenser(void);

	// Update, dispensing over time if set to do so.
	void Update(int delta) override;

	// Try to dispense. Only does so if player can afford it. Throws a string for the character to say if something goes wrong.
	void Dispense(void);

	// Forcibly dispense coins from the dispenser. Used in testing.
	void ForceDispense(const int num);

	/* Determine a DispenseList of coins based on this dispenser's level 
	progress and total coin value. This is public so that something 
	can get a DispenseList using the dispenser's launch information. */
	DispenseList DetermineCoinList(const int totalValue) const;

	// Get the number of coins required in order to dispense
	int GetCost(void) { return m_CurrentCost; }

	// Get data about the progress made with this dispenser
	LevelProgress* GetProgress(void) { return m_Progress; }

protected:
	// Default burst delay for the burst dispense style. Controls the number of frames between OnBurst calls.
	static const unsigned int k_DefaultBurstDelay = 25;

	// Default fire rate for the sputter and serpentine dispense styles. Controls the number of frames between OnSputter and OnSerpentine calls.
	static const unsigned int k_DefaultFireRate = 5;

	// The suppression on the angle of launch when dispensing.
	static const unsigned int k_AngleSuppression = 1;

	// The number of coins per shot at which multiple coins are shot from the same point (to save time at higher numbers)
	static const unsigned int k_MultishotQuantityThreshold = 20;

	// Implement as a dispenser, giving an x and y position for the GameObject component, and a dispenser element to determine coin element.
	Dispenser(const int x, const int y, const int ele);

	// Return a position to be launched do. (Each subclass handles this different based on the DispensePatterns)
	virtual const Position GetLaunchTo(void) const = 0;

	virtual void OnDump(DispenseList& dispenseList) = 0;
	virtual void OnBurst(DispenseList& dispenseList) = 0;
	virtual void OnSputter(DispenseList& dispenseList) = 0;
	virtual void OnSerpentine(DispenseList& dispenseList) = 0;

	// Extra virtual behaviour on dispense
	virtual void OnDispense(void) {}

	// The dispense list holds types and quantities. Return the total quantity.
	const int ComputeListTotal(void) const;

	void SetBurstDelay(const int newDelay) { m_BurstDelay = newDelay; }
	void SetFireRate(const int newRate) { m_FireRate = newRate; }
	const int GetFireRate(void) { return m_FireRate; }

	// The current coin cost to dispense TODO: Move this to LevelProgress
	int m_CurrentCost;

	// A counter for use with the some dispense styles
	int m_SingleShotTicker;

	// A counter for use with the burst dispense style
	int m_BurstTicker;

	// Amount per burst
	int m_BurstAmount;

	// The progress that the player has made with this dispenser
	LevelProgress* m_Progress;

	// The last saved launch data
	DataPacket* m_LaunchData;

	// The element of the dispenser, determining the element of the coins and cash dispensed.
	int m_CoinElement;

private:
	// A list of things to dispense, and how many of each.
	DispenseList m_DispenseList;

	// Whether or not the dispenser is currently dispensing.
	bool m_Dispensing;

	// Time between bursts when in burst mode
	int m_BurstDelay;

	// Time between single shots sputter or serpentine modes
	int m_FireRate;

	// The chance of a powerup appearing per dispense
	static const float k_PowerupChance;

	// Number of bursts in burst mode
	static const unsigned int k_NumBursts = 5;

	// Delegate to the virtual functions On___() depending on the DispenseStyle
	virtual void HandleDispenseList(DispenseList& dispenseList);

	void AddPowerupsToList(void);

	// Determine and set the list of throwables to be dispensed
	void DetermineList(void);

	// Return whether or not the wallet contains the right amount of money to dispense.
	const bool CanAfford(void) const;

	// Finish dispensing. Reset relevant values.
	void OnFinish(void);
};


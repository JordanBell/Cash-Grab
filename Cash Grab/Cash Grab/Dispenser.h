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

typedef list<pair<string, int>> DispenseList;

#define ANGLE_SUPPRESSION 1
#define DEFAULT_BURST_DELAY 5
#define DEFAULT_FIRE_RATE 1
#define QUANTITY_THRESHOLD 20

/* This small chunk of code has been defined, as a lot of dispensers 
use this repeated bit. It will be altered throughout development, so 
it's usefull to have all in one place. */
#define DISPENSE_BY_TYPE \
		if (type == "bronzecoin")\
			LaunchThrowable<CoinBronze>(launchPos, launchAmount);\
		if (type == "silvercoin")\
			LaunchThrowable<CoinSilver>(launchPos, launchAmount);\
		if (type == "goldcoin")\
			LaunchThrowable<CoinGold>(launchPos, launchAmount);\
		if (type == "powerupsmash")\
			LaunchThrowable<PowerupSmash>(launchPos, launchAmount);\
		if (type == "poweruppull")\
			LaunchThrowable<PowerupPull>(launchPos, launchAmount);\
		if (type == "powerupmagnetism")\
			LaunchThrowable<PowerupMagnetism>(launchPos, launchAmount);

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

	// Determine a DispenseList of coins based on this dispenser's level progress but with a different total value
	DispenseList DetermineCoinList(const int totalValue) const;

	// Get the number of coins required in order to dispense
	int GetCost(void) { return m_CurrentCost; }

	// Get data about the progress made with this dispenser
	LevelProgress* GetProgress(void) { return m_Progress; }

protected:
	Dispenser(const int x, const int y, const int ele);

	// Return a position to be launched do. (Each subclass handles this different based on the DispensePatterns)
	virtual const Position GetLaunchTo(void) = 0;

	virtual void OnDump(DispenseList& dispenseList) = 0;
	virtual void OnBurst(DispenseList& dispenseList) = 0;
	virtual void OnSputter(DispenseList& dispenseList) = 0;
	virtual void OnSerpentine(DispenseList& dispenseList) = 0;

	virtual void OnDispense(void) {}

	// Launch a particular type of throwable
	template <class Throw_Type>
	void LaunchThrowable(const Position start, const int count)
	{
		for (int i = 0; i < count; i++)
		{
			// Find this throwable's target position
			Position to = GetLaunchTo();

			// Create a new throwable for that destination
			Throw_Type* throwable = new Throw_Type(start.x, start.y, to.x, to.y, m_CoinElement);
			throwable->Launch(ANGLE_SUPPRESSION);

			// Add it to the collidables list
			g_game->addCollidable(throwable);
		}
	}

	int GetListTotal(void) const;

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

	// The counter between the last dispense - makes sure it doesn't call OnDispense for every frame.
	int m_TimeElapsed;

	// Time between bursts when in burst mode
	int m_BurstDelay;

	// Time between single shots sputter or serpentine modes
	int m_FireRate;

	// Delegate to the virtual functions On___() depending on the DispenseStyle
	virtual void HandleDispenseList(DispenseList& dispenseList);

	void AddPowerupsToList(void);

	// Determine and set the list of throwables to be dispensed
	void DetermineList(void);

	// Return the total amount in the currently held DispenseList
	inline const int ComputeListTotal(void);

	// Return whether or not the wallet contains the right amount of money to dispense.
	const bool CanAfford(void) const;

	// Finish dispensing. Reset relevant values.
	void OnFinish(void);
};


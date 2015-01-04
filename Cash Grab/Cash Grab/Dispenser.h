#pragma once
#include "GameObject.h"
#include "LevelProgress.h"
#include <list>

typedef list<pair<string, int>> DispenseList;

#define ANGLE_SUPPRESSION 1
#define BURST_DELAY 5
#define QUANTITY_THRESHOLD 20

class Dispenser :
	public GameObject
{
public:
	virtual ~Dispenser(void);

	// Update, dispensing over time if set to do so.
	void Update(int delta) override;

	// Try to dispense. Only does so if player can afford it.
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

	// Launch a particular type of throwable
	template <class Throw_Type>
	void LaunchThrowable(const Position start, const int count)
	{
		for (int i = 0; i < count; i++)
		{
			// Find this Coin's launch info
			Position to = GetLaunchTo();

			// Create a new coin for that destination
			Throw_Type* coin = new Throw_Type(start.x, start.y, to.x, to.y, m_CoinElement);
			coin->Launch(ANGLE_SUPPRESSION);

			// Add it to the collidables list
			g_game->addCollidable(coin);
		}
	}

	// The current coin cost to dispense TODO: Move this to LevelProgress
	int m_CurrentCost;

	// A counter for use with the serpentine dispense style
	int m_SerpentineTicker;

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

	// Delegate to the virtual functions On___() depending on the DispenseStyle
	virtual void HandleDispenseList(DispenseList& dispenseList);

	// Determine and set the list of throwables to be dispensed
	void DetermineList(void);

	// Return the total amount in the currently held DispenseList
	inline const int ComputeListTotal(void);

	// Return whether or not the wallet contains the right amount of money to dispense.
	const bool CanAfford(void) const;

	// Finish dispensing. Reset relevant values.
	void OnFinish(void);
};


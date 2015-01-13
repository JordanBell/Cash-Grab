#include "Dispenser.h"
#include "Inventory.h"
#include <string>

using namespace std;

#define DISPENSING_STUTTER 35
#define BURST_TIMES 5
#define POWERUP_CHANCE 0.16f
#define MULTISHOT_QUANTITY_THRESHOLD 20

Dispenser::Dispenser(const int x, const int y, const int ele)
	: GameObject(x, y), m_Dispensing(false), m_BurstTicker(0), m_BurstAmount(0), m_SingleShotTicker(0), m_CurrentCost(START_MONEY), 
	m_TimeElapsed(0), m_LaunchData(), m_CoinElement(ele), m_BurstDelay(DEFAULT_BURST_DELAY), m_FireRate(DEFAULT_FIRE_RATE)
{
	// Initialise level progress
	m_Progress = new LevelProgress();
	m_Progress->Notify(0);

	m_LaunchData = m_Progress->GetDataPacket();
}

Dispenser::~Dispenser(void)
{
	delete m_Progress;
}

void Dispenser::Update(int delta)
{
	m_TimeElapsed += delta;

    if ((m_Dispensing) && (m_TimeElapsed >= DISPENSING_STUTTER))
	{
		m_TimeElapsed = 0;

		// Have the subclass handle the dispense list
		HandleDispenseList(m_DispenseList);

		// Remove any expended elements (int == 0)
		DispenseList toRemove = DispenseList();

		for (auto e : m_DispenseList)
			if (e.second == 0)
				toRemove.emplace_back(e);

		// Remove them
		for (auto e : toRemove)
			m_DispenseList.remove(e);

		// Stop dispensing if everything has now been dispensed
		if (m_DispenseList.empty()) 
			OnFinish();
	}
}

const int Dispenser::ComputeListTotal(void)
{
	int r_total = 0;

	for (pair<string, int> pr : m_DispenseList)
		r_total += pr.second;

	return r_total;
}

void Dispenser::Dispense(void)
{
	// Only dispense if not currently doing so
	if (!m_Dispensing)
	{
		// Can the player afford it?
		if (CanAfford())
		{
			// Take the player's money
			Inventory::GetCoinWallet(m_CoinElement)->Remove(m_CurrentCost);

			// Increase the cost of the next coin set by the increase constant.
			m_CurrentCost *= COIN_INCREASE; 
			// Note: We do this now, and not after dispensing, so that the number of coins dispensed is enough money for the player to afford the next price
			
			m_Dispensing = true;
			m_LaunchData = m_Progress->GetDataPacket();

			// Calculate and set the list of throwables to dispense next update
			DetermineList();

			// Call any subclass's OnDispense implementation
			OnDispense();
		}
		else 
		{
			// The player is not allowed to dispense. Throw a string for the player to say, notifying the user.
			int r = rand() % 3;
			
			// Get a random error phrase for the player to say
			switch (r)
			{
				case 0: throw string("Need. More. MONEY!");
				case 1: throw string("Insufficient Funds.");
				case 2: throw string("Can't invest yet.");
			}
		}
	}
}

void Dispenser::ForceDispense(int coinNum)
{
	m_Dispensing = true;
	m_CurrentCost = coinNum;
	m_LaunchData = m_Progress->GetDataPacket();
	DetermineList();
	OnDispense();
}

void Dispenser::HandleDispenseList(DispenseList& dispenseList)
{
	DispenseStyle dispenseStyle = m_LaunchData->style;
	
	if (dispenseStyle == DUMP)
	{
		OnDump(dispenseList);
	}
	else if (dispenseStyle == BURST)
	{
		if (m_BurstTicker == 0)
		{
			OnBurst(dispenseList);
		}
			
		m_BurstTicker++;

		if (m_BurstTicker == m_BurstDelay) // Reset at max
			m_BurstTicker = 0;
	}
	else if (dispenseStyle == SERPENTINE) // Serpentine or Sputter. Both work similarly. Differentiate within.
	{
		if ((m_SingleShotTicker % m_FireRate) == 0)
			OnSerpentine(dispenseList);

		m_SingleShotTicker++;
	}
	else if (dispenseStyle == SPUTTER) // Serpentine or Sputter. Both work similarly. Differentiate within.
	{
		if ((m_SingleShotTicker % m_FireRate) == 0)
			OnSputter(dispenseList);

		m_SingleShotTicker++;
	}
	else
		throw runtime_error("Dispense style not recognised.");
}

void Dispenser::DispenseByType(const Position launchPos, const int launchAmount, const string type) const
{
	if (type == "bronzecoin")
		LaunchThrowable<CoinBronze>(launchPos, launchAmount);
	if (type == "silvercoin")
		LaunchThrowable<CoinSilver>(launchPos, launchAmount);
	if (type == "goldcoin")
		LaunchThrowable<CoinGold>(launchPos, launchAmount);
	if (type == "powerupsmash")
		LaunchThrowable<PowerupSmash>(launchPos, launchAmount);
	if (type == "poweruppull")
		LaunchThrowable<PowerupPull>(launchPos, launchAmount);
	if (type == "powerupmagnetism")
		LaunchThrowable<PowerupMagnetism>(launchPos, launchAmount);
}


int Dispenser::GetListTotal(void) const
{
	int total = 0;

	for (auto pair : m_DispenseList)
		total += pair.second;

	return total;
}

DispenseList Dispenser::DetermineCoinList(const int totalValue) const
{
	// Determine the list of throwables to be dispensed
	DispenseList r_DispenseList = DispenseList(); // Return list

	int numBronze, numSilver, numGold; // Number of each kind of coin
	numBronze = numSilver = numGold = 0; // Intialise counts

	CoinType coinType = m_LaunchData->coinType;

	// When evenly divided, across all currently set coin types, this is the value that one of each would equal
	int totalEnumCoinTypeValue;
	if (coinType == LaunchData::BRONZE) totalEnumCoinTypeValue = CoinBronze::value;
	if (coinType == LaunchData::BS)	  totalEnumCoinTypeValue = CoinBronze::value + CoinSilver::value;
	if (coinType == LaunchData::SILVER) totalEnumCoinTypeValue = CoinSilver::value;
	if (coinType == LaunchData::SG)	  totalEnumCoinTypeValue = CoinSilver::value + CoinGold::value;
	if (coinType == LaunchData::GOLD)   totalEnumCoinTypeValue = CoinGold::value;
			
	// Total integer divisions of that value into the total value
	int numSets = totalValue / totalEnumCoinTypeValue;
	int remainder = totalValue % totalEnumCoinTypeValue;

	// Set the number of each type to be shot 
	if (coinType == LaunchData::BRONZE) 
	{
		numBronze = numSets;
	}
	if (coinType == LaunchData::BS)
	{
		numBronze = numSets;
		numSilver = numSets;
	}
	if (coinType == LaunchData::SILVER)
	{
		numSilver = numSets;
	}
	if (coinType == LaunchData::SG)
	{
		numSilver = numSets;
		numGold = numSets;
	}
	if (coinType == LaunchData::GOLD)
	{
		numGold = numSets;
	}

	// Find the remainder value that was not evenly divided into the sets
	if (remainder > 0)
	{
		int& fillerCoinCount = (remainder%10 == 0) ? numGold : (remainder%5 == 0) ? numSilver : numBronze;
		int  fillerCoinValue = (remainder%10 == 0) ? CoinGold::value : (remainder%5 == 0) ? CoinSilver::value : CoinBronze::value;
		fillerCoinCount += remainder / fillerCoinValue;
	}

	if (numBronze)
		r_DispenseList.push_back(pair<string, int>("bronzecoin", numBronze));

	if (numSilver)
		r_DispenseList.push_back(pair<string, int>("silvercoin", numSilver));
	
	if (numGold)
		r_DispenseList.push_back(pair<string, int>("goldcoin", numGold));

	return r_DispenseList;
}

void Dispenser::DetermineList(void)
{
	// Determine the list of throwables to be dispensed
	m_DispenseList.clear();
	m_DispenseList = DetermineCoinList(m_CurrentCost);
	AddPowerupsToList();

	// Should we launch the key?
	//if (!m_KeyLaunched) 
	//{
	//	if (m_CurrentCost >= KEY_LAUNCH_VAL) 
	//	{
	//		Key* key = new Key(x+m_imageSurface->w/2, y+TILE_SIZE*2, screen->w/2-16, screen->h/2-16, DOOR_ID_TOHUB);
	//		key->Launch(1);
	//		g_game->addCollidable(key);
	//		m_KeyLaunched = true;
	//	}
	//}

	//// Launch cash if told to
	//while (m_CashToDispense > 0)
	//{
	//	// OnDispenseCash()

	//	m_cashToDispense--;

	//	// Get a random position in the board
	//	int randX, randY;
	//	randX = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
	//	randY = rand() % (screen->h - 7*TILE_SIZE) + 4*TILE_SIZE; 

	//	Cash* cash = new Cash(x+m_imageSurface->w/2, y+TILE_SIZE*2, randX, randY, CASH_AMOUNT);
	//	cash->Launch(1);
	//	g_game->addCollidable(cash);
	//}

	// Set the burst amount
	m_BurstAmount = ComputeListTotal() / BURST_TIMES;
}

void Dispenser::AddPowerupsToList(void)
{
	bool willDispensePowerup = (rand()%100 < POWERUP_CHANCE*100);

	if (willDispensePowerup)
	{
		int randPowerupIndex = rand() % 3;

		switch (randPowerupIndex)
		{
		case 0: m_DispenseList.push_back(pair<string, int>("powerupmagnetism", 1)); break;
		case 1: m_DispenseList.push_back(pair<string, int>("poweruppull", 1)); break;
		case 2: m_DispenseList.push_back(pair<string, int>("powerupsmash", 1)); break;
		}
	}
}


void Dispenser::OnFinish(void) 
{
	m_Dispensing = false;
}

const bool Dispenser::CanAfford(void) const
{
	return (Inventory::GetCoinWallet(m_CoinElement)->GetAmount() >= m_CurrentCost);
}


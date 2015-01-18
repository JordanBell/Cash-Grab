#include "Dispenser.h"
#include "Inventory.h"
#include <string>

using namespace std;

const float Dispenser::k_PowerupChance = 0.16f;

Dispenser::Dispenser(const int x, const int y, const int ele)
	: GameObject(x, y), m_Dispensing(false), m_BurstTicker(0), m_BurstAmount(0), m_SingleShotTicker(0), m_CurrentCost(Inventory::k_StartMoney), 
	m_LaunchData(), m_CoinElement(ele), m_BurstDelay(k_DefaultBurstDelay), m_FireRate(k_DefaultFireRate)
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
    if (m_Dispensing)
	{
		// Have the subclass handle the dispense list
		HandleDispenseList(m_DispenseList);

		// Remove any expended elements (int == 0)
		DispenseList toRemove = DispenseList();

		for (auto tq : m_DispenseList)
			if (tq->IsEmpty())
				toRemove.emplace_back(tq);

		// Remove them
		for (auto tq : toRemove)
			m_DispenseList.remove(tq);

		// Stop dispensing if everything has now been dispensed
		if (m_DispenseList.empty()) 
			OnFinish();
	}
}

const int Dispenser::ComputeListTotal(void) const
{
	int total = 0;

	for (auto tq : m_DispenseList)
		total += tq->GetQuantity();

	return total;
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
			m_CurrentCost *= Inventory::k_CoinIncrease; 
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
	dispenseStyle = BURST; // Override for testing

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

		if (m_BurstTicker == m_BurstDelay) // Reset when at max
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
		r_DispenseList.push_back( new ThrowableQuantity<CoinBronze>(numBronze, m_CoinElement) );

	if (numSilver)
		r_DispenseList.push_back( new ThrowableQuantity<CoinSilver>(numSilver, m_CoinElement) );

	if (numGold)
		r_DispenseList.push_back( new ThrowableQuantity<CoinGold>(numGold, m_CoinElement) );

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
	m_BurstAmount = ComputeListTotal() / k_NumBursts;
}

void Dispenser::AddPowerupsToList(void)
{
	bool willDispensePowerup = (rand()%100 < k_PowerupChance*100);

	if (willDispensePowerup)
	{
		int randPowerupIndex = rand() % 3;

		switch (randPowerupIndex)
		{
		case 0: 
			m_DispenseList.push_back( new ThrowableQuantity<PowerupMagnetism>(1) );
			break;
		case 1: 
			m_DispenseList.push_back( new ThrowableQuantity<PowerupPull>(1) );
			break;
		case 2: 
			m_DispenseList.push_back( new ThrowableQuantity<PowerupSmash>(1) );
			break;
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


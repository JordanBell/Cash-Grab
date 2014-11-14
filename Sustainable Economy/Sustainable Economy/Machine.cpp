#include "Machine.h"
#include "Resources.h"
#include "Wallet.h"

Machine* g_machine = nullptr;

Machine::Machine(int x, int y) 
	: Collidable(x, y), coins(), m_dispensing(false), m_ticker(0), m_numDispensed(0),
	coinCost(START_MONEY), m_timeElapsed(0), m_coinType(LaunchData::BRONZE), m_dispensePattern(LaunchData::NORM), m_dispenseStyle(LaunchData::SPUTTER)
{
	// Initialise launch data
	LaunchData::Notify(0);

	sprite_sheet = g_resources->GetMoneyMachineSheet();
	skin = nullptr; //Use the entire image
    
    m_IsMoveable = false;
    m_HitBox->w = TILE_SIZE * 6;
    m_HitBox->h = TILE_SIZE * 2;

    dispenser_pos = std::pair<int, int>(x, y + (2 * TILE_SIZE));
    
    for (int i = 0; i < NUM_SLOTS; i++) {
        int slotX = dispenser_pos.first + (i * TILE_SIZE);
        int slotY = dispenser_pos.second;
        
        pair<int, int> slot(slotX, slotY);
        coin_slots[i] = slot;
    }
}

void Machine::update(int delta)
{
	m_timeElapsed += delta;

    if ((m_dispensing) && (m_timeElapsed >= DISPENSING_STUTTER))
	{
		m_timeElapsed = 0;

		if (m_dispenseStyle == LaunchData::BURST)
		{
			if (m_ticker == 0)
			{
				// Shoot a number of coins from that slot, proportional to the total number being shot out. This will reduce times for large amounts of coins to a maximum number of shot
				const int maxCoinsPerSlot = (coinCost / (QUANTITY_THRESHOLD*6/BURST_DELAY)) + 1;
				int yetToBeShot, coinsPerSlot;

				// Dispense a set of coins for each row
				for (int slotNum = 0; (slotNum < 6) && (m_numDispensed < coinCost); slotNum++)
				{
					yetToBeShot = (coinCost - m_numDispensed);
					coinsPerSlot = (yetToBeShot >= maxCoinsPerSlot) ? maxCoinsPerSlot : yetToBeShot;
					// Dispense a coin for each value of coinsPerSlot
					ShootCoinsFrom(slotNum, coinsPerSlot);
					if (m_numDispensed > coinCost) printf("OVERSHOT: After Shooting in Burst Mode");
				}
			}
			
			m_ticker++;

			if (m_ticker == BURST_DELAY) // Reset at max
				m_ticker = 0;
		}
		else if (m_dispenseStyle == LaunchData::DUMP)
		{
			int slotAmounts[6];
			slotAmounts[0] = slotAmounts[1] = slotAmounts[2] = slotAmounts[3] = slotAmounts[4] = slotAmounts[5] = 0;
			int coinCounter = coinCost;

			for (int i = 0; coinCounter > 0; i = (i==5) ? 0 : i+1)
			{
				slotAmounts[i]++;
				coinCounter--;
			}
			for (int slotNum = 0; slotNum < 6; slotNum++)
			{
				ShootCoinsFrom(slotNum, slotAmounts[slotNum]);
				if (m_numDispensed > coinCost) printf("OVERSHOT: After Shooting in Dump mode at index/slotnum: %d\n", slotNum);
			}
		}
		else // Serpentine or Sputter. Both work similarly. Differentiate within.
		{
			
			// Shoot a number of coins from that slot, proportional to the total number being shot out. This will reduce times for large amounts of coins to a maximum number of shot
			int maxCoinsPerSlot = (coinCost / QUANTITY_THRESHOLD) + 1;
			int yetToBeShot = (coinCost - m_numDispensed);
			int coinsPerSlot = (yetToBeShot >= maxCoinsPerSlot) ? maxCoinsPerSlot : yetToBeShot;

			int slotNum = 0;
			if (m_dispenseStyle == LaunchData::SERPENTINE) // Choose the slot number, in a serpentine pattern.
			{
				int n = m_numDispensed/coinsPerSlot % (NUM_SLOTS*2); // SlotNum in a NUM_SLOTS*2 idea of slots (as it loops over the NUM_SLOTS twice in the pattern)
				slotNum = (n < NUM_SLOTS) ?
						   n :
						   ((NUM_SLOTS*2)-1) - n;
			}
			else if (m_dispenseStyle == LaunchData::SPUTTER) // Choose the slot randomly
				slotNum = rand() % 6;

			// Dispense!
			ShootCoinsFrom(slotNum, coinsPerSlot);
			if (m_numDispensed > coinCost) printf("OVERSHOT: After Shooting in serpentine/sputter mode.\n");
		}


		// Stop dispensing if all of the coins have now been dispensed
		if (m_numDispensed >= coinCost) FinishDispensing();
	}
}

void Machine::dispense()
{
	// Can the player afford it?
	if (!m_dispensing && canAfford())
	{
		m_dispensing = true;
		// Take the player's money
		Wallet::Remove(coinCost);
		// Increase the cost of the next coin set by the increase constant.
		coinCost *= COIN_INCREASE; 
		// Note: We do this now, and not after dispensing, so that the number of coins dispensed is enough money for the player to afford the next price
		
		// Set the launch data
		LaunchData::DataPacket launchData = LaunchData::GetDataPacket();
		m_coinType = launchData.coinType;
		m_dispensePattern = launchData.pattern;
		m_dispenseStyle = launchData.style;
	}
}

void Machine::ForceDispense(int coinNum)
{
	m_dispensing = true;
	coinCost = coinNum;
	
	ShootCoinsFrom(3, coinNum, false);

	FinishDispensing();
}

void Machine::ShootCoinsFrom(int slotNum, int totalValue, bool intervalCoins)
{
	int numBronze, numSilver, numGold; // Number of each kind of coin
	numBronze = numSilver = numGold = 0; // Intialise counts
	// Initialise Values

	// When evenly divided, across all currently set coin types, this is the value that one of each would equal
	int totalEnumCoinTypeValue;
	if (m_coinType == LaunchData::BRONZE) totalEnumCoinTypeValue = CoinBronze::value;
	if (m_coinType == LaunchData::BS)	  totalEnumCoinTypeValue = CoinBronze::value + CoinSilver::value;
	if (m_coinType == LaunchData::SILVER) totalEnumCoinTypeValue = CoinSilver::value;
	if (m_coinType == LaunchData::SG)	  totalEnumCoinTypeValue = CoinSilver::value + CoinGold::value;
	if (m_coinType == LaunchData::GOLD)   totalEnumCoinTypeValue = CoinGold::value;
			
	// Total integer divisions of that value into the total value
	int numSets = totalValue / totalEnumCoinTypeValue;

	// Set the number of each type to be shot 
	if (m_coinType == LaunchData::BRONZE) 
	{
		numBronze = numSets;
	}
	if (m_coinType == LaunchData::BS)
	{
		numBronze = numSets;
		numSilver = numSets;
	}
	if (m_coinType == LaunchData::SILVER)
	{
		numSilver = numSets;
	}
	if (m_coinType == LaunchData::SG)
	{
		numSilver = numSets;
		numGold = numSets;
	}
	if (m_coinType == LaunchData::GOLD)
	{
		numGold = numSets;
	}

	// Find the remainder value that was not evenly divided into the sets
	int remainder = totalValue % totalEnumCoinTypeValue;
	if (remainder > 0)
	{
		int& fillerCoinCount = (remainder%10 == 0) ? numGold : (remainder%5 == 0) ? numSilver : numBronze;
		int  fillerCoinValue = (remainder%10 == 0) ? CoinGold::value : (remainder%5 == 0) ? CoinSilver::value : CoinBronze::value;
		fillerCoinCount += remainder / fillerCoinValue;
	}

	LaunchCoin<CoinBronze>(numBronze, slotNum);
	LaunchCoin<CoinSilver>(numSilver, slotNum);
	LaunchCoin<CoinGold>(numGold, slotNum);
}

template <class Coin_Type>
void Machine::LaunchCoin(int count, int slotNum)
{
	// DEBUG: Loop does not check for transgressions against: (m_numDispensed < coinCost). At time of coding - not sure if necessary
	for (count; count > 0 ; count--)
	{
		// Find this Coin's launch info
		SDL_Rect launchInfo = CoinLaunchInfo(slotNum);
		// Create a new coin for that destination
		Coin_Type* coin = new Coin_Type(launchInfo.x, launchInfo.y, launchInfo.w, launchInfo.h);
		// Add it to the collidables list
		g_game->addCollidable(coin);

		m_numDispensed += Coin_Type::value;
	}
}

SDL_Rect Machine::CoinLaunchInfo(int slotNum)
{
	int coinX = 0;
	int coinY = 0;
	bool valid;

	// Find a landing position based on the type of dispensing
	if (m_dispensePattern == LaunchData::POINT)
	{
		coinX = (screen->w / 2) - (TILE_SIZE/2);
		coinY = (screen->h / 2);
	}
	else if (m_dispensePattern == LaunchData::CORNERS)
	{
		coinX = (screen->w / 2);
		coinY = (screen->h / 2) + (TILE_SIZE/2);

		// Get a random point from here
		int n = rand() % 8;
		
		// Left Ground Coin
		coinX -= (n==0) * (TILE_SIZE*8);
		coinY -= (n==0) * (TILE_SIZE*3);
		
		coinX -= (n==1) * (TILE_SIZE*8);
		coinY += (n==1) * (TILE_SIZE*3);
		
		coinX -= (n==2) * (TILE_SIZE*3);
		coinY -= (n==2) * (TILE_SIZE*3);
		
		coinX -= (n==3) * (TILE_SIZE*3);
		coinY += (n==3) * (TILE_SIZE*3);


		// Right Ground Coin
		coinX += (n==4) * (TILE_SIZE*7);
		coinY += (n==4) * (TILE_SIZE*3);
		
		coinX += (n==5) * (TILE_SIZE*7);
		coinY -= (n==5) * (TILE_SIZE*3);

		coinX += (n==6) * (TILE_SIZE*2);
		coinY += (n==6) * (TILE_SIZE*3);
		
		coinX += (n==7) * (TILE_SIZE*2);
		coinY -= (n==7) * (TILE_SIZE*3);

	}
	else if (m_dispensePattern == LaunchData::LINES_H)
	{
		coinX = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
		coinY = (rand() % 5) * (2 * TILE_SIZE) + (4 * TILE_SIZE);
	}
	else if (m_dispensePattern == LaunchData::LINES_V)
	{
		coinX = (rand() % 9) * (2 * TILE_SIZE) + (2 * TILE_SIZE);
		coinY = rand() % (screen->h - 7*TILE_SIZE) + 4*TILE_SIZE; 
	}
	else if ((m_dispensePattern == LaunchData::LEFT) || (m_dispensePattern == LaunchData::RIGHT) || (m_dispensePattern == LaunchData::BOTH))
	{
		XY coords;

		if (m_dispensePattern == LaunchData::LEFT) coords = GetLeftCircleCoords();
		else if (m_dispensePattern == LaunchData::RIGHT) coords = GetRightCircleCoords();
		else // (m_dispensePattern == LaunchData::BOTH)
		{
			// Get either of the circle's coordinates
			bool b = rand() % 2;
			coords = b? GetLeftCircleCoords() : GetRightCircleCoords();
		}

		coinX = coords.x;
		coinY = coords.y;
	}
	else // NORM, randomise within the box
	{
		do
		{
			coinX = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
			coinY = rand() % (screen->h - 7*TILE_SIZE) + 4*TILE_SIZE; 
			valid = ValidLandingPosition(coinX, coinY);
		} while (!valid);
	}

	SDL_Rect r_rect = { static_cast<Sint16>(coin_slots[slotNum].first), static_cast<Sint16>(coin_slots[slotNum].second), static_cast<Uint16>(coinX), static_cast<Uint16>(coinY) };
	return r_rect;
}

Machine::XY Machine::GetLeftCircleCoords(bool addRightCoords)
{
	XY r_coords;

	// Top left corner
	XY topLeft;
	topLeft.x = 3*TILE_SIZE;
	topLeft.y = 6*TILE_SIZE;

	// Addition in right circle x coordinates
	int xc = addRightCoords * (10*TILE_SIZE); 
	
	r_coords.x = ((rand() % 4) * TILE_SIZE) + topLeft.x + xc;
	r_coords.y = ((rand() % 5) * TILE_SIZE) + topLeft.y;

//	printf("(%f, %f)\n", r_coords.x, r_coords.y);

	return r_coords;

}

bool Machine::ValidLandingPosition(int _x, int _y)
{
	return true;
	// Check to see if any of the coins collide with unmoveable objects (walls, shiny blocks, etc.)
}

void Machine::FinishDispensing() 
{
	m_dispensing = false;
	m_numDispensed = 0;
	m_ticker = 0;
}

bool Machine::canAfford()
{
    return (Wallet::GetCoins() >= coinCost);
}
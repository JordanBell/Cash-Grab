#include "Machine.h"
#include "Resources.h"

Machine::Machine(int x, int y) : Entity(x, y), coins(), m_dispensing(false), m_ticker(0), m_numDispensed(0), coinCost(START_MONEY), m_timeElapsed(0), m_dispenseType(NORM)
{
	sprite_sheet = g_resources->GetMoneyMachineSheet();
	skin = NULL; //Use the entire image

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
	//printf("Coins: %d, Cost: %d\n", g_game->wallet, coinCost);

	m_timeElapsed += delta;

    if ((m_dispensing) && (m_timeElapsed >= DISPENSING_STUTTER))
	{
		m_timeElapsed = 0;
		

		if (m_dispensePattern == BURST)
		{
			if (m_ticker == 0)
			{
				// Shoot a number of coins from that slot, proportional to the total number being shot out. This will reduce times for large amounts of coins to a maximum number of shot
				int coinsPerSlot = (coinCost / (QUANTITY_THRESHOLD*6/BURST_DELAY)) + 1;

				// Dispense a set of coins for each row
				for (int slotNum = 0; (slotNum < 6) && (m_numDispensed < coinCost); slotNum++)
				{
					// Dispense a coin for each value of coinsPerSlot
					ShootCoinsFrom(slotNum, coinsPerSlot);
				}
			}
			
			m_ticker++;

			if (m_ticker == BURST_DELAY) // Reset at max
				m_ticker = 0;
		}
		else if (m_dispensePattern == DUMP)
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
			}
		}
		else // Serpentine or Sputter. Both work similarly
		{
			
			// Shoot a number of coins from that slot, proportional to the total number being shot out. This will reduce times for large amounts of coins to a maximum number of shot
			int coinsPerSlot = (coinCost / QUANTITY_THRESHOLD) + 1;
			// Choose the slot number, in a serpentine pattern.
			int n = m_numDispensed/coinsPerSlot % (NUM_SLOTS*2);
			int slotNum = 0;
			if (m_dispensePattern == SERPENTINE)
			{
				slotNum = (n < NUM_SLOTS) ?
						   n :
						   ((NUM_SLOTS*2)-1) - n;
			}
			else if (m_dispensePattern == SPUTTER)
				slotNum = rand() % 6;

			// Dispense!
			ShootCoinsFrom(slotNum, coinsPerSlot);
		}


		// Stop dispensing if all of the coins have now been dispensed
		if (m_numDispensed > coinCost) printf("Somehow dispensed too many.\n");
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
		g_game->wallet -= coinCost;
		// Increase the cost of the next coin set by the increase constant.
		coinCost *= COIN_INCREASE; 
		// Note: We do this now, and not after dispensing, so that the number of coins dispensed is enough money for the player to afford the next price
		m_dispenseType = RandomDispenseType();
		m_dispensePattern = RandomDispensePattern();
	}
}

void Machine::ShootCoinsFrom(int slotNum, int totalValue, bool intervalCoins)
{
	// Silver Coins (5) NOTE: For Gold coins, only dispense half the amount, leave some values for Silver coins
	int setsOfTen = totalValue / 10;
	for (int numGold = setsOfTen / 2; ((numGold > 0) && (m_numDispensed < coinCost)); numGold--)// (((totalValue / 10) >= 1) && (m_numDispensed < coinCost))
	{
		// Find this Coin's launch info
		SDL_Rect launchInfo = CoinLaunchInfo(slotNum);
		// Create a new coin for that destination
		CoinGold* coin = new CoinGold(launchInfo.x, launchInfo.y, launchInfo.w, launchInfo.h);
		// Add it to the collidables
		g_game->addCollidable(coin);

		m_numDispensed += 10;
		totalValue -= 10;
	}

	// Silver Coins (5)
	while (((totalValue / 5) >= 1) && (m_numDispensed < coinCost))
	{

		// Find this Coin's launch info
		SDL_Rect launchInfo = CoinLaunchInfo(slotNum);
		// Create a new coin for that destination
		CoinSilver* coin = new CoinSilver(launchInfo.x, launchInfo.y, launchInfo.w, launchInfo.h);
		// Add it to the collidables
		g_game->addCollidable(coin);

		m_numDispensed += 5;
		totalValue -= 5;
	}

	// Bronze Coins (1)
	while ((totalValue > 0) && (m_numDispensed < coinCost))
	{
		if (m_numDispensed > coinCost) 
			printf("YO");

		// Find this coin's launch info
		SDL_Rect launchInfo = CoinLaunchInfo(slotNum);
		// Create a new coin for that destination
		Coin* coin = new Coin(launchInfo.x, launchInfo.y, launchInfo.w, launchInfo.h);
		// Add it to the collidables
		g_game->addCollidable(coin);

		m_numDispensed++;
		totalValue--;
	}
}


SDL_Rect Machine::CoinLaunchInfo(int slotNum)
{
	int coinX = 0;
	int coinY = 0;
	bool valid;

	// Find a landing position based on the type of dispensing
	if (m_dispenseType == POINT)
	{
		coinX = (screen->w / 2) - (TILE_SIZE/2);
		coinY = (screen->h / 2);
	}
	else if (m_dispenseType == CORNERS)
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
	else if (m_dispenseType == LINES_H)
	{
		coinX = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
		coinY = (rand() % 5) * (2 * TILE_SIZE) + (4 * TILE_SIZE);
	}
	else if (m_dispenseType == LINES_V)
	{
		coinX = (rand() % 9) * (2 * TILE_SIZE) + (2 * TILE_SIZE);
		coinY = rand() % (screen->h - 6*TILE_SIZE) + 4*TILE_SIZE; 
	}
	else if ((m_dispenseType == LEFT) || (m_dispenseType == RIGHT) || (m_dispenseType == BOTH))
	{
		XY coords;

		if (m_dispenseType == LEFT) coords = getLeftCircleCoords();
		else if (m_dispenseType == RIGHT) coords = getRightCircleCoords();
		else // (m_dispenseType == BOTH)
		{
			// Get either of the circle's coordinates
			bool b = rand() % 2;
			coords = b? getLeftCircleCoords() : getRightCircleCoords();
		}

		coinX = coords.x;
		coinY = coords.y;
	}
	else // NORM, randomise within the box
	{
		do
		{
			coinX = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
			coinY = rand() % (screen->h - 6*TILE_SIZE) + 4*TILE_SIZE; 
			valid = ValidLandingPosition(coinX, coinY);
		} while (!valid);
	}

	SDL_Rect r_rect = { coin_slots[slotNum].first, coin_slots[slotNum].second, coinX, coinY };
	return r_rect;
}

Machine::XY Machine::getLeftCircleCoords(bool addRightCoords)
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
	m_dispenseType = NORM;
}

bool Machine::canAfford()
{
    return (g_game->wallet >= coinCost);
}

Machine::DispenseType Machine::RandomDispenseType(void)
{
	int n = rand() % 20;
	
	//return INSERT_TEST_VALUE;

	// 10% chance for each non-normal dispense type
	if (n == 0) return POINT;
	if (n == 1) return CORNERS;
	if (n == 2) return LINES_H;
	if (n == 3) return LINES_V;
	if (n == 4) return LEFT;
	if (n == 5) return RIGHT;
	if (n == 6) return BOTH;
	else return NORM;
}

Machine::DispensePattern Machine::RandomDispensePattern(void)
{
	int n = rand() % 10;
	
	//return INSERT_TEST_VALUE;

	// 10% chance for each non-normal dispense type
	if (n <= 2)		 return BURST;		// %30 Chance
	else if (n <= 5) return SERPENTINE; // %30 Chance
	else if (n <= 8) return SPUTTER;	// %30 Chance
	else			 return DUMP;		// %10 Chance
	
}
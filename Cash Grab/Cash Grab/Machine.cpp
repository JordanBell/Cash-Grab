#include "Machine.h"
#include "Resources.h"
#include "Inventory.h"
#include "PowerupMagnetism.h"
#include "PowerupPull.h"
#include "PowerupSmash.h"
#include "Door.h"
#include "Key.h"
#include "CashWad.h"

#include "CoinBronze.h"
#include "CoinSilver.h"
#include "CoinGold.h"

#define KEY_LAUNCH_VAL 50
#define CASH_INTERVAL 25
#define CASH_AMOUNT 100

Machine::Machine(const int x, const int y)
	: Collidable(x, y), Dispenser(x, y, Element::NORMAL), m_LaunchKey(false), m_KeyLaunched(false)
{
	m_imageSurface = g_resources->GetMoneyMachineSheet();
    m_HitBox->w = TILE_SIZE * 6;
    m_HitBox->h = TILE_SIZE * 2;
    
	// Claim as immoveable as a Collidable
    m_IsMoveable = false;

    for (int i = 0; i < NUM_SLOTS; i++) 
	{
        int slotX = x + (i * TILE_SIZE);
        int slotY = y + 2*TILE_SIZE;
        
        Position* slotPos = new Position(slotX, slotY);
        CoinSlots[i] = *slotPos;
    }
}

void Machine::OnDump(DispenseList& dispenseList)
{
	for (auto& dispensePair : dispenseList)
	{
		const string type = dispensePair.first;
		int& amount = dispensePair.second;

		int slotAmounts[NUM_SLOTS];
		slotAmounts[0] = slotAmounts[1] = slotAmounts[2] = slotAmounts[3] = slotAmounts[4] = slotAmounts[5] = 0; 

		// Add amounts for each slot
		for (int slotNum = 0; amount > 0; slotNum = (slotNum==NUM_SLOTS-1) ? 0 : slotNum+1)
		{
			slotAmounts[slotNum]++;
			amount--;
		}

		// Shoot from each of the slots
		for (int slotNum = 0; slotNum < 6; slotNum++)
		{
			int perSlot = slotAmounts[slotNum];
			const Position launchPos = Position(CoinSlots[slotNum].x, CoinSlots[slotNum].y);
			const int launchAmount = perSlot;
			DISPENSE_BY_TYPE
		}
	}
}

void Machine::OnBurst(DispenseList& dispenseList)
{
	for (auto& dispensePair : dispenseList)
	{
		const string type = dispensePair.first;
		int& amount = dispensePair.second;

		// Shoot a number of throwables from that slot, proportional to the total number being shot out. This will reduce times for large amounts of throwables to a maximum number of shot
		const int maxPerSlot = (amount / (QUANTITY_THRESHOLD*6/DEFAULT_BURST_DELAY)) + 1;
				
		// Throwables to be shot per slot
		int perSlot;

		// Dispense a set of throwables for each row
		for (int slotNum = 0; (slotNum < 6) && (amount > 0); slotNum++)
		{
			perSlot = amount;
			if (perSlot > maxPerSlot)
				perSlot = maxPerSlot;

			// Launch that number of throwables from this slot
			const Position launchPos = Position(CoinSlots[slotNum].x, CoinSlots[slotNum].y);
			const int launchAmount = perSlot;
			DISPENSE_BY_TYPE

			amount -= perSlot;
		}
	}
}

void Machine::OnSerpentine(DispenseList& dispenseList)
{
	for (auto& dispensePair : dispenseList)
	{
		const string type = dispensePair.first;
		int& amount = dispensePair.second;
		int total = amount;

		// Shoot a number of coins from that slot, proportional to the total number being shot out. This will reduce times for large amounts of coins to a maximum number of shot
		const int maxPerSlot = (amount / QUANTITY_THRESHOLD) + 1;
		int perSlot = amount;
		if (perSlot > maxPerSlot)
			perSlot = maxPerSlot;

		int slotNum = 0;

		int n = m_SingleShotTicker % (NUM_SLOTS*2); // SlotNum in a NUM_SLOTS*2 idea of slots (as it loops over the NUM_SLOTS twice in the pattern)
		slotNum = (n < NUM_SLOTS) ?
					n :
					((NUM_SLOTS*2)-1) - n;

		// Launch that number of throwables from this slot
		const Position launchPos = Position(CoinSlots[slotNum].x, CoinSlots[slotNum].y);
		const int launchAmount = perSlot;
		DISPENSE_BY_TYPE

		amount -= perSlot;
	}
}

void Machine::OnSputter(DispenseList& dispenseList)
{
	for (auto& dispensePair : dispenseList)
	{
		const string type = dispensePair.first;
		int& amount = dispensePair.second;
		int total = amount;

		// Shoot a number of coins from that slot, proportional to the total number being shot out. This will reduce times for large amounts of coins to a maximum number of shot
		const int maxPerSlot = (amount / QUANTITY_THRESHOLD) + 1;
		int perSlot = amount;
		if (perSlot > maxPerSlot)
			perSlot = maxPerSlot;

		int slotNum = rand() % 6;

		// Launch that number of throwables from this slot
		const Position launchPos = Position(CoinSlots[slotNum].x, CoinSlots[slotNum].y);
		const int launchAmount = perSlot;
		DISPENSE_BY_TYPE

		amount -= perSlot;
	}
}

const Position Machine::GetLaunchTo(void)
{
	// Determint the 
	Position to;
	DispensePattern dispensePattern = m_LaunchData->pattern;

	// Find a landing position based on the type of dispensing
	if (dispensePattern == LaunchData::POINT)
	{
		to.x = (screen->w / 2) - (TILE_SIZE/2);
		to.y = (screen->h / 2);
	}
	else if (dispensePattern == LaunchData::CORNERS)
	{
		to.x = (screen->w / 2);
		to.y = (screen->h / 2) + (TILE_SIZE/2);

		// Get a random point from here
		int r = rand() % 8;
		
		// Left Ground Coin
		to.x -= (r==0) * (TILE_SIZE*8);
		to.y -= (r==0) * (TILE_SIZE*3);
		
		to.x -= (r==1) * (TILE_SIZE*8);
		to.y += (r==1) * (TILE_SIZE*3);
		
		to.x -= (r==2) * (TILE_SIZE*3);
		to.y -= (r==2) * (TILE_SIZE*3);
		
		to.x -= (r==3) * (TILE_SIZE*3);
		to.y += (r==3) * (TILE_SIZE*3);


		// Right Ground Coin
		to.x += (r==4) * (TILE_SIZE*7);
		to.y += (r==4) * (TILE_SIZE*3);
		
		to.x += (r==5) * (TILE_SIZE*7);
		to.y -= (r==5) * (TILE_SIZE*3);

		to.x += (r==6) * (TILE_SIZE*2);
		to.y += (r==6) * (TILE_SIZE*3);
		
		to.x += (r==7) * (TILE_SIZE*2);
		to.y -= (r==7) * (TILE_SIZE*3);

	}
	else if (dispensePattern == LaunchData::LINES_H)
	{
		to.x = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
		to.y = (rand() % 5) * (2 * TILE_SIZE) + (4 * TILE_SIZE);
	}
	else if (dispensePattern == LaunchData::LINES_V)
	{
		to.x = (rand() % 9) * (2 * TILE_SIZE) + (2 * TILE_SIZE);
		to.y = rand() % (screen->h - 7*TILE_SIZE) + 4*TILE_SIZE; 
	}
	else if ((dispensePattern == LaunchData::LEFT) || (dispensePattern == LaunchData::RIGHT) || (dispensePattern == LaunchData::BOTH))
	{
		XY coords;

		if (dispensePattern == LaunchData::LEFT) coords = GetLeftCircleCoords();
		else if (dispensePattern == LaunchData::RIGHT) coords = GetRightCircleCoords();
		else // (dispensePattern == LaunchData::BOTH)
		{
			// Get either of the circle's coordinates
			bool b = rand() % 2;
			coords = b? GetLeftCircleCoords() : GetRightCircleCoords();
		}

		to.x = coords.x;
		to.y = coords.y;
	}
	else // NORM, randomise within the box
	{
		to.x = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
		to.y = rand() % (screen->h - 7*TILE_SIZE) + 4*TILE_SIZE; 
	}

	return to;
}

const Position Machine::GetLeftCircleCoords(const bool addRightCoords)
{
	Position r_Pos;

	// Top left corner
	XY topLeft;
	topLeft.x = 3*TILE_SIZE;
	topLeft.y = 6*TILE_SIZE;

	// Addition in right circle x coordinates
	int xc = addRightCoords * (10*TILE_SIZE); 
	
	r_Pos.x = ((rand() % 4) * TILE_SIZE) + topLeft.x + xc;
	r_Pos.y = ((rand() % 5) * TILE_SIZE) + topLeft.y;

//	printf("(%f, %f)\n", r_coords.x, r_coords.y);

	return r_Pos;

}

#undef DISPENSE_BY_TYPE

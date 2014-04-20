#include "Machine.h"
#include "Resources.h"
#include "Game.h"

Machine::Machine(int x, int y) : Entity(x, y), coins(), m_dispensing(false), m_numDispensed(0)
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
    if (m_dispensing)
	{
		// Take that money from the player
		g_game-> wallet--;
		// Find where to shoot the coin from
		int slotNum = m_numDispensed % NUM_SLOTS;

		// Dispense!
		ShootCoinFrom(slotNum);

		m_numDispensed++;

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
		// Increase the cost of the next coin set by the increase constant.
		coinCost *= COIN_INCREASE; 
		// Note: We do this now, and not after dispensing, so that the number of coins dispensed is enough money for the player to afford the next price
	}

	for (int i = 0; i < NUM_SLOTS; i++)
	{	
		ShootCoinFrom(i);
	}
}

void Machine::ShootCoinFrom(int slotNum)
{
	int coinX = 0;
	int coinY = 0;
	bool valid;

	// Find a valid landing position
	do
	{
		coinX = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
		coinY = rand() % (screen->h - 6*TILE_SIZE) + 4*TILE_SIZE; 
		valid = ValidLandingPosition(coinX, coinY);
	} while (!valid);

	// Create a new coin for that destination
	Coin *coin = new Coin(coin_slots[slotNum].first, coin_slots[slotNum].second, coinX, coinY);
	// Add it to the collidables
	g_game->addCollidable(coin);
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
}
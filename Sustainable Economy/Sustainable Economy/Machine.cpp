#include "Machine.h"
#include "Resources.h"
#include "Game.h"

Machine::Machine(int x, int y) : Entity(x, y), coins()
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


Machine::~Machine(void)
{
}

void Machine::update(int delta)
{
    
}

void Machine::dispense()
{
	for (int i = 0; i < NUM_SLOTS; i++)
	{	
		int coinX = 0;
		int coinY = 0;
		bool valid = true;
		do
		{
			coinX = rand() % (screen->w - 3*TILE_SIZE) + TILE_SIZE;
			coinY = rand() % (screen->h - 6*TILE_SIZE) + 4*TILE_SIZE; 
			//valid = ValidLandingPosition(coinX, coinY);
		} while (!valid);

		Coin *coin = new Coin(coin_slots[i].first, coin_slots[i].second, coinX, coinY);
		g_game->addCollidable(coin);
	}
}

bool ValidLandingPosition(int _x, int _y)
{
	return true;
	// Check to see if any of the coins collide with unmoveable objects (walls, shiny blocks, etc.)
}

void Machine::set_skin()
{
    
}
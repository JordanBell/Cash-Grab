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
		int coinX = rand() % screen->w;
		int coinY = rand() % screen->h;
		printf("x1: %d, y1: %d, x2: %d, y2: %d\n", coin_slots[i].first, coin_slots[i].second, coinX, coinY);
		Coin *coin = new Coin(coin_slots[i].first, coin_slots[i].second, coinX, coinY);
		g_game->addEntity(coin);
	}
}

void Machine::set_skin()
{
    
}
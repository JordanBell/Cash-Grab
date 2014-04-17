#include "Machine.h"
#include "Resources.h"
#include "Game.h"

Machine::Machine(int x, int y) : Entity(x, y), coins()
{
	sprite_sheet = g_resources->GetMoneyMachineSheet();
	skin = NULL; //Use the entire image

    dispenser_pos = std::pair<int, int>(x, (y + 2) * TILE_SIZE);
    
    for (int i = 0; i < NUM_SLOTS; i++) {
        int slotX = (dispenser_pos.first + i) * TILE_SIZE;
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
	printf("DISPENSING");
    /*Coin *coin = new Coin(x, y, 0, 0);
    g_game->addEntity(coin);*/
}

void Machine::set_skin()
{
    
}
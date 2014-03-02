#include "Machine.h"
#include "Game.h"

Machine::Machine(int x, int y) : Entity(x, y), coins()
{
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

void Machine::update()
{
    
}

void Machine::dispense()
{
    Coin *coin = new Coin(x, y, 0, 0);
    Game::addEntity(coin);
}

void Machine::set_skin()
{
    
}
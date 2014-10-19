#include "KeyCode.h"
#include "Machine.h"
#include "Player.h"

void KeyCode::enter(void)
{
    machine->dispense();
}
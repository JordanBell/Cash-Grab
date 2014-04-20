#ifndef prompt_h
#define prompt_h

#include "entity.h"
#include "Machine.h"

#define MS_OF_FLASH 500
class Prompt :
	public Entity
{
public:
	Prompt(Machine* machine);
	~Prompt(void) {}

	void update(int delta);
	void render(void) { if (visible) Entity::render(); }

private:
	int timeSinceFlash;
	Machine* machine;
	bool visible;
};

#endif
#ifndef prompt_h
#define prompt_h

#include "entity.h"

#define MS_OF_FLASH 500
class Prompt :
	public Entity
{
public:
	Prompt(int x, int y);
	~Prompt(void) {}

	void update(int delta);
	void render(void) { if (visible) Entity::render(); }

private:
	int timeSinceFlash;
	bool visible;
};

#endif
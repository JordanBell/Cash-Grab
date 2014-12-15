#ifndef prompt_h
#define prompt_h

#include "gameObject.h"
#include "Machine.h"

#define MS_OF_FLASH 500
class Prompt :
	public GameObject
{
public:
	Prompt(Machine* machine);
	~Prompt(void) {}

	void Update(int delta);
	void Render(void) { if (visible) GameObject::Render(); }

private:
	int timeSinceFlash;
	Machine* machine;
	bool visible;
};

#endif
#ifndef prompt_h
#define prompt_h

#include "entity.h"
class Prompt :
	public Entity
{
public:
	Prompt(int x, int y);
	~Prompt(void);

	void update(int delta);

private:
	void set_skin();
};

#endif
#pragma once
#include "entity.h"
class Prompt :
	public Entity
{
public:
	Prompt(void);
	~Prompt(void);

	void update();
	void render();

private:
	void set_skin();
};


#pragma once
#include "entity.h"
class Environment :
	public Entity
{
public:
	Environment(void);
	~Environment(void);

	void update();
	void render();

private:
	void set_skin();
};


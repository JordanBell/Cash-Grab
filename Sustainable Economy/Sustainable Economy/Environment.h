#ifndef environment_h
#define environment_h

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

#endif
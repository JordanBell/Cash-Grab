#ifndef machine_h
#define machine_h

#include "entity.h"
class Machine :
	public Entity
{
public:
	Machine(void);
	~Machine(void);
	
	void update();
	void dispense();

private:
	void set_skin();
};

#endif
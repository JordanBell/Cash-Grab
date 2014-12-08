//
//  Wall.h
//  CashGrab
//
//  Created by Tristan Bell on 20/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __CashGrab__Wall__
#define __CashGrab__Wall__

#include "Collidable.h"

class Wall : public Collidable, public GameObject {
    
public:
    Wall(int x, int y) : Collidable(x, y), GameObject(x, y)
		{ m_IsMoveable = false; }

	void Render(void) { /* Do Nothing */ }
};

#endif /* defined(__CashGrab__Wall__) */

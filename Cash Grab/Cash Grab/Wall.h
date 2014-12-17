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
		{ m_IsMoveable = false; m_renderPriority = 99; }

	void Render(void) { if ( SHOW_WALLS ) { SDL_Rect r = { (Sint16)(x+s_renderingOffset_x), (Sint16)(y+s_renderingOffset_y), 32, 32}; SDL_FillRect(screen, &r, 0xFF0000FF); } }
};

#endif /* defined(__CashGrab__Wall__) */

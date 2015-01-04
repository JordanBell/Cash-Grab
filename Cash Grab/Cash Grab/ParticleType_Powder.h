#pragma once
#include "ParticleSimple.h"

class ParticleType_Powder :
	public ParticleSimple
{
public:

	ParticleType_Powder(int end_x, int end_y, int height)
    : ParticleSimple(end_x, end_y, height)
    {
        /* Make it Light */
        SetGravity(m_gravityForce/300);
        
        /* Make it a random size */
        int randSize = rand()%3+1;
        XY newSize(randSize, randSize);
        SetSize(newSize);
    }

	ParticleType_Powder(int start_x, int start_y, int end_x, int end_y)
    : ParticleSimple(start_x, start_y, end_x, end_y)
    { 
        /* Make it Light */
        SetGravity(m_gravityForce/300);
        
        /* Make it a random size */
        int randSize = rand()%3+1;
        XY tmp(randSize, randSize);
        SetSize(tmp);
    }
};

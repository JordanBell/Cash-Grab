#pragma once
#include "particlesimple.h"

class ParticleType_Powder :
	public ParticleSimple
{
public:
	#define COMMON_CONSTRUCT \
		{ \
		/* Make it White */ \
		SetColor(0x00cce3e6); \
		\
		/* Make it Light */ \
		SetGravity(m_gravityForce/300); \
		\
		/* Make it a random size */ \
		int randSize = rand()%3+1; \
		SetSize(XY(randSize, randSize)); \
	    }

	ParticleType_Powder(int end_x, int end_y, int height)
		: ParticleSimple(end_x, end_y, height) 
	COMMON_CONSTRUCT

	ParticleType_Powder(int start_x, int start_y, int end_x, int end_y)
		: ParticleSimple(start_x, start_y, end_x, end_y) 
	COMMON_CONSTRUCT

	#undef COMMON_CONSTRUCT
};

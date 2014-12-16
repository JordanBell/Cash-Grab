#pragma once
#include "particletype_powder.h"

class ParticleAsh :
	public ParticleType_Powder
{
public:
	ParticleAsh(int end_x, int end_y, int height)
		: ParticleType_Powder(end_x, end_y, height) { SetColor(0x00333333); }
};


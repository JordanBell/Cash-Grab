#pragma once
#include "ParticleType_Powder.h"

class ParticleSnow :
	public ParticleType_Powder
{
public:
	ParticleSnow(int end_x, int end_y, int height)
		: ParticleType_Powder(end_x, end_y, height) { SetColor(0x00cce3e6); }
};

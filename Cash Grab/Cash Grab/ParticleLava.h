#pragma once
#include "particlesimple.h"
#include "XY.h"

class ParticleLava :
	public ParticleSimple
{
public:
	ParticleLava(const int sx, const int sy, const int ex, const int ey, Dimensions size);

	void Update(int delta) override final;

private:
	Uint32 m_CoolingColorChange;
};


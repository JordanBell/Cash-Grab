#include "ParticleLava.h"

ParticleLava::ParticleLava(const int sx, const int sy, const int ex, const int ey, Dimensions size)
	: ParticleSimple(sx, sy, ex, ey), m_CoolingColorChange(0)
{
	// Lava particles have a new fade length
	SetFadeLength(70);

	// Vary the size
	if ((size.x > 1) && (size.y > 1))
	{
		// -1, +0, +1
		int sizeChange;
		if (size.x < 5) sizeChange = rand()% 3 - 1;
		else sizeChange = rand()% 7 - 3;

		size.x += sizeChange;
		size.y += sizeChange;
	}

	SetSize(size);

	// Find the starting color
	int startKey = rand()%4; // Size determines the rate of cooling
	Uint32 startDeviation = 0;

	switch (startKey)
	{
	case 0: startDeviation = 0x00080000; break;
	case 1: startDeviation = 0x00110000; break;
	case 2: startDeviation = 0x00220000; break;
	case 3: startDeviation = 0x00440000; break;
	}


	SetColor(k_BaseColor - startDeviation);

	// Find the rate of cooling
	int changeKey = size.x; // Size determines the rate of cooling

	if (changeKey <= 3)
		m_CoolingColorChange = 0x00030000;
	else if (changeKey <= 7)
		m_CoolingColorChange = 0x00020000;
	else if (changeKey <= 10)
		m_CoolingColorChange = 0x00010000;
}

void ParticleLava::Update(int delta)
{
	ParticleSimple::Update(delta);

	// Make the color darker as it cools
	int newColor = GetColor() - m_CoolingColorChange;

	// Only change if there is room to do so
	if (newColor > 0)
		SetColor(newColor);
}


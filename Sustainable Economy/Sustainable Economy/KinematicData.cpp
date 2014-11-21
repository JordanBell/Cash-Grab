#include "KinematicData.h"
#include <cstdlib>

const float KinematicData::ComputeAngleBySuppression(const int angleSuppression)
{
	if (angleSuppression <= -1)
		return 90; // Straight Up

	// Angles are more shallow the higher the suppression
	if (angleSuppression == 0)
		return (rand() % 14) + 75;
	else if (angleSuppression == 1)
		return (rand() % 10) + 70;
	else if (angleSuppression == 2)
		return 45;
	else if (angleSuppression == 3)
		return 30;
	else if (angleSuppression == 4)
		return 15;
	else if (angleSuppression >= 5)
		return 1;
}
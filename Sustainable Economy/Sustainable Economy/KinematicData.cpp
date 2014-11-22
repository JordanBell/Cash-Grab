#include "KinematicData.h"
#include <cstdlib>

const float KinematicData::ComputeAngleBySuppression(const int angleSuppression)
{
	if (angleSuppression <= -1)
		return 90; // Straight Up

	// Angles are more shallow the higher the suppression
    switch (angleSuppression) {
        case 0:
            return (rand() % 14) + 75;
            break;
        case 1:
            return (rand() % 10) + 70;
            break;
        case 2:
            return 45;
            break;
        case 3:
            return 30;
            break;
        case 4:
            return 15;
            break;
        case 5:
            return 1;
            break;
        default:
            return 1;
    }
}
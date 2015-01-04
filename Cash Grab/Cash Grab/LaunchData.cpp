#include "LaunchData.h"

string LaunchData::ToString(c_type coin)
{
	if (coin == BRONZE) return "Bronze";
	if (coin == BS) return "Bronze & Silver";
	if (coin == SILVER) return "Silver";
	if (coin == SG) return "Silver & Gold";
	if (coin == GOLD) return "Gold";

	return "Error in ToString(c_type)";
}

string LaunchData::ToString(d_style style)
{
	if (style == BURST) return "Burst";
	if (style == SERPENTINE) return "Serpentine";
	if (style == SPUTTER) return "Sputter";
	if (style == DUMP) return "Dump";

	return "Error in ToString(d_style)";
}

string LaunchData::ToString(d_pat pat)
{
	if (pat == NORM) return "Normal";
	if (pat == POINT) return "Point";
	if (pat == CORNERS) return "Corners";
	if (pat == LINES_H) return "Horizontal Lines";
	if (pat == LINES_V) return "Vertical Lines";
	if (pat == LEFT) return "Left Side";
	if (pat == RIGHT) return "Right Side";
	if (pat == BOTH) return "Both Sides";

	return "Error in ToString(d_pat)";
}


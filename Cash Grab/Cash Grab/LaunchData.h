#pragma once
#include <vector>
#include <string>
using namespace std;

namespace LaunchData
{
	enum DispensePattern {
		NORM, POINT, CORNERS, LINES_H, LINES_V, LEFT, RIGHT, BOTH
	};

	enum DispenseStyle {
		BURST, SERPENTINE, SPUTTER, DUMP
	};

	enum CoinType {
		BRONZE, BS, SILVER, SG, GOLD
	};

	typedef DispenseStyle	d_style;
	typedef DispensePattern d_pat;
	typedef CoinType		c_type;

	struct DataPacket {
		DataPacket(d_style ds, d_pat dp, c_type cp) 
			: style(ds), pattern(dp), coinType(cp) {}

		d_style style;
		d_pat pattern;
		c_type coinType;
	};
	
	string ToString(d_pat pat);
	string ToString(d_style style);
	string ToString(c_type coin);
};


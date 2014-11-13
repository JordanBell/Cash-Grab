#pragma once
#include <vector>
using namespace std;

class LaunchData
{
public:
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
	
	static vector<int>  ComputeActivationLevels(bool print = false);
	static DataPacket GetDataPacket();
	static void Notify(int totalCoins);
	static void ForceTier(int tier) { Notify(tierActivationLevels[tier]); }
	static void PrintLaunchInfo(void);

private:
	LaunchData(void);
	~LaunchData(void);

	static void UpdateTier(void);
	static void UpdatePatternsAndStyles(void);
	static CoinType ComputeCoinType(void);
	static DispenseStyle ComputeStyle(void);
	static DispensePattern ComputePattern(void);
	
	static string ToString(d_pat pat);
	static string ToString(d_style style);
	static string ToString(c_type coin);
	
	static const vector<int> tierActivationLevels;
	static vector<pair<d_style, int>> possibleStyles;   // Pairs of style with corresponding chance weights
	static vector<pair<d_pat, int>>	possiblePatterns;
	static int recordedTotal;
	static int recordedTier;
};


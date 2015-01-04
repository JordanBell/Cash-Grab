#pragma once
#include <vector>
#include "LaunchData.h"
using namespace LaunchData;

class LevelProgress
{
public:
	LevelProgress(void);
	~LevelProgress(void) {}
	
	// Set the value for tierActivationLevels based on a calculation
	vector<int>  ComputeActivationLevels(bool print = false);

	// Construct and return a data packet containing the launch data example at this level.
	DataPacket* GetDataPacket(void);

	// Update the recorded total of coins, and change data accordingly
	void Notify(const int totalCoins);

	// (debug) Print the information of this level's launch info
	void PrintLaunchInfo(void);

private:
	// Update the recordedTier value by recalculating it with the currently held coin total
	void UpdateTier(void);

	// Get the coin type that this is currently obtained.
	CoinType ComputeCoinType(void);

	// Get a dispense style with respect to each of their chances of selection
	DispenseStyle ComputeStyle(void);

	// Get a dispense pattern with respect to each of their chances of selection
	DispensePattern ComputePattern(void);
	


	// The last recorded coin total, as told by the last Notify call
	int recordedTotal;

	// The last calculated tier (level) as updated from the Notify call.
	int recordedTier;

	// The list of number of rounds needed for each level
	vector<int> tierActivationLevels;

	// Pairs of style with corresponding chance weights
	vector< pair<d_style, int> > possibleStyles; 

	// Pairs of patterns with corresponding chance weights
	vector< pair<d_pat, int> > possiblePatterns;
};


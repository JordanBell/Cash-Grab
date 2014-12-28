#include "LevelProgress.h"
#include "LaunchData.h"
#include "Wallet.h"
#include <cstdlib>

using namespace LaunchData;

LevelProgress::LevelProgress(void)
	: recordedTier(-1), recordedTotal(0)
{
	tierActivationLevels = ComputeActivationLevels();
	possibleStyles = vector<pair<LaunchData::DispenseStyle, int>>();
	possiblePatterns = vector<pair<LaunchData::DispensePattern, int>>();
}

vector<int> LevelProgress::ComputeActivationLevels(bool print)
{
	vector<int> r_thresholds = vector<int>();

	int numRoundsPerTier[] = {5, // Bronze
							  5,
							  5, // Bronze/Silver
							  5,
							  5, // Silver
							  5,
							  5, // Silver/Gold
							  5, 
							  5}; // Gold

	int count = 0;
	// Print the calculated rounds per tier
	for (int i : numRoundsPerTier)
	{
		if (print) {
			count++;
			printf("For tier %d: %d\n", count, i);
		}
	}

	int coinsAfterRound = 5; // After 0 rounds
	count = 0;
	for (int i : numRoundsPerTier)
	{
		for (int j = 0; j < i; j++) // i times
			coinsAfterRound *= COIN_INCREASE;

		r_thresholds.push_back(coinsAfterRound);
		count++;
		if (print)
			printf("Num coins needed for tier %d = %d\n", count, coinsAfterRound);
	}

	return r_thresholds;
}

DataPacket LevelProgress::GetDataPacket()
{
	// The current tier determines the launch data
	int tier = recordedTier;

	// Determine coin type
	c_type r_coin = ComputeCoinType();
	d_style r_style = ComputeStyle();
	d_pat r_pat = ComputePattern();

	return DataPacket(r_style, r_pat, r_coin);
}

void LevelProgress::Notify(const int totalCoins)
{

	int oldTier = recordedTier;
	recordedTotal = totalCoins;
	UpdateTier();

	// If a new tier has been reached, add new styles and/or patterns
	if (recordedTier != oldTier)
	{
		//printf("*!*!* NEW TIER, %d, REACHED !*!*!\n", recordedTier);
		possibleStyles.clear();
		possiblePatterns.clear();
		if (recordedTier >= 0)
		{
			possibleStyles.push_back(pair<d_style, int>(SPUTTER, 30));
			possiblePatterns.push_back(pair<d_pat, int>(NORM, 30));
		}
		if (recordedTier >= 1)
		{
			possiblePatterns.push_back(pair<d_pat, int>(LINES_H, 10));
			possiblePatterns.push_back(pair<d_pat, int>(LINES_V, 10));
		}
		if (recordedTier >= 2)
		{
			possibleStyles.push_back(pair<d_style, int>(BURST, 30));
		}
		if (recordedTier >= 3)
		{
			possiblePatterns.push_back(pair<d_pat, int>(CORNERS, 10));
		}
		if (recordedTier >= 4)
		{
			possibleStyles.push_back(pair<d_style, int>(SERPENTINE, 30));
		}
		if (recordedTier >= 5)
		{
			possiblePatterns.push_back(pair<d_pat, int>(LEFT, 10));
			possiblePatterns.push_back(pair<d_pat, int>(RIGHT, 10));
		}
		if (recordedTier >= 6)
		{
			possiblePatterns.push_back(pair<d_pat, int>(BOTH, 10));
		}
		if (recordedTier >= 7)
		{
			possiblePatterns.push_back(pair<d_pat, int>(POINT, 10));
		}
		if (recordedTier >= 8)
		{
			possibleStyles.push_back(pair<d_style, int>(DUMP, 10));
		}
	}
}

void LevelProgress::UpdateTier(void)
{
	// Find the tier index that the total of coins is between
	int size = tierActivationLevels.size();
	for (int i = 0; i < size; i++)
	{
		if (tierActivationLevels.at(i) > recordedTotal) 
		{
			recordedTier = (i>0) ? i-1 : 0; // Equate to the previous index, if not at 0;
			return;
		}
	}

	// Made it this far, must be the last index
	recordedTier = tierActivationLevels.size()-1;
}

CoinType LevelProgress::ComputeCoinType(void)
{
		 if (recordedTier < 2)  return BRONZE;
	else if (recordedTier < 4)  return BS;
	else if (recordedTier < 6)  return SILVER;
	else if (recordedTier < 8)  return SG;
	else						return GOLD;
}

DispenseStyle LevelProgress::ComputeStyle(void)
{
	// Count all of the weights, for computing a selection average
	int totalWeight = 0;
	for (pair<d_style, int> styleAndWeight : possibleStyles)
		totalWeight += styleAndWeight.second;

	int randAllocator = rand() % totalWeight;
	for (auto pair : possibleStyles)
	{
		if (randAllocator <= pair.second)
			return pair.first;
		else
			randAllocator -= pair.second;
	}

	// Something went wrong
	throw new runtime_error("Bad algorithm.");
}

DispensePattern LevelProgress::ComputePattern(void)
{
	// Count all of the weights, for computing a selection average
	int totalWeight = 0;
	for (pair<d_pat, int> patternAndWeight : possiblePatterns)
		totalWeight += patternAndWeight.second;

    int randAllocator = rand() % totalWeight;
	for (auto pair : possiblePatterns)
	{
		if (randAllocator <= pair.second)
			return pair.first;
		else
			randAllocator -= pair.second;
	}

	// Something went wrong
	throw new runtime_error("Bad algorithm.");
}

void LevelProgress::PrintLaunchInfo(void)
{
	string out = "";

	out += "Possible Patterns:\n\t";
	for (pair<d_pat, int> p : possiblePatterns)
		out += (ToString(p.first).append(" "));
	
	out += "\nPossible Styles:\n\t";
	for (pair<d_style, int> s : possibleStyles)
		out += ToString(s.first).append(" ");
	
	out += "\nCoin Type: ";
	out += ToString(ComputeCoinType());

	printf("%s\n", out.c_str());
}

#include "LaunchData.h"
#include "Wallet.h"

#include <random>

const vector<int> LaunchData::tierActivationLevels = LaunchData::ComputeActivationLevels();

vector<pair<LaunchData::DispenseStyle, int>> LaunchData::possibleStyles = vector<pair<LaunchData::DispenseStyle, int>>();
vector<pair<LaunchData::DispensePattern, int>> LaunchData::possiblePatterns = vector<pair<LaunchData::DispensePattern, int>>();
int LaunchData::recordedTotal = 0;
int LaunchData::recordedTier = -1;

vector<int> LaunchData::ComputeActivationLevels(bool print)
{
	vector<int> r_thresholds = vector<int>();

	// Calculate the values for each theoretical tier to be activated, in order to last the suggested rounds at the current settings
	int numSecondsPerTier[] = {90, // Bronze
							  60, 
							  60, // Bronze/Silver
							  60,
							  30, // Silver
							  60,
							  60, // Silver/Gold
							  60,
							  90}; // Gold

	// Note: In the upcoming calculation, each of the ideal times are divided by a rough estimate of how long it would take for the player to collect the coins
	//int numRoundsPerTier[] = {numSecondsPerTier[0] / 18, // Bronze
	//						  numSecondsPerTier[1] / 22,
	//						  numSecondsPerTier[2] / 25, // Bronze/Silver
	//						  numSecondsPerTier[3] / 25,
	//						  numSecondsPerTier[4] / 25, // Silver
	//						  numSecondsPerTier[5] / 25,
	//						  numSecondsPerTier[6] / 25, // Silver/Gold
	//						  numSecondsPerTier[7] / 25, 
	//						  numSecondsPerTier[8] / 25}; // Gold

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


// Update the recorded total of coins, and change data accordingly
void LaunchData::Notify(int totalCoins)
{

	int oldTier = recordedTier;
	recordedTotal = totalCoins;
	UpdateTier();

	// If a new tier has been reached, add new styles and/or patterns
	if (recordedTier != oldTier)
	{
		printf("*!*!* NEW TIER, %d, REACHED !*!*!\n", recordedTier);
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

void LaunchData::PrintLaunchInfo(void)
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

LaunchData::DataPacket LaunchData::GetDataPacket()
{
	// The current tier determines the launch data
	int tier = recordedTier;

	// Determine coin type
	c_type r_coin = ComputeCoinType();
	d_style r_style = ComputeStyle();
	d_pat r_pat = ComputePattern();

	return DataPacket(r_style, r_pat, r_coin);
}

LaunchData::CoinType LaunchData::ComputeCoinType(void)
{
		 if (recordedTier < 2)  return BRONZE;
	else if (recordedTier < 4)  return BS;
	else if (recordedTier < 6)  return SILVER;
	else if (recordedTier < 8)  return SG;
	else						return GOLD;
}

LaunchData::DispenseStyle LaunchData::ComputeStyle(void)
{
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

LaunchData::DispensePattern LaunchData::ComputePattern(void)
{
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

void LaunchData::UpdateTier(void)
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

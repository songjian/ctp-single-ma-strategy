#include "stdafx.h"
#include <numeric>
#include "indicators_class.h"

double Indicators::ma(string chInstrumentId, int nPeriod, int nTimePeriod, int nShift)
{
	vector<Bar> bars;
	vector<double> closeVec(nPeriod);
	int r = Bar::getBars(&bars, chInstrumentId, nPeriod, nTimePeriod, nShift);

	if (r == -2)
	{
		return 0.0;
	}

	for (size_t i = 0; i < bars.size(); i++)
	{
		closeVec[i] = bars[i].close;
	}

	int sum = accumulate(closeVec.begin(), closeVec.end(), 0);
	
	return sum / nPeriod;
}
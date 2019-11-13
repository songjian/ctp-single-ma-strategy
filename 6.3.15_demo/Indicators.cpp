#include "stdafx.h"
#include "Indicators.h"
#include <numeric>

double Indicators::ma(TThostFtdcInstrumentIDType instrumentId, int period, int timePeriod, int shift)
{
	vector<Bar> bars(period);
	vector<double> closeVec(period);
	int r = Bar::getBars(&bars, period, timePeriod, shift);

	if (r == -2)
	{
		return 0.0;
	}

	for (size_t i = 0; i < bars.size(); i++)
	{
		closeVec[i] = bars[i].close;
	}

	int sum = accumulate(closeVec.begin(), closeVec.end(), 0);
	
	return sum / period;
}
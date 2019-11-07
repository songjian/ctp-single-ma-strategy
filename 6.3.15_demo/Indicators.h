#pragma once
#include "ThostFtdcUserApiDataType.h"

class Indicators
{
	double ma(TThostFtdcInstrumentIDType instrumentId, int period, int timePeriod, int shift);
};

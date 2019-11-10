#pragma once
#include "ThostFtdcUserApiDataType.h"
#include "Bar.h"

class Indicators
{
public:
	double ma(TThostFtdcInstrumentIDType instrumentId, int period, int timePeriod, int shift);
};

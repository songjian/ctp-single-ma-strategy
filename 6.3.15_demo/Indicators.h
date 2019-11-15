#pragma once
#include "ThostFtdcUserApiDataType.h"
#include "Bar.h"

class Indicators
{
public:
	double ma(string chInstrumentId, int nPeriod, int nTimePeriod, int nShift);
};

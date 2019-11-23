#pragma once
#include "ThostFtdcUserApiDataType.h"
#include "bar_class.h"

class Indicators
{
public:
	double ma(string chInstrumentId, int nPeriod, int nTimePeriod, int nShift);
};

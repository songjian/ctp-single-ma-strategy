#pragma once
#include "define.h"
#include "strategy.h"
#include "Indicators.h"
#include "ThostFtdcUserApiStruct.h"

class SingleMaStrategy : public Strategy
{
public:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData);
	virtual void OnBar();
	SingleMaStrategy(TThostFtdcInstrumentIDType instrumentId);
private:
	int period=10;
	int timePeriod=15;
	Indicators indicators;
	TThostFtdcInstrumentIDType instrumentId;
};


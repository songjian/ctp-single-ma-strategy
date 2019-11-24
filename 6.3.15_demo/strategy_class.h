#pragma once
#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcTraderApi.h"

using namespace std;

class Strategy
{
public:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData);
	virtual void OnBar(CThostFtdcDepthMarketDataField* pDepthMarketData, size_t nTimePeriod);
	virtual void OnMessage();
	virtual void OnAccount();
};
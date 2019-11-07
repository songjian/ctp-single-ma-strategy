#pragma once
#include "ThostFtdcUserApiStruct.h"

class Strategy
{
public:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData);
	virtual void OnBar(CThostFtdcDepthMarketDataField* pDepthMarketData);
	virtual void OnMessage();
	virtual void OnAccount();
};
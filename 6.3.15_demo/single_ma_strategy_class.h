#pragma once
#include "define.h"
#include "getconfig.h"
#include "ThostFtdcUserApiStruct.h"
#include "strategy_class.h"
#include "indicators_class.h"

class SingleMaStrategy : public Strategy
{
public:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData);
	virtual void OnBar(CThostFtdcDepthMarketDataField* pDepthMarketData, size_t nTimePeriod);
	SingleMaStrategy(TThostFtdcInstrumentIDType chInstrumentID, CThostFtdcTraderApi* pUserApi) : m_InstrumentId(chInstrumentID), m_pUserApi(pUserApi) {}
private:
	int OpenPosition(TThostFtdcDirectionType cDirection, double fLimitPrice);
	int ClosePosition();
	int ReversePosition();
	int m_nPeriod=10;
	int m_nTimePeriod=15;
	int m_nRequestID = 0;
	Indicators m_Indicators;
	string m_InstrumentId;
	CThostFtdcOrderField m_Order;
	CThostFtdcTraderApi* m_pUserApi;
};


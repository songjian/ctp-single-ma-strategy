#pragma once
#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcTraderApi.h"

class Strategy
{
public:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData);
	virtual void OnBar(CThostFtdcDepthMarketDataField* pDepthMarketData, size_t nTimePeriod);
	virtual void OnMessage();
	virtual void OnAccount();
	Strategy(){}
	Strategy(TThostFtdcInstrumentIDType chInstrumentID, CThostFtdcTraderApi* pUserApi) : m_InstrumentId(chInstrumentID), m_pUserApi(pUserApi) {}
protected:
	string m_InstrumentId;
	CThostFtdcTraderApi* m_pUserApi;
};
#pragma once
#include "CustomMdHandler.h"
#include "MarketDataRecord.h"

extern MarketDataRecord g_mdRecord;

class CMdHandler : public CCustomMdHandler
{
public:
	CMdHandler(CThostFtdcMdApi* pUserMdApi) : CCustomMdHandler(pUserMdApi) {};
	///深度行情通知
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		g_mdRecord.update(pDepthMarketData);
		printf("接收行情,%s,%lf\n", pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);
	}
};


#pragma once
#include "CustomMdHandler.h"
#include "MarketDataRecord.h"

extern MarketDataRecord g_mdRecord;

class CMdHandler : public CCustomMdHandler
{
public:
	CMdHandler(CThostFtdcMdApi* pUserMdApi) : CCustomMdHandler(pUserMdApi) {};
	///�������֪ͨ
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		g_mdRecord.update(pDepthMarketData);
		printf("��������,%s,%lf\n", pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice);
	}
};


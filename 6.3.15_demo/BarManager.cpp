#include "stdafx.h"
#include "BarManager.h"

void BarManager::OnTick(CThostFtdcDepthMarketDataField* pMarketData)
{
	m_pMarketDataVec->push_back(*pMarketData);

	for (size_t i = 0; i < m_pMarketDataVec->size(); i++)
	{
		printf("MarketDataVec_%zd_%s", i, m_pMarketDataVec[i].LastPrice);
	}
}
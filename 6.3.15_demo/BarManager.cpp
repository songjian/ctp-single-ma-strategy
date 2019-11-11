#include "stdafx.h"
#include "BarManager.h"
#include "getconfig.h"

using namespace std;


BarManager* BarManager::CreateBarManager()
{
	static BarManager bm;
	return &bm;
}

void BarManager::OnTick(CThostFtdcDepthMarketDataField* pMarketData)
{
	int index = findIndex(pMarketData->InstrumentID);

	m_MarketDataMVec[index].push_back(*pMarketData);
}

BarManager::BarManager()
{
	string instrumentIds = getConfig("config", "InstrumentID");
	m_InstrumentIdVec.push_back(instrumentIds);
	m_MarketDataMVec.resize(m_InstrumentIdVec.size());
}

int BarManager::findIndex(string sInstrumentId)
{
	for (size_t i = 0; i < m_InstrumentIdVec.size(); i++)
	{
		if (m_InstrumentIdVec[i] == sInstrumentId)
		{
			return i;
		}
	}
	return -1;
}

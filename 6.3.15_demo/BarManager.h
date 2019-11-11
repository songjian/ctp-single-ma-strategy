#pragma once
#include "ThostFtdcUserApiStruct.h"
#include <algorithm>

using namespace std;

class BarManager
{
public:
	static BarManager* CreateBarManager();
	void OnTick(CThostFtdcDepthMarketDataField*);
	BarManager();
private:
	string FileName(CThostFtdcDepthMarketDataField* pDepthMarketData);
	int findIndex(string sInstrumentId);
	vector<string> m_InstrumentIdVec;
	vector<vector<CThostFtdcDepthMarketDataField> > m_MarketDataMVec;
};

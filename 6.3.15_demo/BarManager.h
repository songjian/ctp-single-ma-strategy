#pragma once
#include "ThostFtdcUserApiStruct.h"
#include <algorithm>
#include <fstream>
#include "Bar.h"

using namespace std;

class BarManager
{
public:
	static BarManager* CreateBarManager();
	void OnTick(CThostFtdcDepthMarketDataField*);
	BarManager();
private:
	string FileName(string instrumentId, int i_TimePeriod);
	void BarToFile(string fileName, Bar* bar);
	int findIndex(string sInstrumentId);
	tm MdUpdateTimeToTm(CThostFtdcDepthMarketDataField* pDepthMarketData);
	Bar* MdVecToBar(int iVecIndex);
	void PeriodConverter(string instrumentId, int period);
	vector<int> GetCurrentPeriodConverter(CThostFtdcDepthMarketDataField* pDepthMarketData);
	int GetPervPeriodIndex(int period);
	vector<string> m_InstrumentIdVec;
	vector<vector<CThostFtdcDepthMarketDataField> > m_MarketDataMVec;
	ofstream outfile;
	const int periods[4] = { 5, 15, 30, 60 };
};

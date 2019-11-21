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
	string FileName(string chInstrumentId, int nTimePeriod);
	void BarToFile(string chFileName, Bar* pBar);
	size_t FindIndex(string chInstrumentId);
	tm GetDepthMarketDataTm(CThostFtdcDepthMarketDataField* pDepthMarketData);
	Bar* MdVecToBar(size_t nVecIndex);
	void PeriodConverter(string chInstrumentId, size_t nTimePeriod);
	void ExecutionPeriodConverter(string chInstrumentId);
	size_t GetCurrentPeriodConverter(CThostFtdcDepthMarketDataField* pDepthMarketData, vector<int>* gnConverTimePeriods);
	size_t GetPervTimePeriod(size_t nTimePeriod);
	vector<string> m_gchInstrumentIds;
	vector<vector<CThostFtdcDepthMarketDataField> > m_gDepthMarketData;
	ofstream m_Outfile;
	const int m_nTimePeriods[4] = { 5,15,30,60 };
};

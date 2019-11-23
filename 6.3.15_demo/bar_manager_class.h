#pragma once
#include "getconfig.h"
#include "ThostFtdcUserApiStruct.h"
#include <algorithm>
#include <fstream>
#include "bar_class.h"
#include "strategy_class.h"

using namespace std;

class BarManager
{
public:
	void OnTick(CThostFtdcDepthMarketDataField*);
	BarManager(Strategy* pStrategy) : m_pStrategy(pStrategy)
	{
		string instrumentIds = getConfig("config", "InstrumentID");
		m_gchInstrumentIds.push_back(instrumentIds);
		m_gDepthMarketData.resize(m_gchInstrumentIds.size());
	}
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
	Strategy* m_pStrategy;
};

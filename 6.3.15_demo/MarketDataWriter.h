#pragma once
#include "ThostFtdcUserApiStruct.h"
#include <fstream>
#include "BarManager.h"

using namespace std;

class MarketDataWriter
{
public:
	void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData);
	MarketDataWriter(BarManager* barManager) : m_pBarManager(barManager) {}
	~MarketDataWriter();
private:
	void MdToFile(CThostFtdcDepthMarketDataField* pDepthMarketData);
	string FileName(CThostFtdcDepthMarketDataField* pDepthMarketData);
	string lastFileName;
	ofstream outfile;
	BarManager* m_pBarManager;
};

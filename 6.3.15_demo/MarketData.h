#pragma once
#include "ThostFtdcUserApiStruct.h"
#include <fstream>
#include "BarManager.h"

using namespace std;

class MarketData
{
public:
	void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData);
	MarketData();
	~MarketData();
private:
	void MdToFile(CThostFtdcDepthMarketDataField* pDepthMarketData);
	string FileName(CThostFtdcDepthMarketDataField* pDepthMarketData);
	string lastFileName;
	ofstream outfile;
	BarManager* m_pBarManager;
};

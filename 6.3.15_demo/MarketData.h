#pragma once
#include "ThostFtdcUserApiStruct.h"
#include <fstream>

using namespace std;

class MarketData
{
public:
	vector<CThostFtdcDepthMarketDataField>* m_pMarketDataVec;
	void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData);
	void OnBar();
	~MarketData();
private:
	void MdToFile(CThostFtdcDepthMarketDataField* pDepthMarketData);
	string FileName(CThostFtdcDepthMarketDataField* pDepthMarketData);
	string lastFileName = NULL;
	ofstream outfile;
};

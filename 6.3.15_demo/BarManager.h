#pragma once
#include "ThostFtdcUserApiStruct.h"

using namespace std;

class BarManager
{
public:
	void OnTick(CThostFtdcDepthMarketDataField*);
private:
	vector<CThostFtdcDepthMarketDataField>* m_pMarketDataVec;
};

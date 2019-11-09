#pragma once
#include <string>
#include <vector>
#include "ThostFtdcUserApiStruct.h"
#include "readfile.h"

using namespace std;

class Bar
{
public:
	void update(CThostFtdcDepthMarketDataField*);
	//void PeriodConverter();
	//void OnBarGenerated();
	static Bar* getBars(int timePeriod, int nums);
private:
	vector<CThostFtdcDepthMarketDataField>* m_pBuffMd;
};

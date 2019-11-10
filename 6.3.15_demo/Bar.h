#pragma once
#include "ThostFtdcUserApiStruct.h"
#include "readfile.h"

using namespace std;

class Bar
{
public:
	double open;
	double high;
	double low;
	double close;
	int volume;
public:
	void update(CThostFtdcDepthMarketDataField*);
	//void PeriodConverter();
	//void OnBarGenerated();
	//static int getBars(Bar buffBars[], int period, int timePeriod, int shift);
	static int getBars(vector<Bar> buffBars, int period, int timePeriod, int shift);
private:
	vector<CThostFtdcDepthMarketDataField>* m_pBuffMd;
	static Bar CsvToBar(string csv);
};

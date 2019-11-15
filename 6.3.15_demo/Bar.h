#pragma once
#include "ThostFtdcUserApiStruct.h"
#include "readfile.h"

using namespace std;

class Bar
{
public:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	double open;
	double high;
	double low;
	double close;
	int volume;
public:
	static int getBars(vector<Bar>* pBuffBars, string chInstrumentId, int nPeriod, int nTimePeriod, int nShift);
private:
	static Bar GetBarFromCsv(string chCsv);
};

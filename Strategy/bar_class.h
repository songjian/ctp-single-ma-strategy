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
	size_t timeperiod;
public:
	static int getBars(vector<Bar>* pBarVector, string chInstrumentId, int nPeriod, int nTimePeriod, int nShift = 0)
	{
		vector<string> buffLine;
		string filePath = ".\\bars\\" + chInstrumentId + "_" + to_string(nTimePeriod) + ".csv";
		int r = readFileTail(&buffLine, filePath, nPeriod, nShift);

		if (r == -2)
		{
			return -2;
		}

		for (size_t i = 0; i < buffLine.size(); i++)
		{
			Bar bar = Bar::GetBarFromCsv(buffLine[i]);
			pBarVector->push_back(bar);
		}

		return 0;
	}
private:
	static Bar GetBarFromCsv(string chCsv)
	{
		static Bar bar;
		int r = sscanf(chCsv.c_str(), "%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%d", &bar.year, &bar.month, &bar.day, &bar.hour, &bar.minute, &bar.open, &bar.high, &bar.low, &bar.close, &bar.volume);
		return bar;
	}
};
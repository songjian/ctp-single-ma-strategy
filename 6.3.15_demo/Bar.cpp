#include "stdafx.h"
#include "Bar.h"

using namespace std;

int Bar::getBars(vector<Bar>* buffBars, int period, int timePeriod, int shift = 0)
{
	vector<string> buffLine;
	string filePath = ".\\bars\\" + to_string(timePeriod) + ".csv";
	int r = readFileTail(&buffLine, filePath, period, shift);

	if (r == -2)
	{
		return -2;
	}

	for (size_t i = 0; i < buffLine.size(); i++)
	{
		buffBars->push_back(Bar::CsvToBar(buffLine[i]));
	}

	return 0;
}

Bar Bar::CsvToBar(string csv)
{
	Bar bar;
	int r = sscanf(csv.c_str(), "%.8lf,%.8lf,%.8lf,%.8lf,%d", &bar.open, &bar.high, &bar.low, &bar.close, &bar.volume);
	return bar;
}

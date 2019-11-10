#include "stdafx.h"
#include "Bar.h"

using namespace std;

void Bar::update(CThostFtdcDepthMarketDataField* pMarketData)
{
}

int Bar::getBars(vector<Bar> buffBars, int period, int timePeriod, int shift = 0)
{
	vector<string> buffLine;
	string filePath = ".\\bars\\" + to_string(timePeriod) + ".csv";
	printf("文件路径%s\n", filePath.c_str());
	printf("开始读取bar。\n");
	//int ret = readFileTail(filePath, period, &buffLine);
	int r = readFileTail(&buffLine, filePath, period, shift);

	if (r == -2)
	{
		return -2;
	}

	for (size_t i = 0; i < buffLine.size(); i++)
	{
		buffBars[i] = Bar::CsvToBar(buffLine[i]);
	}

	for (size_t i = 0; i < period; i++)
	{
		printf("buffBars %zd Close  %.8lf\n", i, buffBars[i].close);
	}
	return 0;
}

Bar Bar::CsvToBar(string csv)
{
	Bar bar;
	int r = sscanf(csv.c_str(), "%.8lf,%.8lf,%.8lf,%.8lf,%d", &bar.open, &bar.high, &bar.low, &bar.close, &bar.volume);
	return bar;
}

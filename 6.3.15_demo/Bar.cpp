#include "stdafx.h"
#include "Bar.h"

using namespace std;

void Bar::update(CThostFtdcDepthMarketDataField* pMarketData)
{

}

Bar* Bar::getBars(int timePeriod, int nums)
{
	vector<string> buffLine;
	string filePath = ".\\klinefile\\" + to_string(timePeriod) + "m.csv";
	printf("开始读取bar。\n");
	int ret = readFileTail(filePath, nums, &buffLine);

	if (ret == -2)
	{
		printf("文件记录不足。\n");
	}

	printf("readFileTail结果%d", ret);

	printf("buffLine Size:%zd", buffLine.size());

	for (int i = 0; i < buffLine.size(); i++)
	{
		printf("buffLine_%d: %s\n", i, buffLine[i].c_str());
	}
	return nullptr;
}

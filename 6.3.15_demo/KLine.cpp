#pragma once
#include "stdafx.h"
#include "KLine.h"

FILE* klinefile, * c_15m;
vector<CThostFtdcDepthMarketDataField> bufferMdVec;
vector<Bar> buff1mKLine(15);
tm lastMdTm;

vector<Bar> bars;
vector<double> buffSma;
const int period = 10;
int barSize = 0;

void updateBufferMarketData(CThostFtdcDepthMarketDataField *md)
{
	int year, month, day, hour, minute, second;
	sscanf(md->ActionDay, "%4d%2d%2d", &year, &month, &day);
	sscanf(md->UpdateTime, "%d:%d:%d", &hour, &minute, &second);

	LOG("年：%d  月：%d  日：%d  时：%d  分：%d  秒：%d\n", year, month, day, hour, minute, second);
	LOG("lastMdTm年：%d  月：%d  日：%d\n", lastMdTm.tm_year, lastMdTm.tm_mon, lastMdTm.tm_mday);

	tm mdTm;
	mdTm.tm_year = year - 1900;
	mdTm.tm_mon = month - 1;
	mdTm.tm_mday = day;
	mdTm.tm_hour = hour;
	mdTm.tm_min = minute;
	mdTm.tm_sec = second;
	mdTm.tm_isdst = 0;

	if (lastMdTm.tm_year == 0)
	{
		lastMdTm = mdTm;
	}

	if (mdTm.tm_min > lastMdTm.tm_min)
	{
		mdflush();
		lastMdTm = mdTm;
	}

	/*if (mdTm.tm_min == 1 || mdTm.tm_min == 16 || mdTm.tm_min == 31 || mdTm.tm_min == 46)
	{
		conver(15);
	}*/

	if (mdTm.tm_min == 3 || 
		mdTm.tm_min == 5 || 
		mdTm.tm_min == 7 ||
		mdTm.tm_min == 9 ||
		mdTm.tm_min == 11 ||
		mdTm.tm_min == 13 ||
		mdTm.tm_min == 15 ||
		mdTm.tm_min == 17 ||
		mdTm.tm_min == 19 ||
		mdTm.tm_min == 21 ||
		mdTm.tm_min == 23 ||
		mdTm.tm_min == 25 ||
		mdTm.tm_min == 27 ||
		mdTm.tm_min == 29 ||
		mdTm.tm_min == 31 ||
		mdTm.tm_min == 33 ||
		mdTm.tm_min == 35 ||
		mdTm.tm_min == 37 ||
		mdTm.tm_min == 39 ||
		mdTm.tm_min == 41 ||
		mdTm.tm_min == 43 ||
		mdTm.tm_min == 45 ||
		mdTm.tm_min == 47 ||
		mdTm.tm_min == 49 ||
		mdTm.tm_min == 51 ||
		mdTm.tm_min == 53 ||
		mdTm.tm_min == 55 ||
		mdTm.tm_min == 57 ||
		mdTm.tm_min == 59 ||
		mdTm.tm_min == 1)
	{
		conver(2);
	}

	bufferMdVec.push_back(*md);

	
	LOG("lastMdTm年：%d  月：%d  日：%d\n", lastMdTm.tm_year, lastMdTm.tm_mon, lastMdTm.tm_mday);
}

void mdflush()
{
	double open, high, low, close;
	int volume;
	
	open = bufferMdVec.front().LastPrice;
	close = bufferMdVec.back().LastPrice;
	high = bufferMdVec.front().LastPrice;
	low = bufferMdVec.front().LastPrice;
	volume = bufferMdVec.back().Volume - bufferMdVec.front().Volume;

	for (size_t i = 0; i < bufferMdVec.size(); i++)
	{
		high = bufferMdVec[i].LastPrice > high ? bufferMdVec[i].LastPrice : high;
		low = bufferMdVec[i].LastPrice < low ? bufferMdVec[i].LastPrice : low;
	}
	
	TThostFtdcDateType day;
	strcpy_s(day, bufferMdVec.front().ActionDay);
	int hour, minute, second;
	sscanf(bufferMdVec.front().UpdateTime, "%d:%d:%d", &hour, &minute, &second);

	klinefile = fopen(".\\klinefile\\1m.csv", "a");
	fprintf(klinefile, "%s,%d,%d,%.8lf,%.8lf,%.8lf,%.8lf,%d\n", day, hour, minute, open, high, low, close, volume);
	fflush(klinefile);
	fclose(klinefile);

	bufferMdVec.clear();

	Bar b = { *day ,hour, minute, open, high, low, close,volume };

	buff1mKLine.push_back(b);
}

void conver(int c_minute)
{
	if (buff1mKLine.size()!=c_minute)
	{
		buff1mKLine.clear();
		return;
	}

	FILE* m15csv;

	TThostFtdcDateType day;
	char hour[3], minute[3];
	double open, high, low, close;
	int volume;

	strcpy_s(day, buff1mKLine.front().Day);
	strcpy_s(hour, buff1mKLine.front().Hour);
	strcpy_s(minute, buff1mKLine.front().Minute);
	open = buff1mKLine.front().Open;
	close = buff1mKLine.back().Close;
	high = buff1mKLine.front().High;
	low = buff1mKLine.front().Low;
	volume = 0;

	for (size_t i = 0; i < buff1mKLine.size(); i++)
	{
		high = buff1mKLine[i].High > high ? buff1mKLine[i].High : high;
		low = buff1mKLine[i].Low < low ? buff1mKLine[i].Low : low;
		volume += buff1mKLine[i].Volume;
	}

	m15csv = fopen(".\\klinefile\\15m.csv", "a");
	fprintf(m15csv, "%s,%s,%s,%.8lf,%.8lf,%.8lf,%.8lf,%d\n", day, hour, minute,open, high, low, close, volume);
	fflush(m15csv);
	fclose(m15csv);

	Bar b = { *day, *hour, *minute, open, high, low, close, volume };
	StartStrategy(&b);
}






int checkSignal(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	if (bars.empty())
	{
		readCsv();
	}

	if (bars.size() >= period && bars.size() > barSize)
	{
		double sma = calcSma();
		buffSma.push_back(sma);
		barSize = bars.size();
	}


	return 0;
}

int StartStrategy(Bar* bar)
{
	if (bars.empty())
	{
		readCsv();
	}
	bars.push_back(*bar);
	return 0;
}

int readCsv()
{
	FILE* kline;
	kline = fopen(".\\klinefile\\15m.csv", "r");
	char buff[255];
	while (fgets(buff, 255, kline))
	{
		TThostFtdcDateType day;
		char hour[3], minute[3];
		double open, high, low, close;
		int volume;
		sscanf(buff, "%s,%s,%s,%.8lf,%.8lf,%.8lf,%.8lf,%d", day, hour, minute, &open, &high, &low, &close, &volume);
		Bar b = { *day, *hour, *minute, open, high, low, close, volume };
		bars.push_back(b);
	}
	return 0;
}

double calcSma()
{
	double sma, total = 0;
	for (size_t i = bars.size() - period; i < bars.size(); i++)
	{
		total += bars[i].Close;
	}
	sma = total / period;
	return sma;
}
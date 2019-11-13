#include "stdafx.h"
#include "BarManager.h"
#include "getconfig.h"

using namespace std;


BarManager* BarManager::CreateBarManager()
{
	static BarManager bm;
	return &bm;
}

void BarManager::OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	string instrumentId = pDepthMarketData->InstrumentID;
	int index = findIndex(instrumentId);
	if (m_MarketDataMVec[index].empty())
	{
		return;
	}
	tm tmCurrMd = MdUpdateTimeToTm(pDepthMarketData);
	tm tmPrevMd = MdUpdateTimeToTm(&m_MarketDataMVec[index].back());

	if (tmCurrMd.tm_min != tmPrevMd.tm_min)
	{
		vector<int> currPeriodConverter = GetCurrentPeriodConverter(&m_MarketDataMVec[index].back());
		Bar* bar = MdVecToBar(index);
		string fileName = FileName(instrumentId, 1);
		BarToFile(fileName, bar);

		for (size_t i = 0; i < currPeriodConverter.size(); i++)
		{
			PeriodConverter(instrumentId, currPeriodConverter[i]);
		}
	}

	m_MarketDataMVec[index].push_back(*pDepthMarketData);
}

BarManager::BarManager()
{
	string instrumentIds = getConfig("config", "InstrumentID");
	m_InstrumentIdVec.push_back(instrumentIds);
	m_MarketDataMVec.resize(m_InstrumentIdVec.size());
}

string BarManager::FileName(string instrumentId, int i_TimePeriod = 1)
{
	string filePath = ".\\bars\\";
	return filePath + instrumentId + "_" + to_string(i_TimePeriod) + ".csv";
}

void BarManager::BarToFile(string fileName, Bar* bar)
{
	outfile.open(fileName, ios::app);

	outfile << bar->year << ",";
	outfile << bar->month << ",";
	outfile << bar->day << ",";
	outfile << bar->hour << ",";
	outfile << bar->minute << ",";
	outfile << bar->open << ",";
	outfile << bar->high << ",";
	outfile << bar->low << ",";
	outfile << bar->close << ",";
	outfile << bar->volume << endl;

	outfile.close();
}

int BarManager::findIndex(string sInstrumentId)
{
	for (size_t i = 0; i < m_InstrumentIdVec.size(); i++)
	{
		if (m_InstrumentIdVec[i] == sInstrumentId)
		{
			return i;
		}
	}
	return -1;
}

tm BarManager::MdUpdateTimeToTm(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	int year, month, day, hour, minute, second;
	sscanf_s(pDepthMarketData->ActionDay, "%4d%2d%2d", &year, &month, &day);
	sscanf_s(pDepthMarketData->UpdateTime, "%d:%d:%d", &hour, &minute, &second);
	tm mdTm;
	mdTm.tm_year = year - 1900;
	mdTm.tm_mon = month - 1;
	mdTm.tm_mday = day;
	mdTm.tm_hour = hour;
	mdTm.tm_min = minute;
	mdTm.tm_sec = second;
	mdTm.tm_isdst = 0;
	return mdTm;
}

Bar* BarManager::MdVecToBar(int iVecIndex)
{
	static Bar bar;
	tm tmMd = MdUpdateTimeToTm(&m_MarketDataMVec[iVecIndex].back());
	bar.year = tmMd.tm_year;
	bar.month = tmMd.tm_mon;
	bar.day = tmMd.tm_yday;
	bar.hour = tmMd.tm_hour;
	bar.minute = tmMd.tm_min;
	bar.open = m_MarketDataMVec[iVecIndex].front().LastPrice;
	bar.close = m_MarketDataMVec[iVecIndex].back().LastPrice;
	bar.high = m_MarketDataMVec[iVecIndex].front().LastPrice;
	bar.low = m_MarketDataMVec[iVecIndex].front().LastPrice;

	for (size_t i = 0; i < m_MarketDataMVec[iVecIndex].size(); i++)
	{
		bar.high = m_MarketDataMVec[iVecIndex][i].LastPrice > bar.high ? m_MarketDataMVec[iVecIndex][i].LastPrice : bar.high;
		bar.low = m_MarketDataMVec[iVecIndex][i].LastPrice < bar.low ? m_MarketDataMVec[iVecIndex][i].LastPrice : bar.low;
	}

	m_MarketDataMVec[iVecIndex].clear();

	return &bar;
}

void BarManager::PeriodConverter(string instrumentId, int timePeriod)
{
	int iPervTimePeriod = GetPervPeriodIndex(timePeriod);
	iPervTimePeriod = iPervTimePeriod > 0 ? iPervTimePeriod : 1;
	int iBarNum = timePeriod / iPervTimePeriod;
	vector<Bar> vecBars(iBarNum);
	int r = Bar::getBars(&vecBars, iBarNum, iPervTimePeriod, 0);

	if (r == -2)
	{
		return;
	}

	Bar bar;
	bar.year = vecBars.front().year;
	bar.month = vecBars.front().month;
	bar.day = vecBars.front().day;
	bar.hour = vecBars.front().hour;
	bar.minute = vecBars.front().minute;
	bar.open = vecBars.front().open;
	bar.close = vecBars.back().close;
	bar.high = vecBars.front().high;
	bar.low = vecBars.front().low;

	for (size_t i = 0; i < vecBars.size(); i++)
	{
		bar.high = bar.high < vecBars[i].high ? vecBars[i].high : bar.high;
		bar.low = bar.low > vecBars[i].low ? vecBars[i].low : bar.low;
	}

	string outFileName = FileName(instrumentId, timePeriod);
	BarToFile(outFileName, &bar);
}

vector<int> BarManager::GetCurrentPeriodConverter(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	static vector<int> periodVec;
	tm tmMd = MdUpdateTimeToTm(pDepthMarketData);
	for (size_t i = 0; i < sizeof(periods); i++)
	{
		if (tmMd.tm_min % periods[i] == 0)
		{
			periodVec.push_back(periods[i]);
		}
	}
	return periodVec;
}

int BarManager::GetPervPeriodIndex(int period)
{
	int index = 0;
	for (size_t i = 0; i < sizeof(periods); i++)
	{
		if (periods[i] == period)
		{
			index = i;
		}
	}

	return index > 0 ? index - 1 : 0;
}


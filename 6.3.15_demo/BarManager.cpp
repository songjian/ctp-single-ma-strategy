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
	string chInstrumentId = pDepthMarketData->InstrumentID;
	string chFileName = FileName(chInstrumentId, 1);
	int nIndex = FindIndex(chInstrumentId);
	if (m_gDepthMarketData[nIndex].empty())
	{
		m_gDepthMarketData[nIndex].push_back(*pDepthMarketData);
		return;
	}
	tm tmCurrMd = GetDepthMarketDataTm(pDepthMarketData);
	tm tmPrevMd = GetDepthMarketDataTm(&m_gDepthMarketData[nIndex].back());

	if (tmCurrMd.tm_min != tmPrevMd.tm_min)
	{
		Bar* pBar = MdVecToBar(nIndex);
		BarToFile(chFileName, pBar);
		//ExecutionPeriodConverter(chInstrumentId);
		m_gDepthMarketData[nIndex].clear();
	}

	m_gDepthMarketData[nIndex].push_back(*pDepthMarketData);
}

BarManager::BarManager()
{
	string instrumentIds = getConfig("config", "InstrumentID");
	m_gchInstrumentIds.push_back(instrumentIds);
	m_gDepthMarketData.resize(m_gchInstrumentIds.size());
}

string BarManager::FileName(string chInstrumentId, int nTimePeriod = 1)
{
	string chFilePath = ".\\bars\\";
	return chFilePath + chInstrumentId + "_" + to_string(nTimePeriod) + ".csv";
}

void BarManager::BarToFile(string chFileName, Bar* pBar)
{
	m_Outfile.open(chFileName, ios::app);

	m_Outfile << pBar->year << ",";
	m_Outfile << pBar->month << ",";
	m_Outfile << pBar->day << ",";
	m_Outfile << pBar->hour << ",";
	m_Outfile << pBar->minute << ",";
	m_Outfile << pBar->open << ",";
	m_Outfile << pBar->high << ",";
	m_Outfile << pBar->low << ",";
	m_Outfile << pBar->close << ",";
	m_Outfile << pBar->volume << endl;

	m_Outfile.close();
}

int BarManager::FindIndex(string chInstrumentId)
{
	for (size_t i = 0; i < m_gchInstrumentIds.size(); i++)
	{
		if (m_gchInstrumentIds[i] == chInstrumentId)
		{
			return i;
		}
	}
	return -1;
}

tm BarManager::GetDepthMarketDataTm(CThostFtdcDepthMarketDataField* pDepthMarketData)
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

Bar* BarManager::MdVecToBar(int nVecIndex)
{
	static Bar bar;
	tm tmMd = GetDepthMarketDataTm(&m_gDepthMarketData[nVecIndex].back());
	bar.year = tmMd.tm_year;
	bar.month = tmMd.tm_mon;
	bar.day = tmMd.tm_yday;
	bar.hour = tmMd.tm_hour;
	bar.minute = tmMd.tm_min;
	bar.open = m_gDepthMarketData[nVecIndex].front().LastPrice;
	bar.close = m_gDepthMarketData[nVecIndex].back().LastPrice;
	bar.high = m_gDepthMarketData[nVecIndex].front().LastPrice;
	bar.low = m_gDepthMarketData[nVecIndex].front().LastPrice;

	for (size_t i = 0; i < m_gDepthMarketData[nVecIndex].size(); i++)
	{
		bar.high = m_gDepthMarketData[nVecIndex][i].LastPrice > bar.high ? m_gDepthMarketData[nVecIndex][i].LastPrice : bar.high;
		bar.low = m_gDepthMarketData[nVecIndex][i].LastPrice < bar.low ? m_gDepthMarketData[nVecIndex][i].LastPrice : bar.low;
	}

	return &bar;
}

void BarManager::PeriodConverter(string chInstrumentId, int nTimePeriod)
{
	int nPervTimePeriodIndex = GetPervTimePeriodIndex(nTimePeriod);
	int converTimePeriod = 1;
	if (nPervTimePeriodIndex >= 0)
	{
		int converTimePeriod = m_nTimePeriods[nPervTimePeriodIndex];
	}
	int nBarNum = nTimePeriod / converTimePeriod;
	vector<Bar> vecBars(nBarNum);
	int r = Bar::getBars(&vecBars, nBarNum, converTimePeriod, 0);

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

	string outFileName = FileName(chInstrumentId, nTimePeriod);
	BarToFile(outFileName, &bar);
}

void BarManager::ExecutionPeriodConverter(string chInstrumentId)
{
	int nIndex = FindIndex(chInstrumentId);
	vector<int> converPeriods = GetCurrentPeriodConverter(&m_gDepthMarketData[nIndex].back());
	for (size_t i = 0; i < converPeriods.size(); i++)
	{
		PeriodConverter(chInstrumentId, converPeriods[i]);
	}
}

vector<int> BarManager::GetCurrentPeriodConverter(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	static vector<int> periodVec;
	tm tmMd = GetDepthMarketDataTm(pDepthMarketData);
	int arrSize = sizeof(m_nTimePeriods) / sizeof(m_nTimePeriods[0]);
	for (size_t i = 0; i < arrSize; i++)
	{
		if (tmMd.tm_min % m_nTimePeriods[i] == 0)
		{
			periodVec.push_back(m_nTimePeriods[i]);
		}
	}
	return periodVec;
}

int BarManager::GetPervTimePeriodIndex(int nTimePeriod)
{
	int nIndex = -1;
	int arrSize = sizeof(m_nTimePeriods) / sizeof(m_nTimePeriods[0]);
	for (size_t i = 0; i < arrSize; i++)
	{
		if (m_nTimePeriods[i] == nTimePeriod)
		{
			nIndex = i - 1;
		}
	}
	return nIndex;
}


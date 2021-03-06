#pragma once
#include "getconfig.h"
#include "ThostFtdcUserApiStruct.h"
#include <algorithm>
#include <fstream>
#include "bar_class.h"
#include "subject_class.h"
#include "observer_class.h"
#include <vector>

using namespace std;

class BarManager : public Subject, public Observer
{
public:
	void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		string chInstrumentId = pDepthMarketData->InstrumentID;
		string chFileName = FileName(chInstrumentId, 1);
		size_t nIndex = FindIndex(chInstrumentId);
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
			ExecutionPeriodConverter(chInstrumentId);
			m_gDepthMarketData[nIndex].clear();
		}

		m_gDepthMarketData[nIndex].push_back(*pDepthMarketData);
	}
	void update()
	{
		if (subject->SubjectState() == 1)
		{
			OnTick(&subject->SubjectTick());
		}
	}

	BarManager(Subject* sub) : Observer(sub)
	{
		string instrumentIds = getConfig("config", "InstrumentID");
		m_gchInstrumentIds.push_back(instrumentIds);
		m_gDepthMarketData.resize(m_gchInstrumentIds.size());
	}
private:
	string FileName(string chInstrumentId, int nTimePeriod = 1)
	{
		string chFilePath = ".\\bars\\";
		return chFilePath + chInstrumentId + "_" + to_string(nTimePeriod) + ".csv";
	}
	void BarToFile(string chFileName, Bar* pBar)
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
	size_t FindIndex(string chInstrumentId)
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
	tm GetDepthMarketDataTm(CThostFtdcDepthMarketDataField* pDepthMarketData)
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
	Bar* MdVecToBar(size_t nVecIndex)
	{
		static Bar bar;
		tm tmMd = GetDepthMarketDataTm(&m_gDepthMarketData[nVecIndex].back());
		bar.year = tmMd.tm_year + 1900;
		bar.month = tmMd.tm_mon + 1;
		bar.day = tmMd.tm_mday;
		bar.hour = tmMd.tm_hour;
		bar.minute = tmMd.tm_min;
		bar.open = m_gDepthMarketData[nVecIndex].front().LastPrice;
		bar.close = m_gDepthMarketData[nVecIndex].back().LastPrice;
		bar.high = m_gDepthMarketData[nVecIndex].front().LastPrice;
		bar.low = m_gDepthMarketData[nVecIndex].front().LastPrice;
		bar.volume = m_gDepthMarketData[nVecIndex].back().Volume - m_gDepthMarketData[nVecIndex].front().Volume;

		for (size_t i = 0; i < m_gDepthMarketData[nVecIndex].size(); i++)
		{
			bar.high = m_gDepthMarketData[nVecIndex][i].LastPrice > bar.high ? m_gDepthMarketData[nVecIndex][i].LastPrice : bar.high;
			bar.low = m_gDepthMarketData[nVecIndex][i].LastPrice < bar.low ? m_gDepthMarketData[nVecIndex][i].LastPrice : bar.low;
		}

		return &bar;
	}
	void PeriodConverter(string chInstrumentId, size_t nTimePeriod)
	{
		size_t nConverTimePeriod = GetPervTimePeriod(nTimePeriod);
		int nBarNum = nTimePeriod / nConverTimePeriod;
		vector<Bar> vecBars;
		int r = Bar::getBars(&vecBars, chInstrumentId, nBarNum, nConverTimePeriod, 0);

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
		bar.volume = 0;
		bar.timeperiod = nTimePeriod;

		for (size_t i = 0; i < vecBars.size(); i++)
		{
			bar.high = bar.high < vecBars[i].high ? vecBars[i].high : bar.high;
			bar.low = bar.low > vecBars[i].low ? vecBars[i].low : bar.low;
			bar.volume += vecBars[i].volume;
		}

		string outFileName = FileName(chInstrumentId, nTimePeriod);
		BarToFile(outFileName, &bar);

		//??????bar
		subject->SubjectBar(&bar);

		//int nIndex = FindIndex(chInstrumentId);
		//m_pStrategy->OnBar(&bar, &m_gDepthMarketData[nIndex].back(), nTimePeriod);
	}
	void ExecutionPeriodConverter(string chInstrumentId)
	{
		size_t nIndex = FindIndex(chInstrumentId);
		vector<int> gnConverTimePeriods;
		GetCurrentPeriodConverter(&m_gDepthMarketData[nIndex].back(), &gnConverTimePeriods);

		if (gnConverTimePeriods.size() > 0)
		{
			tm bTm = GetDepthMarketDataTm(&m_gDepthMarketData[nIndex].back());
		}

		for (size_t i = 0; i < gnConverTimePeriods.size(); i++)
		{
			PeriodConverter(chInstrumentId, gnConverTimePeriods[i]);
		}
	}
	size_t GetCurrentPeriodConverter(CThostFtdcDepthMarketDataField* pDepthMarketData, vector<int>* gnConverTimePeriods)
	{
		tm tmMd = GetDepthMarketDataTm(pDepthMarketData);
		int minute = tmMd.tm_min + 1;
		int arrSize = sizeof(m_nTimePeriods) / sizeof(m_nTimePeriods[0]);
		for (size_t i = 0; i < arrSize; i++)
		{
			if (minute % m_nTimePeriods[i] == 0)
			{
				gnConverTimePeriods->push_back(m_nTimePeriods[i]);
			}
		}
		return gnConverTimePeriods->size();
	}

	size_t GetPervTimePeriod(size_t nTimePeriod)
	{
		size_t nPervTimePeriod = 1;
		if (nTimePeriod == 1)
		{
			return 1;
		}
		size_t nSize = sizeof(m_nTimePeriods) / sizeof(m_nTimePeriods[0]);
		for (size_t i = 0; i < nSize; i++)
		{
			if (i == 0)
			{
				return 1;
			}
			else if (m_nTimePeriods[i] == nTimePeriod)
			{
				nPervTimePeriod = m_nTimePeriods[i - 1];
			}
		}
		return nPervTimePeriod > 1 ? nPervTimePeriod : 1;
	}
	vector<string> m_gchInstrumentIds;
	vector<vector<CThostFtdcDepthMarketDataField> > m_gDepthMarketData;
	ofstream m_Outfile;
	const int m_nTimePeriods[4] = { 5,15,30,60 };
};

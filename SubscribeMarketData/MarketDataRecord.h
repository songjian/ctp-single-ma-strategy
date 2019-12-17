#pragma once
#include "..\Common\ThostFtdcUserApiStruct.h"
#include <fstream>

using namespace std;

class MarketDataRecord
{
public:
	MarketDataRecord() {};
	~MarketDataRecord()
	{
		if (outfile.is_open())
		{
			outfile.close();
		}
	};
	void update(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		MdToFile(pDepthMarketData);
	};
private:
	void MdToFile(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		string fileName = FileName(pDepthMarketData);
		if (fileName != lastFileName)
		{
			lastFileName = fileName;
			if (outfile.is_open())
			{
				outfile.close();
			}
			outfile.open(fileName, ios::app);
		}
		outfile << pDepthMarketData->TradingDay << ",";
		outfile << pDepthMarketData->ActionDay << ",";
		outfile << pDepthMarketData->UpdateTime << ",";
		outfile << pDepthMarketData->UpdateMillisec << ",";
		outfile << pDepthMarketData->ExchangeID << ",";
		outfile << pDepthMarketData->InstrumentID << ",";
		outfile << pDepthMarketData->OpenPrice << ",";
		outfile << pDepthMarketData->HighestPrice << ",";
		outfile << pDepthMarketData->LowestPrice << ",";
		outfile << pDepthMarketData->ClosePrice << ",";
		outfile << pDepthMarketData->LastPrice << ",";
		outfile << pDepthMarketData->Volume << ",";
		outfile << pDepthMarketData->Turnover << endl;
	};
	string FileName(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		string filePath = ".\\md\\";
		string day = pDepthMarketData->ActionDay;
		string instrument = pDepthMarketData->InstrumentID;
		return filePath + instrument + "_" + day + ".csv";
	};
	string lastFileName;
	ofstream outfile;
};
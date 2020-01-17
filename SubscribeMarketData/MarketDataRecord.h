#pragma once
#include "ThostFtdcUserApiStruct.h"
#include <fstream>
#include <assert.h>

using namespace std;

class MarketDataRecord
{
public:
	MarketDataRecord() {};
	~MarketDataRecord() {};
	void update(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		MdToFile(pDepthMarketData);
	};
private:
	void MdToFile(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		string fileName = FileName(pDepthMarketData);
		// ����ļ��Ƿ����
		ifstream infile(fileName);
		bool fileExist = !infile ? false : true;  // ����ļ��Ƿ����
		infile.close();

		// ׷��д���¼
		ofstream outfile(fileName, ios::app);

		// ���ļ�д�������
		if (!fileExist)
		{
			outfile
				<< "TradingDay" << ','
				<< "UpdateTime" << ','
				<< "ExchangeID" << ','
				<< "InstrumentID" << ','
				<< "OpenPrice" << ','
				<< "HighestPrice" << ','
				<< "LowestPrice" << ','
				<< "ClosePrice" << ','
				<< "LastPrice" << ','
				<< "Volume" << ','
				<< "Turnover" << endl;
		}

		outfile
			<< pDepthMarketData->TradingDay << ','
			<< pDepthMarketData->UpdateTime << '.' << pDepthMarketData->UpdateMillisec << ','
			<< pDepthMarketData->ExchangeID << ','
			<< pDepthMarketData->InstrumentID << ','
			<< pDepthMarketData->OpenPrice << ','
			<< pDepthMarketData->HighestPrice << ','
			<< pDepthMarketData->LowestPrice << ','
			<< pDepthMarketData->ClosePrice << ','
			<< pDepthMarketData->LastPrice << ','
			<< pDepthMarketData->Volume << ','
			<< pDepthMarketData->Turnover << endl;

		outfile.close();
	};
	string FileName(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		string filePath = ".\\md\\";
		string day = pDepthMarketData->TradingDay;
		string instrument = pDepthMarketData->InstrumentID;
		return filePath + instrument + "_" + day + ".csv";
	};
};
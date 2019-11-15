#include "stdafx.h"
#include "MarketData.h"

void MarketData::OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	MdToFile(pDepthMarketData);
	m_pBarManager->OnTick(pDepthMarketData);
}

MarketData::MarketData()
{
	m_pBarManager = BarManager::CreateBarManager();
}

MarketData::~MarketData()
{
	if (outfile.is_open())
	{
		outfile.close();
	}
}

void MarketData::MdToFile(CThostFtdcDepthMarketDataField* pDepthMarketData)
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
}

string MarketData::FileName(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	string filePath = ".\\md\\";
	string day = pDepthMarketData->ActionDay;
	string instrument = pDepthMarketData->InstrumentID;
	return filePath + instrument + "_" + day + ".csv";
}

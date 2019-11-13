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
	outfile << pDepthMarketData->TradingDay << "," << pDepthMarketData->ActionDay << "," << pDepthMarketData->UpdateTime << "," << pDepthMarketData->UpdateMillisec << "," << pDepthMarketData->ExchangeID << "," << pDepthMarketData->InstrumentID << "," << pDepthMarketData->OpenPrice << "," << pDepthMarketData->HighestPrice << "," << pDepthMarketData->LowestPrice << "," << pDepthMarketData->ClosePrice << "," << pDepthMarketData->LastPrice << "," << pDepthMarketData->Volume << "," << pDepthMarketData->Turnover << endl;
}

string MarketData::FileName(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	string filePath = ".\\md\\";
	string day = pDepthMarketData->ActionDay;
	string instrument = pDepthMarketData->InstrumentID;
	return filePath + instrument + "_" + day + ".csv";
}

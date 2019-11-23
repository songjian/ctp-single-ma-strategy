#include "stdafx.h"
#include "market_data_writer_class.h"

void MarketDataWriter::OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	MdToFile(pDepthMarketData);
	m_pBarManager->OnTick(pDepthMarketData);
}

MarketDataWriter::~MarketDataWriter()
{
	if (outfile.is_open())
	{
		outfile.close();
	}
}

void MarketDataWriter::MdToFile(CThostFtdcDepthMarketDataField* pDepthMarketData)
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

string MarketDataWriter::FileName(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	string filePath = ".\\md\\";
	string day = pDepthMarketData->ActionDay;
	string instrument = pDepthMarketData->InstrumentID;
	return filePath + instrument + "_" + day + ".csv";
}

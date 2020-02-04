#pragma once
#include "CustomMdHandler.h"
#include <fstream>
#include <cassert>

class CMdHandler : public CCustomMdHandler
{
public:
	CMdHandler(CThostFtdcMdApi* pUserMdApi) : CCustomMdHandler(pUserMdApi)
	{};

	///深度行情通知
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		//写入文件
		MdToFile(pDepthMarketData);

		//输出信息
		cout
			<< "接收行情," << pDepthMarketData->InstrumentID
			<< ',' << pDepthMarketData->LastPrice
			<< endl;
	}

private:
	//市场深度数据写入文件
	void MdToFile(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		using namespace std;

		//dmd字段不能为空
		assert(pDepthMarketData->InstrumentID != '\0');
		assert(pDepthMarketData->TradingDay != '\0');

		// 追加写入记录
		ofstream outfile(FilePath(pDepthMarketData), ios::app);

		// 写入数据
		outfile
			<< pDepthMarketData->TradingDay << ','
			<< pDepthMarketData->ActionDay << ','
			<< pDepthMarketData->UpdateTime << ','
			<< pDepthMarketData->UpdateMillisec << ','
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

	// 取得输出文件路径
	string FilePath(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		return chDmdDir
			+ pDepthMarketData->InstrumentID
			+ '_'
			+ pDepthMarketData->TradingDay
			+ ".csv";
	};

private:
	//深度市场数据存储目录
	string chDmdDir = "./data/dmd/";
};


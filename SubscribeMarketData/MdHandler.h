#pragma once
#include "CustomMdHandler.h"
#include <fstream>
#include <cassert>

class CMdHandler : public CCustomMdHandler
{
public:
	CMdHandler(CThostFtdcMdApi* pUserMdApi) : CCustomMdHandler(pUserMdApi)
	{};

	///�������֪ͨ
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		//д���ļ�
		MdToFile(pDepthMarketData);

		//�����Ϣ
		cout
			<< "��������," << pDepthMarketData->InstrumentID
			<< ',' << pDepthMarketData->LastPrice
			<< endl;
	}

private:
	//�г��������д���ļ�
	void MdToFile(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		using namespace std;

		//dmd�ֶβ���Ϊ��
		assert(pDepthMarketData->InstrumentID != '\0');
		assert(pDepthMarketData->TradingDay != '\0');

		// ׷��д���¼
		ofstream outfile(FilePath(pDepthMarketData), ios::app);

		// д������
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

	// ȡ������ļ�·��
	string FilePath(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		return chDmdDir
			+ pDepthMarketData->InstrumentID
			+ '_'
			+ pDepthMarketData->TradingDay
			+ ".csv";
	};

private:
	//����г����ݴ洢Ŀ¼
	string chDmdDir = "./data/dmd/";
};


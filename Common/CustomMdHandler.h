#pragma once
#include "ThostFtdcMdApi.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

extern HANDLE g_hEvent;
extern vector<string> md_InstrumentID;
class CCustomMdHandler : public CThostFtdcMdSpi
{
public:
	CCustomMdHandler(CThostFtdcMdApi* pUserMdApi) : m_pUserMdApi(pUserMdApi)
	{
	};
	void OnFrontConnected()
	{
		ReqUserLogin();
	};
	void ReqUserLogin()
	{
		CThostFtdcReqUserLoginField a;
		int num = m_pUserMdApi->ReqUserLogin(&a, 0);
	};
	void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin,
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo->ErrorID != 0) {
			// �˵�ʧ�ܣ��ͻ�������д�����
			exit(-1);
		}
		printf("��¼�ɹ�\n");

		//��������
		SubscribeMarketData();
	};

	///��������
	void SubscribeMarketData()
	{
		int md_num = 0;
		char** ppInstrumentID = new char* [5000];
		for (int count1 = 0; count1 <= md_InstrumentID.size() / 500; count1++)
		{
			if (count1 < md_InstrumentID.size() / 500)
			{
				int a = 0;
				for (a; a < 500; a++)
				{
					ppInstrumentID[a] = const_cast<char*>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = m_pUserMdApi->SubscribeMarketData(ppInstrumentID, a);
				//LOG((result == 0) ? "������������1......���ͳɹ�\n" : "������������1......����ʧ�ܣ��������=[%d]\n", result);
			}
			else if (count1 == md_InstrumentID.size() / 500)
			{
				int count2 = 0;
				for (count2; count2 < md_InstrumentID.size() % 500; count2++)
				{
					ppInstrumentID[count2] = const_cast<char*>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = m_pUserMdApi->SubscribeMarketData(ppInstrumentID, count2);
				//LOG((result == 0) ? "������������2......���ͳɹ�\n" : "������������2......����ʧ�ܣ��������=[%d]\n", result);
			}
		}
	};

	///��������Ӧ��
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
	};

	///�������֪ͨ
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
	};
protected:
	CThostFtdcMdApi* m_pUserMdApi;
};


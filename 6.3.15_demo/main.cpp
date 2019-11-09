#include "stdafx.h"
#include "main.h"

/*
int main()
{
	logfile = fopen("syslog.txt", "w");
	mdfile = fopen(".\\mdfile\\md.csv", "a");
	string InstrumentID = getConfig("config", "InstrumentID");
	strcpy_s(g_chInstrumentID, const_cast<char*>(InstrumentID.c_str()));
	string g_chFrontaddr = getConfig("config", "FrontAddr");
	CTraderApi* pUserApi = new CTraderApi();
	pUserApi->CreateFtdcTraderApi(".\\flow\\");
	CSimpleHandler sh(pUserApi);
	pUserApi->RegisterSpi(&sh);
	pUserApi->SubscribePublicTopic(THOST_TERT_QUICK);
	pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK);
	pUserApi->RegisterFront(const_cast<char*>(g_chFrontaddr.c_str()));
	pUserApi->Init();
	WaitForSingleObject(g_hEvent, INFINITE);

	sh.ReqAuthenticate();
	WaitForSingleObject(g_hEvent, INFINITE);
	sh.ReqUserLogin();
	WaitForSingleObject(g_hEvent, INFINITE);

	//结算单确认请求
	sh.ReqSettlementInfoConfirm();
	WaitForSingleObject(g_hEvent, INFINITE);

	string g_chFrontMdaddr = getConfig("config", "FrontMdAddr");
	CThostFtdcMdApi* pUserMdApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\flow\\md\\");
	CSimpleMdHandler ash(pUserMdApi);
	pUserMdApi->RegisterSpi(&ash);
	pUserMdApi->RegisterFront(const_cast<char*>(g_chFrontMdaddr.c_str()));
	pUserMdApi->Init();
	WaitForSingleObject(xinhao, INFINITE);
	sh.ReqQryInstrument();
	WaitForSingleObject(xinhao, INFINITE);
	ash.SubscribeMarketData();
	WaitForSingleObject(xinhao, INFINITE);
	pUserMdApi->Release();
	return 0;
}
*/

int main()
{
	printf("程序开始。\n");
	Bar::getBars(1, 10);
}
#include "stdafx.h"
#include "main.h"

int main()
{
	CGetInstrumentID::ReadInstrumentID();

	CThostFtdcMdApi* pUserMdApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\flow\\SubscribeMarketData\\md\\");
	CMdHandler spi(pUserMdApi);
	pUserMdApi->RegisterSpi(&spi);
	string chTcpAddress = "tcp://180.168.146.187:10110";
	pUserMdApi->RegisterFront(const_cast<char*>(chTcpAddress.c_str()));
	pUserMdApi->Init();
	pUserMdApi->Join();
	return 0;
}
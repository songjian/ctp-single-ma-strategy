#include "stdafx.h"
#include "singleMaStrategy.h"

void SingleMaStrategy::OnStart()
{
	double ma = indicators.ma(instrumentId, period, timePeriod, 1);

	if (ma == 0)
	{
		printf("数据不足，请不要关闭软件，等待数据接收完毕后程序开始执行。\n");
	}
	else
	{
		printf("ma值%.8lf\n", ma);
	}
};

void SingleMaStrategy::OnStop()
{
};

void SingleMaStrategy::OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
};

void SingleMaStrategy::OnBar()
{
};

SingleMaStrategy::SingleMaStrategy(TThostFtdcInstrumentIDType InstrumentId)
{
	strcpy(instrumentId, InstrumentId);
};
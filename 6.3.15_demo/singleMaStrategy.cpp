#include "stdafx.h"
#include "singleMaStrategy.h"

void SingleMaStrategy::OnStart()
{
	double ma = indicators.ma(instrumentId, period, timePeriod, 1);

	if (ma == 0)
	{
		printf("���ݲ��㣬�벻Ҫ�ر�������ȴ����ݽ�����Ϻ����ʼִ�С�\n");
	}
	else
	{
		printf("maֵ%.8lf\n", ma);
	}
};

void SingleMaStrategy::OnStop()
{
};

void SingleMaStrategy::OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	printf("���Գɹ����յ�Tick���ݡ�\n");
};

void SingleMaStrategy::OnBar()
{
};

SingleMaStrategy::SingleMaStrategy(TThostFtdcInstrumentIDType InstrumentId)
{
	strcpy(instrumentId, InstrumentId);
};
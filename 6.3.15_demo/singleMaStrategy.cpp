#include "stdafx.h"
#include "singleMaStrategy.h"

void SingleMaStrategy::OnStart()
{
};

void SingleMaStrategy::OnStop()
{
};

void SingleMaStrategy::OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	double fPrice = pDepthMarketData->LastPrice;
	double fMa = m_Indicators.ma(m_InstrumentId, m_nPeriod, m_nTimePeriod, 0);
	if (fMa == 0)
	{
		printf("���ݲ��㣬�벻Ҫ�ر�������ȴ����ݽ�����Ϻ����ʼִ�С�\n");
		return;
	}

	if (fPrice > fMa)
	{

	}
};

void SingleMaStrategy::OnBar(CThostFtdcDepthMarketDataField* pDepthMarketData, size_t nTimePeriod)
{
	printf("��Bar�� ʱ�����ڣ�%zd\n", nTimePeriod);
}

int SingleMaStrategy::OpenPosition(TThostFtdcDirectionType cDirection, double fLimitPrice)
{
	CThostFtdcInputOrderField ord = { 0 };
	strcpy_s(ord.BrokerID, getConfig("config", "BrokerID").c_str());
	strcpy_s(ord.InvestorID, getConfig("config", "InvestorID").c_str());
	strcpy_s(ord.InstrumentID, m_InstrumentId);
	strcpy_s(ord.UserID, getConfig("config", "UserID").c_str());
	strcpy_s(ord.ExchangeID, getConfig("config", "ExchangeID").c_str());
	ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	ord.Direction = cDirection;
	strcpy_s(ord.CombHedgeFlag, "1");
	//ord.LimitPrice = atoi(getConfig("config", "LimitPrice").c_str());
	ord.LimitPrice = fLimitPrice;
	ord.VolumeTotalOriginal = 1;
	ord.TimeCondition = THOST_FTDC_TC_GFD;///������Ч
	ord.VolumeCondition = THOST_FTDC_VC_CV;///ȫ������
	ord.MinVolume = 1;
	ord.ContingentCondition = THOST_FTDC_CC_Immediately;
	ord.StopPrice = 0;
	ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	ord.IsAutoSuspend = 0;
	int a = m_pUserApi->ReqOrderInsert(&ord, 1);
	return 0;
}
;
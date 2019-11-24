#include <string.h>
#include "stdafx.h"
#include "single_ma_strategy_class.h"

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
		printf("数据不足，请不要关闭软件，等待数据接收完毕后程序开始执行。\n");
		return;
	}

	if (fPrice > fMa)
	{

	}
};

void SingleMaStrategy::OnMessage(){};
void SingleMaStrategy::OnAccount(){};

void SingleMaStrategy::OnBar(CThostFtdcDepthMarketDataField* pDepthMarketData, size_t nTimePeriod)
{
	printf("新Bar！ 时间周期：%zd\n", nTimePeriod);
}

int SingleMaStrategy::OpenPosition(TThostFtdcDirectionType cDirection, double fLimitPrice)
{
	CThostFtdcInputOrderField ord = { 0 };
	strcpy_s(ord.BrokerID, getConfig("config", "BrokerID").c_str());
	strcpy_s(ord.InvestorID, getConfig("config", "InvestorID").c_str());
	strcpy_s(ord.InstrumentID, m_InstrumentId.c_str());
	strcpy_s(ord.UserID, getConfig("config", "UserID").c_str());
	strcpy_s(ord.ExchangeID, getConfig("config", "ExchangeID").c_str());
	ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	ord.Direction = cDirection;
	strcpy_s(ord.CombHedgeFlag, "1");
	//ord.LimitPrice = atoi(getConfig("config", "LimitPrice").c_str());
	ord.LimitPrice = fLimitPrice;
	ord.VolumeTotalOriginal = 1;
	ord.TimeCondition = THOST_FTDC_TC_GFD;///当日有效
	ord.VolumeCondition = THOST_FTDC_VC_CV;///全部数量
	ord.MinVolume = 1;
	ord.ContingentCondition = THOST_FTDC_CC_Immediately;
	ord.StopPrice = 0;
	ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	ord.IsAutoSuspend = 0;
	int a = m_pUserApi->ReqOrderInsert(&ord, 1);
	return 0;
}
;
#pragma once
#include "define.h"
#include "getconfig.h"
#include "ThostFtdcUserApiStruct.h"
#include "strategy_class.h"
#include "indicators_class.h"

extern int nRequestID;

class SingleMaStrategy : public Strategy
{
public:
	virtual void OnStart() {}
	virtual void OnStop() {}
	virtual void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		m_pLastTick = pDepthMarketData;
	}
	virtual void OnBar(Bar* pBar)
	{
		//调试
		printf("买入价格：%lf\n", pBar->close);
		printf("LowerLimitPrice：%lf\n", m_pLastTick->LowerLimitPrice);
		printf("nRequestID：%d\n", nRequestID);
		//测试创建订单
		OrderInsert(THOST_FTDC_D_Buy, m_pLastTick->LowerLimitPrice);
		/*
		printf("新Bar！ 时间周期：%zd\n", pBar->timeperiod);
		double ma = Indicators::ma(m_chInstrumentId, m_nPeriod, m_nTimePeriod, 0);
		printf("ma: %lf", ma);
		if (ma > pBar->close)
		{
			// 卖出
			OpenPosition(THOST_FTDC_D_Sell, pBar->close);
		} 
		else
		{
			// 买入
			OpenPosition(THOST_FTDC_D_Buy, pBar->close);
		}*/
	};
	virtual void OnMessage()
	{
		printf("订单信息---------------------\n");
	}

	virtual void OnAccount()
	{}
	SingleMaStrategy(CThostFtdcTraderApi* pUserApi, Subject* sub) : Strategy(sub), m_pUserApi(pUserApi) {}
	~SingleMaStrategy(){};
	void Check()
	{
		/*
		double fPrice = pDepthMarketData->LastPrice;
		double fMa = m_Indicators.ma(m_chInstrumentId, m_nPeriod, m_nTimePeriod, 0);
		if (fMa == 0)
		{
			printf("数据不足，请不要关闭软件，等待数据接收完毕后程序开始执行。\n");
			return;
		}

		if (fPrice > fMa)
		{

		}
		*/
	}
private:
	// 插入订单
	void OrderInsert(TThostFtdcDirectionType cDirection, double fLimitPrice)
	{
		debug_OrderInsert();
		/*CThostFtdcInputOrderField ord = { 0 };
		ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		ord.Direction = cDirection; //买卖方向
		ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open; //开平方向
		ord.LimitPrice = fLimitPrice;
		ord.VolumeTotalOriginal = 1; //数量
		ord.TimeCondition = THOST_FTDC_TC_GFD;//当日有效
		ord.VolumeCondition = THOST_FTDC_VC_CV;//成交量类型：全部数量
		ord.MinVolume = 1;
		ord.ContingentCondition = THOST_FTDC_CC_Immediately;//触发条件：立即
		ord.StopPrice = 0;//止损价
		ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;//强平原因：非强平
		ord.IsAutoSuspend = 0;//自动挂起标志
		ord.RequestID = nRequestID;
		strcpy_s(ord.CombHedgeFlag, "1");
		strcpy_s(ord.BrokerID, getConfig("config", "BrokerID").c_str());
		strcpy_s(ord.InvestorID, getConfig("config", "InvestorID").c_str());
		strcpy_s(ord.InstrumentID, m_chInstrumentId);
		strcpy_s(ord.UserID, getConfig("config", "UserID").c_str());
		strcpy_s(ord.ExchangeID, getConfig("config", "ExchangeID").c_str());
		int a = m_pUserApi->ReqOrderInsert(&ord, nRequestID++);
		printf("订单返回值:%d\n", a);*/
	}
	void debug_OrderInsert()
	{
		CThostFtdcInputExecOrderField OrderInsert = { 0 };
		strcpy_s(OrderInsert.BrokerID, "9999");
		strcpy_s(OrderInsert.InvestorID, "153183");
		strcpy_s(OrderInsert.InstrumentID, "rb2008");
		strcpy_s(OrderInsert.ExchangeID, "SHFE");
		strcpy_s(OrderInsert.ExecOrderRef, "00001");
		strcpy_s(OrderInsert.UserID, "153183");
		OrderInsert.Volume = 1;
		OrderInsert.RequestID = 1;
		OrderInsert.OffsetFlag = THOST_FTDC_OF_Close;//开平标志
		OrderInsert.HedgeFlag = THOST_FTDC_HF_Speculation;//投机套保标志
		OrderInsert.ActionType = THOST_FTDC_ACTP_Exec;//执行类型类型
		OrderInsert.PosiDirection = THOST_FTDC_PD_Long;//持仓多空方向类型
		OrderInsert.ReservePositionFlag = THOST_FTDC_EOPF_Reserve;//期权行权后是否保留期货头寸的标记类型
		OrderInsert.CloseFlag = THOST_FTDC_EOCF_NotToClose;//期权行权后生成的头寸是否自动平仓类型
		m_pUserApi->ReqExecOrderInsert(&OrderInsert, nRequestID++);
	}
	int m_nPeriod = 10;
	int m_nTimePeriod = 15;
	TThostFtdcInstrumentIDType m_chInstrumentId = "m2009";
	TThostFtdcOrderSysIDType m_chOrderSysID;
	CThostFtdcOrderField* m_pOrder;
	CThostFtdcTraderApi* m_pUserApi;
	CThostFtdcDepthMarketDataField* m_pLastTick;
};


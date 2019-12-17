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
		//����
		printf("����۸�%lf\n", pBar->close);
		printf("LowerLimitPrice��%lf\n", m_pLastTick->LowerLimitPrice);
		printf("nRequestID��%d\n", nRequestID);
		//���Դ�������
		OrderInsert(THOST_FTDC_D_Buy, m_pLastTick->LowerLimitPrice);
		/*
		printf("��Bar�� ʱ�����ڣ�%zd\n", pBar->timeperiod);
		double ma = Indicators::ma(m_chInstrumentId, m_nPeriod, m_nTimePeriod, 0);
		printf("ma: %lf", ma);
		if (ma > pBar->close)
		{
			// ����
			OpenPosition(THOST_FTDC_D_Sell, pBar->close);
		} 
		else
		{
			// ����
			OpenPosition(THOST_FTDC_D_Buy, pBar->close);
		}*/
	};
	virtual void OnMessage()
	{
		printf("������Ϣ---------------------\n");
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
			printf("���ݲ��㣬�벻Ҫ�ر�������ȴ����ݽ�����Ϻ����ʼִ�С�\n");
			return;
		}

		if (fPrice > fMa)
		{

		}
		*/
	}
private:
	// ���붩��
	void OrderInsert(TThostFtdcDirectionType cDirection, double fLimitPrice)
	{
		debug_OrderInsert();
		/*CThostFtdcInputOrderField ord = { 0 };
		ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		ord.Direction = cDirection; //��������
		ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open; //��ƽ����
		ord.LimitPrice = fLimitPrice;
		ord.VolumeTotalOriginal = 1; //����
		ord.TimeCondition = THOST_FTDC_TC_GFD;//������Ч
		ord.VolumeCondition = THOST_FTDC_VC_CV;//�ɽ������ͣ�ȫ������
		ord.MinVolume = 1;
		ord.ContingentCondition = THOST_FTDC_CC_Immediately;//��������������
		ord.StopPrice = 0;//ֹ���
		ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;//ǿƽԭ�򣺷�ǿƽ
		ord.IsAutoSuspend = 0;//�Զ������־
		ord.RequestID = nRequestID;
		strcpy_s(ord.CombHedgeFlag, "1");
		strcpy_s(ord.BrokerID, getConfig("config", "BrokerID").c_str());
		strcpy_s(ord.InvestorID, getConfig("config", "InvestorID").c_str());
		strcpy_s(ord.InstrumentID, m_chInstrumentId);
		strcpy_s(ord.UserID, getConfig("config", "UserID").c_str());
		strcpy_s(ord.ExchangeID, getConfig("config", "ExchangeID").c_str());
		int a = m_pUserApi->ReqOrderInsert(&ord, nRequestID++);
		printf("��������ֵ:%d\n", a);*/
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
		OrderInsert.OffsetFlag = THOST_FTDC_OF_Close;//��ƽ��־
		OrderInsert.HedgeFlag = THOST_FTDC_HF_Speculation;//Ͷ���ױ���־
		OrderInsert.ActionType = THOST_FTDC_ACTP_Exec;//ִ����������
		OrderInsert.PosiDirection = THOST_FTDC_PD_Long;//�ֲֶ�շ�������
		OrderInsert.ReservePositionFlag = THOST_FTDC_EOPF_Reserve;//��Ȩ��Ȩ���Ƿ����ڻ�ͷ��ı������
		OrderInsert.CloseFlag = THOST_FTDC_EOCF_NotToClose;//��Ȩ��Ȩ�����ɵ�ͷ���Ƿ��Զ�ƽ������
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


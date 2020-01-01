#pragma once
#include "ThostFtdcTraderApi.h"
#include <string.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "getconfig.h"

extern TThostFtdcBrokerIDType g_chBrokerID;
extern TThostFtdcUserIDType g_chUserID;
extern TThostFtdcPasswordType g_chPassword;
extern TThostFtdcAuthCodeType g_chAuthCode; //认证码
extern TThostFtdcAppIDType g_chAppID; //App代码
extern int FrontID;
extern int SessionID;
extern int nRequestID;
extern HANDLE g_hEvent;

class CCustomTraderHandler : public CThostFtdcTraderSpi
{
public:
	CCustomTraderHandler(CThostFtdcTraderApi* pUserApi) : m_pUserApi(pUserApi)
	{
	};
	void OnFrontConnected()
	{
		//读配置文件
		strcpy_s(g_chBrokerID, getConfig("config", "BrokerID").c_str());
		strcpy_s(g_chUserID, getConfig("config", "UserID").c_str());
		strcpy_s(g_chPassword, getConfig("config", "Password").c_str());

		ReqAuthenticate();
		WaitForSingleObject(g_hEvent, INFINITE);
		ReqUserLogin();
		WaitForSingleObject(g_hEvent, INFINITE);
		ReqSettlementInfoConfirm();
		WaitForSingleObject(g_hEvent, INFINITE);
		cout << "前置地址连接成功" << endl;
	};
	void ReqAuthenticate()
	{
		//strcpy_s(g_chUserProductInfo, getConfig("config", "UserProductInfo").c_str());
		strcpy_s(g_chAuthCode, getConfig("config", "AuthCode").c_str());
		strcpy_s(g_chAppID, getConfig("config", "AppID").c_str());

		CThostFtdcReqAuthenticateField a = { 0 };
		strcpy_s(a.BrokerID, g_chBrokerID);
		strcpy_s(a.UserID, g_chUserID);
		//strcpy_s(a.UserProductInfo, "");
		strcpy_s(a.AuthCode, g_chAuthCode);
		strcpy_s(a.AppID, g_chAppID);
		int b = m_pUserApi->ReqAuthenticate(&a, 1);
		printf("\t客户端认证 = [%d]\n", b);
	}
	//客户端认证相应
	void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo,
		int nRequestID, bool bIsLast)
	{
		cout << "客户端认证成功" << endl;
		SetEvent(g_hEvent);
	}
	void ReqUserLogin()
	{
		CThostFtdcReqUserLoginField reqUserLogin = { 0 };
		strcpy_s(reqUserLogin.BrokerID, g_chBrokerID);
		strcpy_s(reqUserLogin.UserID, g_chUserID);
		strcpy_s(reqUserLogin.Password, g_chPassword);
		int r = m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
	};
	void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin,
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		FrontID = pRspUserLogin->FrontID;
		SessionID = pRspUserLogin->SessionID;
		if (pRspInfo->ErrorID != 0)
		{
			printf("登录错误,代码:%d,信息:%s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			//exit(-1);
		}
		cout << "用户登录成功" << endl;
		SetEvent(g_hEvent);
	};

	///请求确认结算单
	void ReqSettlementInfoConfirm()
	{
		CThostFtdcSettlementInfoConfirmField Confirm = { 0 };
		///经纪公司代码
		strcpy_s(Confirm.BrokerID, g_chBrokerID);
		///投资者代码
		strcpy_s(Confirm.InvestorID, g_chUserID);
		m_pUserApi->ReqSettlementInfoConfirm(&Confirm, nRequestID++);
	}

	///投资者结算结果确认响应
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm,
		CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		SetEvent(g_hEvent);
	}
protected:
	CThostFtdcTraderApi* m_pUserApi;
};


#pragma once
#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcTraderApi.h"
#include "subject_class.h"
#include "observer_class.h"

class Observer;
class Bar;

using namespace std;

class Strategy : public Observer
{
public:
	Strategy(Subject* sub) : Observer(sub) {}
	void update()
	{
		switch (subject->SubjectState())
		{
		case 1:
			OnTick(&subject->SubjectTick());
			break;
		case 2:
			OnBar(&subject->SubjectBar());
			break;
		case 3:
			OnMessage();
			break;
		default:
			break;
		}
	}
	virtual void OnStart() = 0;
	virtual void OnStop() = 0;
	virtual void OnTick(CThostFtdcDepthMarketDataField* pDepthMarketData) = 0;
	virtual void OnBar(Bar* pBar) = 0;
	virtual void OnMessage() = 0;
	virtual void OnAccount() = 0;
	virtual string LastOrderSysID()
	{
		if (!m_vectorOrderSysID.empty())
		{
			return m_vectorOrderSysID.back();
		}
		return "";
	}
private:
	vector<string> m_vectorOrderSysID;
};
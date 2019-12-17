#pragma once
#include "observer_class.h"
#include "ThostFtdcUserApiStruct.h"
#include "bar_class.h"

#include <list>
#include <algorithm>
#include <string>

using namespace std;

class Bar;

class Subject {
public:
	virtual void Attach(Observer* obj) { objList.push_front(obj); }
	virtual void Detach(Observer* obj) { objList.pop_front(); }
	virtual void Notify() { for_each(objList.begin(), objList.end(), [](Observer* obj) {obj->update(); }); }

	int SubjectState() const { return subjectState; }
	void SubjectState(int val) { subjectState = val; }

	CThostFtdcDepthMarketDataField SubjectTick()
	{
		return *m_pTick;
	}

	void SubjectTick(CThostFtdcDepthMarketDataField* pSubjectTick)
	{
		subjectState = 1;
		m_pTick = pSubjectTick;
		Notify();
	}

	Bar SubjectBar()
	{
		return *m_pBar;
	}

	void SubjectBar(Bar* pBar)
	{
		subjectState = 2;
		m_pBar = pBar;
		Notify();
	}

	CThostFtdcOrderField SubjectOrder()
	{
		return *m_pOrder;
	}

	void SubjectOrder(CThostFtdcOrderField* pOrder)
	{
		subjectState = 3;
		m_pOrder = pOrder;
		Notify();
	}

private:
	list<Observer*> objList;
	int subjectState;
	CThostFtdcDepthMarketDataField* m_pTick;
	CThostFtdcOrderField* m_pOrder;
	Bar* m_pBar;
};
#pragma once
#include <vector>
#include "define.h"
#include "ThostFtdcUserApiStruct.h"
#include "singleMaStrategy.h"

using namespace std;

struct Bar {
	TThostFtdcDateType	Day;
	char Hour[3];
	char Minute[3];
	double Open;
	double High;
	double Low;
	double Close;
	int Volume;
};

extern vector<CThostFtdcDepthMarketDataField> bufferMdVec;
extern tm lastMdTm;
extern FILE* klinefile;

void updateBufferMarketData(CThostFtdcDepthMarketDataField*);

void mdflush();

void conver(int);

int checkSignal(CThostFtdcDepthMarketDataField*);
int StartStrategy(Bar*);
int readCsv();
double calcSma();
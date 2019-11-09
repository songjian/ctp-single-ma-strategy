#pragma once
#include <vector>
#include <string>
#include "ThostFtdcUserApiStruct.h"

using namespace std;

int readFileTail(string, int, vector<string>*);

//string* ReadTail(char, int);

//int writeMarketDataToFile();
//void WriteMarketDataToFile(CThostFtdcDepthMarketDataField*);
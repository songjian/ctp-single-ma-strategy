#pragma once
#include "..\Common\MdHandler.h"
#include "MarketDataRecord.h"
#include <synchapi.h>
#include "GetInstrumentID.h"

using namespace std;

HANDLE g_hEvent = CreateEvent(NULL, false, false, NULL);
MarketDataRecord g_mdRecord;
vector<string> md_InstrumentID;
#pragma once
#include "MdHandler.h"
#include <synchapi.h>
#include "GetInstrumentID.h"

using namespace std;

HANDLE g_hEvent = CreateEvent(NULL, false, false, NULL);
vector<string> md_InstrumentID;
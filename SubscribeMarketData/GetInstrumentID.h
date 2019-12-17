#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

extern vector<string> md_InstrumentID;

class CGetInstrumentID
{
public:
	static void ReadInstrumentID()
	{
		ifstream fin("instruments.csv");
		string line;
		while (getline(fin, line))
		{
			istringstream sin(line);
			vector<string> fields;
			string field;
			while (getline(sin, field, ','))
			{
				fields.push_back(field);
			}
			md_InstrumentID.push_back(fields[0]);
			//cout << "InstrumentID£º" << fields[0] << endl;
		}
		fin.close();
	};
};


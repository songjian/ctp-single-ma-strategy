#include "stdafx.h"
#include "readfile.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int readFileTail(vector<string>* buffLine, string filePath, int rows, int shift = 0)
{
	ifstream fin(filePath, ios::ate);

	if (!fin) 
	{
		cerr << "打开日志文件失败！" << endl;
		return -1;
	}
	int nRows = rows + shift + 1;
	size_t nCounter = 0;
	fin.seekg(-1, ios::cur);
	char c = fin.peek();

	while (c != EOF)
	{
		if (c == '\n')
		{
			nCounter++;

			if (nCounter == nRows)
			{
				break;
			}
		}

		fin.seekg(-1, ios::cur);
		c = fin.peek();
	}

	if (c == EOF)
	{
		printf("找到EOF\n");
		return -2;
	}

	fin.seekg(2, ios::cur);

	string line;
	for (size_t i = 0; i < rows; i++)
	{
		getline(fin, line);
		printf("readfile_line_%zd: %s\n", i,line.c_str());
		buffLine->push_back(line);
	}

	fin.clear();
	fin.close();
	return 0;
}

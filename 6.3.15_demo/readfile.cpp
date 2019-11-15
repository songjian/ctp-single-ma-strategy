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

	// 先倒回文件末尾两个字符
	//fin.seekg(-2, fin.cur);
	for(int i = 0; i < rows + shift + 1; i++)
	{
		// 查看前一个字符是否为回车符
		while (fin.peek() != fin.widen('\n'))
		{
			fin.seekg(-1, fin.cur);
		}

		// 文件末尾返回-2
		if (fin.peek() == EOF)
		{
			fin.clear();
			fin.close();
			return -2;
		}
		
		// 走到这里表示跳过一行了，所以继续跳直到够100行
		fin.seekg(-2, fin.cur);
	}
	
	fin.seekg(2, fin.cur);
	
	// 现在文件指针指向99行的末尾，可以读取了
	string  line;
	for (size_t i = 0; i < rows; i++)
	{
		getline(fin, line);
		printf("readfile_line: %s\n", line.c_str());
		buffLine->push_back(line);
	}

	/*while( getline(fin, line) )
	{	
		//cout <<"新入一行 : "; << line << endl;
		buffLine->push_back(line);
	}*/
	fin.clear();
	fin.close();
	return 0;
}

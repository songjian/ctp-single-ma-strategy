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
		cerr << "����־�ļ�ʧ�ܣ�" << endl;
		return -1;
	}

	// �ȵ����ļ�ĩβ�����ַ�
	//fin.seekg(-2, fin.cur);
	for(int i = 0; i < rows + shift + 1; i++)
	{
		// �鿴ǰһ���ַ��Ƿ�Ϊ�س���
		while (fin.peek() != fin.widen('\n'))
		{
			fin.seekg(-1, fin.cur);
		}

		// �ļ�ĩβ����-2
		if (fin.peek() == EOF)
		{
			fin.clear();
			fin.close();
			return -2;
		}
		
		// �ߵ������ʾ����һ���ˣ����Լ�����ֱ����100��
		fin.seekg(-2, fin.cur);
	}
	
	fin.seekg(2, fin.cur);
	
	// �����ļ�ָ��ָ��99�е�ĩβ�����Զ�ȡ��
	string  line;
	for (size_t i = 0; i < rows; i++)
	{
		getline(fin, line);
		printf("readfile_line: %s\n", line.c_str());
		buffLine->push_back(line);
	}

	/*while( getline(fin, line) )
	{	
		//cout <<"����һ�� : "; << line << endl;
		buffLine->push_back(line);
	}*/
	fin.clear();
	fin.close();
	return 0;
}

#pragma once

#include "iostream"
#include "stdlib.h"
#include "CMysql.h"

class CBook
{
	int secNo1;
	int secNo2;
	int bookNo;
	char* bookName;
	char* writer;
	char* company;
public:
	CBook(int s1, int s2, int bn, char*ba, char*wt, char*com);
	virtual ~CBook();
	int getSecNo1() { return secNo1; }
	int getSecNo2() { return secNo2; }
	int getbookNo() { return bookNo; }
	char* getbookName() { return bookName; }
	char* getwriter() { return writer; }
	char* getcompany() { return company; }
	void print();
};

class CBookManager
{
	CBook *book[MAX_PATH];
	CMysql mysql;
	bool bstate;
	int maxRow;
public:
	CBookManager();
	virtual ~CBookManager(){}
	void bookPrint();
	bool searchBook(char* bookName);
	bool insertBook(int secNo1, int secNo2, int bookNo, char* bookName, char* writer, char* company);
	bool deleteBook(char* bookName);
	bool AllSaveToDB();
	bool DBDisconnect();
	bool DBConnect();
};

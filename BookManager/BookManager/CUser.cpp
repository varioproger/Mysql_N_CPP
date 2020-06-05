#include "stdafx.h"
#include "CUser.h"

//////////////////////////////////////////////
CBook::CBook(int s1=0, int s2=0, int bn=0, char*ba="bookName", char*wt="writer", char*com="company")
{
	secNo1 = s1;
	secNo2 = s2;
	bookNo = bn;
	bookName = new char[20];
	writer = new char[20];
	company = new char[20];

	strcpy_s(bookName, 20, ba);
	strcpy_s(writer, 20, wt);
	strcpy_s(company, 20, com);
}
CBook::~CBook()
{
	delete bookName, writer, company;
}

void CBook::print()
{
	printf("|  %d   |   %d   |   %d   |   %s   |   %s   |   %s\n", secNo1, secNo2, bookNo, bookName, writer, company);
	cout << "+--------------------------------------------------------------------------+" << endl;
}

//////////////////////////////////////////////////////
CBookManager::CBookManager()
{
	bstate = false;
	maxRow = 0;
}
bool CBookManager::DBDisconnect()
{
	if(bstate)
	{
		mysql.Disconnect();
		return true;
	}
	return false;
}
bool CBookManager::DBConnect()
{
	if(mysql.Connect("localhost","root","1","bbs"))
	{
		mysql.SelectDB("bbs");
		mysql.Query("select *from book");
		mysql.First();
		int i = 0;
		while(!mysql.IsEOF())
		{
			book[i] = new CBook(atoi(mysql["secNo1"]), atoi(mysql["secNo2"]), atoi(mysql["bookNo"]),
								mysql["bookName"], mysql["writer"], mysql["company"]);
			mysql.Next();
			i++;
		}
		maxRow = i;
		DBDisconnect();
		return true;
	}
	return false;
}
void CBookManager::bookPrint()
{
	cout << "+--------------------------------------------------------------------------+" << endl;
	cout << "+  No  |  SecNo1  |  SecNo2  |  bookNo  |  bookName  |  Writer  |  Company +" << endl;
	cout << "+--------------------------------------------------------------------------+" << endl;
	for(int i = 0; i<maxRow; i++)
	{
		book[i]->print();
	}
}
bool CBookManager::searchBook(char *bookName)
{
	for(int i = 0; i<maxRow; i++)
	{
		if(strncmp(book[i]->getbookName(), bookName, strlen(bookName)) == 0)
		{
			cout << "+---------------------------------------+" << endl;
			cout << "+ 도서번호 : " << book[i]->getbookNo() << endl;
			cout << "+ 도 서 명 : " << book[i]->getbookName() << endl;
			cout << "+ 저    자 : " << book[i]->getbookName() << endl;
			cout << "+ 출 판 사 : " << book[i]->getbookName() << endl;
			cout << "+---------------------------------------+" << endl;
			return true;
		}
	}
	cout << "+ 검색실패 : 찾으시는 도서가 없습니다" << endl << endl;
	return false;
}
bool CBookManager::insertBook(int secNo1, int secNo2, int bookNo, char* bookName, char* writer, char* company)
{
	for(int i = 0; i<maxRow; i++)
	{
		if(strncmp(book[i]->getbookName(), bookName, strlen(bookName)) == 0 || book[i]->getbookNo() == bookNo)
		{
			cout << "+ 중복되는 도서가 있어, 입력을 취소합니다." << endl << endl;
			cout << "+--------------------------------------------------------------------------+" << endl;
			cout << "+  No  |  SecNo1  |  SecNo2  |  bookNo  |  bookName  |  Writer  |  Company +" << endl;
			cout << "+--------------------------------------------------------------------------+" << endl;
			book[i]->print();
			return false;
		}
	}
	if(MAX_PATH > maxRow)
	{
		book[maxRow++] = new CBook(secNo1, secNo2, bookNo, bookName, writer, company);
		cout << "+ 도서가 등록되었습니다" << endl << endl;
		return true;
	}
	else
	{
		cout << "+ 자료 입력할 공간이 부족합니다" << endl << endl;
		return false;
	}
}
bool CBookManager::deleteBook(char* bookName)
{
	for(int i = 0; i<maxRow; i++)
	{
		if(strncmp(book[i]->getbookName(), bookName, strlen(bookName)) == 0)
		{
			for(int j = i; j<maxRow-1; j++)
				this->book[j] = this->book[j+1];
			
			cout << "+ 자료가 삭제되었습니다" << endl << endl;
			maxRow--;
			return true;
		}
	}
	cout << "+ 삭제실패 : 찾으시는 도서가 없습니다" << endl << endl;
	return false;
}
bool CBookManager::AllSaveToDB()
{
	char str[256];
	if(mysql.Connect("localhost","root","1","bbs"))
	{
		mysql.Query("delete from book");
		for(int i = 0; i<maxRow; i++)
		{
			sprintf(str, "insert into book value(%d,%d,%d,%d,'%s','%s','%s')",i+1, 
				book[i]->getSecNo1(), book[i]->getSecNo2(), book[i]->getbookNo(),
				book[i]->getbookName(), book[i]->getwriter(), book[i]->getcompany());
			mysql.Query(str);
		}
		DBDisconnect();
		return true;;
	}
	else
	{
		cout << "+ DB연결이 되지 않습니다." << endl << endl;
		return false;
	}
}
//////////////////////////////////////////////////////
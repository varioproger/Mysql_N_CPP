// BookManager.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CBookManager *bm = new CBookManager();
	if(!bm->DBConnect())
	{
		cout << "연결 에러!" << endl;
		exit(1);
	}
	int a,b,c; char q[10], w[10], e[10], i;

	cout << "+------------------------------------+" << endl;
	cout << "+    C++ / MySql 클래스 제작 예제    +" << endl;
	cout << "+              Visual Studio 2008    +" << endl;
	cout << "+                MySql ver 5.1.41    +" << endl;
	cout << "+                     by Copynull    +" << endl;
	cout << "+------------------------------------+" << endl;

	while(1)
	{
		cout << "  1. 도서 입력" << endl;
		cout << "  2. 도서 삭제" << endl;
		cout << "  3. 도서 검색" << endl;
		cout << "  4. 도서 출력" << endl;
		cout << "  5. 도서 저장" << endl;
		cout << "  6. 종료 하기" << endl;
		cout << "  7. 프로그램 설명" << endl;
	
		cout << "->";	i = getch();
		cout << i << endl;
		switch(i)
		{
		case '1':
			cout << "secNo1 : "; cin >> a;
			cout << "secNo2 : "; cin >> b;
			cout << "bookNo : "; cin >> c;
			cout << "bookName : "; cin >> q;
			cout << "writer : "; cin >> w;
			cout << "company : "; cin >> e;
			bm->insertBook(a,b,c,q,w,e);
			break;
		case '2':
			cout << "삭제할 도서명 입력 : "; cin >> q;
			bm->deleteBook(q);
			break;
		case '3':
			cout << "검색할 도서명 입력 : "; cin >> q;
			bm->searchBook(q);
			break;
		case '4':
			bm->bookPrint();
			break;
		case '5':
			if(bm->AllSaveToDB())
				cout << "모든 데이터 저장완료!" << endl << endl;
			else
				cout << "저장 에러!" << endl << endl;
			break;
		case '6':
			cout << endl << " + Make : copynull@nate.com" << endl;
			cout << " + Date : 2009. 12. 15" << endl << endl;
			bm->DBDisconnect();
			exit(1);
			break;
		case '7':
			cout << " MySql 클래스를 C++로 제작하여 DB프로그래밍 소스를 만들어 보았다" << endl << endl
				 << " ++ 동작기능 구현 설명 ++" << endl
				 << " CBook Entity class와 CBookManager class로 구성되어있다." << endl << endl
				 << " 최초DBConnect()함수를 통해 DB에 저장된 book 정보를 CBook Entity" << endl
				 << " new를 통한 객체 생성과 동시에 입력후 sql연결을 종료한다." << endl << endl
				 << " 입력,삭제,검색,출력 기능은 객체를 통해 사용되며, 저장하기를" << endl
				 << " 누름으로 최종적으로 다시 db연결 후 모든 데이터를 저장한다." << endl << endl
				 << " 간단하게 만들기 위해 db정보를 모두 삭제한 다음 객체를 다시 저장" << endl
				 << " 되도록 설계하였다." << endl << endl
				 << " 실시간으로 해당명령시 바로 db와 1:1 커넥션 되는 것도 가능했지만" << endl
				 << " 프로그램 유연성을 위해서 객체사용으로 기능구현하도록 하였다." << endl << endl;;
			break;
		default:
			cout << "잘못 입력하셨습니다" << endl;
			break;
		}
	}
	return 0;
}


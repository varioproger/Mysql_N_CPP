#pragma comment(lib, "libmysql.lib")
#pragma comment(lib,"ws2_32")
#include<stdio.h>
#include <mysql.h>

#define DB_HOST "localhost"	// DB IP주소 또는 도메인 또는 localhost
#define DB_USER "root"		// DB접속 계정 명
#define DB_PASS "1234"		// DB접속 계정 암호
#define DB_NAME "cookdb"	// DB 이름


int main()
{
	printf("MySQL client version: %s\n", mysql_get_client_info());

	MYSQL *connection=NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;

	// 초기화
	mysql_init(&conn);

	// DB 연결
	connection = mysql_real_connect(&conn, DB_HOST,	DB_USER, DB_PASS,DB_NAME, 3306,(char *)NULL, 0);
	if(connection==NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}
	else
	{
		printf("성공\n");
	}
	
	//한글사용을위해추가.
	mysql_query(connection,"set session character_set_connection=euckr");
	mysql_query(connection,"set session character_set_results=euckr");
	mysql_query(connection,"set session character_set_client=euckr");


	// Select 쿼리문
	char *query =  "SELECT * FROM pivottest";	// From 다음 DB에 존재하는 테이블 명으로 수정하세요
	query_stat=mysql_query(connection,query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	// 결과출력
	sql_result=mysql_store_result(connection);
	while((sql_row=mysql_fetch_row(sql_result))!=NULL)
	{
		printf("%2s %2s %s\n",sql_row[0],sql_row[1],sql_row[2]);
	}
	mysql_free_result(sql_result);
	// DB 연결닫기
	mysql_close(connection);
	return 0;
}
/*
참고 사이트 

https://copynull.tistory.com/13
https://copynull.tistory.com/14?category=194491
https://copynull.tistory.com/23
*/

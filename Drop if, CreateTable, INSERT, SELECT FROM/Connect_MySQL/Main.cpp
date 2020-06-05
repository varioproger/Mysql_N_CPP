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
	char msg[255];
	char* query;
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

	//use DB; sql문
	if (mysql_select_db(&conn, DB_NAME))
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
	}
	//use DB; sql문
	query = "DROP TABLE IF EXISTS TestTBL";	// 테이블이 존재한다면 삭제 하라
	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "CREATE TABLE Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	// Create_Table 쿼리문
	query = "CREATE TABLE TestTBL (first_name varchar(14), last_name varchar(16))";	// From 다음 DB에 존재하는 테이블 명으로 수정하세요
	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "CREATE TABLE Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	// INSERT INTO 쿼리문 {\"%s\" 큰따옴표 출력하는 방법}
	sprintf(msg, "INSERT INTO TestTBL VALUES (\"%s\",\"%s\")","정","경섭");
	query_stat = mysql_query(connection, msg);
	if (query_stat != 0)
	{
		fprintf(stderr, "NSERT INTO Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	// INSERT INTO 쿼리문 {\"%s\" 큰따옴표 출력하는 방법}
	sprintf(msg, "INSERT INTO TestTBL VALUES (\"%s\",\"%s\")", "김", "미림");
	query_stat = mysql_query(connection, msg);
	if (query_stat != 0)
	{
		fprintf(stderr, "NSERT INTO Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
	// Select 쿼리문
	query =  "SELECT * FROM TestTBL";
	query_stat=mysql_query(connection,query);
	if (query_stat != 0)
	{
		fprintf(stderr, "SELECT * FROM Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	// 결과출력
	sql_result=mysql_store_result(connection);
	while((sql_row=mysql_fetch_row(sql_result))!=NULL)
	{
		printf("%2s %s\n",sql_row[0],sql_row[1]);
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

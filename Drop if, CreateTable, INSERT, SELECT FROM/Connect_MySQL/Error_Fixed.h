#pragma once
/*
Authentication plugin 'caching_sha2_password' cannot be loaded: The specified module could not be found.

C:\ProgramData\MySQL\MySQL Server 8.0\my 클릭해서 default_authentication_plugin 검색해서 수정
#default_authentication_plugin=caching_sha2_password
default_authentication_plugin=mysql_native_password

cmd 창 키고


mysql -u root -p 

ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'your mySQL initial password';

그리고 

 select host,user, account_locked, plugin  from mysql.user; 해서 mysql_native_password 변경됐는지 확인


*/
#include <stdio.h.>
#include <my_global.h>
#include <mysql.h>

#pragma comment(lib, "libmySQL.lib")

void main()
{
	printf("MySQL Client Version: %s\n", mysql_get_client_info());

	MYSQL mysql;
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "dg319368", "shop_db", 3306, NULL, 0))
		printf("error");
	else
		printf("success");
	mysql_close(&mysql);

}

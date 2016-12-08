#include <stdio.h>
#include <mysql.h>
#include <errno.h>

int main(void)
{
	MYSQL mysql;
	MYSQL_RES * res;
	MYSQL_ROW row;
	int fields;

	mysql_init(&mysql);

	if(!mysql_real_connect(&mysql, NULL, "root", "dg319368", "testForConnect", 3306, (char*)NULL, 0))
	{
		printf("%s \n", mysql_error(&mysql));
		exit(1);
	}

	if(mysql_query(&mysql, "USE testForConnect"))
	{
		printf("%s \n", mysql_error(&mysql));
		exit(1);
	}
	if(mysql_query(&mysql, "SELECT * FROM driverInfo"))
	{
		printf("%s \n", mysql_error(&mysql));
		exit(1);
	}

	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);

	while((row = mysql_fetch_row(res)))
	{
		for(int cnt =0; cnt<fields; ++cnt)
		{
			printf("%12s", row[cnt]);
		}
		printf("\n");
	}

	mysql_free_result(res);
	mysql_close(&mysql);

	return 0;
}

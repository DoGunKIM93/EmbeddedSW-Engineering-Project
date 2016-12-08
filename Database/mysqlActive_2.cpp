#include <mysql.h>
#include <string.h>
#include <stdio.h>


#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "dg319368"
#define DB_NAME "testForConnect"
#define CHOP(x) x[strlen(x) - 1] = ' '

int main(void)
{
    MYSQL       *connection=NULL, conn;
    MYSQL_RES   *sql_result;
    MYSQL_ROW   sql_row;
    int       query_stat;

    char name[10];
    char carNumber[20];
    char carInfo[10];
    char query[255];

    mysql_init(&conn);

    connection = mysql_real_connect(&conn, DB_HOST,
                                    DB_USER, DB_PASS,
                                    DB_NAME, 3306,
                                    (char *)NULL, 0);

    if (connection == NULL)
    {
        fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
        return 1;
    }

    query_stat = mysql_query(connection, "select * from driverInfo");
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    sql_result = mysql_store_result(connection);

    printf("%+11s %-30s %-10s", "name", "carNumber", "carInfo");
    while ( (sql_row = mysql_fetch_row(sql_result)) != NULL )
    {
        printf("%+11s %-30s %-10s", sql_row[0], sql_row[1], sql_row[2]);
    }

    mysql_free_result(sql_result);

    printf("name :");
    fgets(name, 12, stdin);
    CHOP(name);

    printf("carNumber :");
    fgets(carNumber, 20, stdin);
    CHOP(carNumber);

    printf("carInfo :");
    fgets(carInfo, 12, stdin);
    CHOP(carInfo);

    sprintf(query, "insert into driverInfo values "
                   "('%s', '%s', '%s')",
                   name, carNumber, carInfo);

    query_stat = mysql_query(connection, query);
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    mysql_close(connection);
}

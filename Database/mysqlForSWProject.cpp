#include <mysql.h>
#include <string.h>
#include <stdio.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "dg319368"
#define DB_NAME "forSWClass"
#define CHOP(x) x[strlen(x) - 1] = ' '

int main(void)
{
    MYSQL       *connection=NULL, conn;
    MYSQL_RES   *sql_result;
    MYSQL_ROW   sql_row;
    int query_stat;
    int idx = 0;
    char name[20];
    char carNumber[10];
    char carInfo[20];
    char date[20];
    char contect[20];
    char point[10];
    char totalPoint[20];
    char query[255];
    int point_number = 0;
    int totalPoint_number = 0;
    int sum = 0;

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

    printf("%s %15s %15s %15s\n", "idx", "name", "carNumber", "carInfo");
    while ( (sql_row = mysql_fetch_row(sql_result)) != NULL )
    {
        printf("%s %20s %20s %20s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
    }

    mysql_free_result(sql_result);

    //////
    query_stat = mysql_query(connection, "select * from driverPoint_1");
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    sql_result = mysql_store_result(connection);

    printf("%s %15s %15s %15s\n", "idx", "date", "contents", "point");
    while ( (sql_row = mysql_fetch_row(sql_result)) != NULL )
    {
        printf("%s %20s %20s %20s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
	sum += atoi(sql_row[3]);
    }

    mysql_free_result(sql_result);
    //////


    //////

    printf("name :");
    fgets(name, 20, stdin);
    CHOP(name);

    printf("carNumber :");
    fgets(carNumber, 10, stdin);
    CHOP(carNumber);

    printf("carInfo :");
    fgets(carInfo, 20, stdin);
    CHOP(carInfo);

    sprintf(query, "insert into driverInfo values "
                   "('%d', '%s', '%s', '%s')",
                   idx, name, carNumber, carInfo);

    query_stat = mysql_query(connection, query);
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    /////
    printf("date :");
    fgets(date, 20, stdin);
    CHOP(date);

    printf("contents :");
    fgets(contect, 20, stdin);
    CHOP(contect);

    printf("point :");
    fgets(point, 10, stdin);
    CHOP(point);
    point_number = atoi(point);

    sprintf(query, "insert into driverPoint_1 values "
                   "('%d', '%s', '%s', '%d')",
                   idx, date, contect, point_number);

    query_stat = mysql_query(connection, query);
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    /////

    sprintf(query, "insert into driverTotalPoint_1 values "
                   "('%d', '%d')",
                   idx, sum);

    query_stat = mysql_query(connection, query);
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    //////
    query_stat = mysql_query(connection, "select * from driverTotalPoint_1");
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    sql_result = mysql_store_result(connection);

    printf("%s %15s\n", "idx", "totalPoint");
    while ( (sql_row = mysql_fetch_row(sql_result)) != NULL )
    {
        printf("%s %15s\n", sql_row[0], sql_row[1]);
    }

    mysql_free_result(sql_result);
    //////


    idx++;

    mysql_close(connection);
}

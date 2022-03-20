/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 15:27:10
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-03-20 20:31:31
 * @Description: file content
 */
#include "sql.h"

extern char* wday[];

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int insert_db_v2(sqlite3 *db, char buf[])
{
    char *zErrMsg = NULL;

    const char s[2] = ":";

    char timeBuf[24];
    memset(timeBuf,0,sizeof(timeBuf));
    
    char *HEAD = NULL;
    char *HUMVAL = NULL;
    char *useless1 = NULL;
    char *useless2 = NULL;
    char *TEMPVAL = NULL;
    char *FIREVAL = NULL;
    char *TIME = NULL;

    HEAD = strtok(buf,s);

    HUMVAL = strtok(NULL,s);

    useless1 = strtok(NULL,s);

    TEMPVAL = strtok(NULL,s);

    useless2 = strtok(NULL,s);

    FIREVAL = strtok(NULL,s);

    #if DEBUG
    // printf("%d/%d/%d/%s/%d:%d:%d\n", (1900+p->tm_year),( 1+p->tm_mon), p->tm_mday,
    //     wday[p->tm_wday],p->tm_hour, p->tm_min, p->tm_sec); 
    #endif

    // 获取时间
    time_t timep; 
    struct tm *p; 
    time(&timep); 
    p=localtime(&timep); /*取得当地时间*/ 
    sprintf(timeBuf,"%d/%d/%d/%s/%d:%d:%d", (1900+p->tm_year),( 1+p->tm_mon), p->tm_mday,
        wday[p->tm_wday],p->tm_hour, p->tm_min, p->tm_sec); 

    // reserve
    // int id = atoi(ID);

    int hum = atoi(HUMVAL);
    int temp = atoi(TEMPVAL);
    int fire_state = atoi(FIREVAL);
    printf("|%d|%d|%d|%s|\n",hum,temp,fire_state,timeBuf);


    // 数据拼接
    sprintf(buf,"INSERT INTO 'data'(HUM,TEMPRATURE,FIRE_STATE,TIME)VALUES(%d,%d,%d,'%s');",hum,temp,fire_state,timeBuf);

    // 执行插入操作
    sqlite3_exec(db, buf, NULL, NULL, &zErrMsg);

    printf("Insert complete\n");

    return 0;
}

#if 0
int insert_db(sqlite3 *db,char buf[])
{
    char *zErrMsg = NULL;
    char *sql1 = "INSERT INTO 'RECV_DATA'(ID,SMOKE,TEMPR,HUM,TIME)VALUES('";
    char *sql2 = "');";

    char *result = malloc(strlen(sql1)+strlen(sql2)+strlen(buf)+1);
    if (result == NULL)
    {
        exit(1);
    }

    strcat(result,sql1);
    strcat(result,buf);
    strcat(result,sql2);

    // // DEBUG
    // printf("%s\n",result);

    sqlite3_exec(db, result, NULL, NULL, &zErrMsg);

}
#endif

int handle_db(char buf[])
{
    sqlite3 *db = NULL;
    int len;
    int i = 0;
    int nrow = 0;
    int ncolumn = 0;
    char *zErrMsg = NULL;
    char **azResult = NULL; //二维数组存放结果
    
    /* 打开数据库 */
    len = sqlite3_open(DB_FILE, &db);
    if (len)
    {
        /*  fprintf函数格式化输出错误信息到指定的stderr文件流中  */
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)); //sqlite3_errmsg(db)用以获得数据库打开错误码的英文描述。
        sqlite3_close(db);
        exit(1);
    }
    else
        printf("Database opened\n");

    /* 创建表 */
    char *sql = "CREATE TABLE data(\
                HUM         INTEGER ,\
                TEMPRATURE  INTEGER ,\
                FIRE_STATE  INTEGER ,\
                TIME        TEXT\
                );";

    sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

    /*插入数据  */    
    insert_db_v2(db,buf);

    //   /* 查询数据 */
    //   sql="select *from SensorData";
    //   sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    //   printf("nrow=%d ncolumn=%d\n",nrow,ncolumn);
    //   printf("the result is:\n");
    //   for(i=0;i<(nrow+1)*ncolumn;i++)
    //     {
    //       printf("azResult[%d]=%s\n",i,azResult[i]);
    //     }

    //  /* 删除某个特定的数据 */
    //   sql="delete from SensorData where SensorID = 1 ;";
    //   sqlite3_exec( db , sql , NULL , NULL , &zErrMsg );

    //   /* 查询删除后的数据 */
    //   sql = "SELECT * FROM SensorData ";
    //   sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    //   printf( "row:%d column=%d\n " , nrow , ncolumn );
    //   printf( "After deleting , the result is : \n" );
    //   for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
    //   {
    //         printf( "azResult[%d] = %s\n", i , azResult[i] );
    //   }
    //   sqlite3_free_table(azResult);

    sqlite3_close(db);
    return 0;
}
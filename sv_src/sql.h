/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 15:27:18
 * @LastEditors: SingleBiu
 * @LastEditTime: 2022-03-20 20:33:15
 * @Description: file content
 */
#ifndef __SQL_H__
#define __SQL_H__

#include<sqlite3.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h> 

#define DB_FILE "data.db"

static int callback(void *NotUsed, int argc, char **argv, char **azColName);
int insert_db_v2(sqlite3 *db, char buf[]);
int handle_db(char buf[]);



#endif
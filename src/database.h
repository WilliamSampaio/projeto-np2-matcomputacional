#pragma once

#include <mysql/mysql.h>

typedef struct
{
    char host[100];
    char user[100];
    char pass[100];
    char database[100];
    int port;
} conn_info_t;

typedef struct
{
    unsigned int id;
    char name[61];
    int genre;
    char login[21];
    unsigned int password;
} tbl_user_t;

typedef struct
{
    unsigned int id;
    unsigned int user_id;
    float imc;
    char *datetime;
} tbl_imc_t;

typedef struct
{
    unsigned long int num_rows;
    tbl_imc_t *values;
} tbl_imc_result_t;

MYSQL *get_conn(conn_info_t *conn_info);
void close_conn(MYSQL **conn);
int _dbValidateLogin(tbl_user_t *user, char *login, int password, MYSQL **conn);
int _dbInsertIMC(tbl_user_t *user, float imc, MYSQL **conn);
int _dbAddUser(tbl_user_t new_user, MYSQL **conn);
int _dbUpdateUser(tbl_user_t *user, tbl_user_t updated_user, MYSQL **conn);
int _dbDeleteUser(tbl_user_t *user, MYSQL **conn);
tbl_imc_result_t *_dbGetIMCbyUserId(tbl_user_t *user, MYSQL **conn);

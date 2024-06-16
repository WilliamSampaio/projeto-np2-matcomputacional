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
    char *name;
    int genre;
    char *login;
    unsigned int password;
} tbl_user_t;

typedef struct
{
    unsigned int id;
    unsigned int user_id;
    float imc;
    char *datetime;
} tbl_imc_t;

MYSQL *get_conn(conn_info_t *conn_info);
void close_conn(MYSQL **conn);
int _dbValidateLogin(tbl_user_t *user, char *login, int password, MYSQL **conn);
int _dbInsertIMC(tbl_user_t *user, float imc, MYSQL **conn);
int _dbAddUser(tbl_user_t new_user, MYSQL **conn);
int _dbUpdateUser(tbl_user_t *user, tbl_user_t updated_user, MYSQL **conn);
tbl_imc_t *_dbGetIMCbyUserId(tbl_user_t *user, MYSQL **conn);

void _BD_atualizarCad();
// void _BD_delCad(char *, int);
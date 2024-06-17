#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "database.h"
#include "terminal.h"

MYSQL *get_conn(conn_info_t *_conn_info)
{
    MYSQL *_conn_obj = mysql_init(0);
    if (!_conn_obj)
        return NULL;
    MYSQL *_conn = mysql_real_connect(
        mysql_init(0),
        _conn_info->host,
        _conn_info->user,
        _conn_info->pass,
        _conn_info->database,
        _conn_info->port,
        NULL,
        0);
    if (!_conn)
        return NULL;
    return _conn;
}

void close_conn(MYSQL **_conn)
{
    mysql_close(*_conn);
}

int _dbValidateLogin(tbl_user_t *_user, char *_login, int _password, MYSQL **_conn)
{
    if (*_conn == NULL)
        return _False;

    MYSQL_RES *res;

    char query[200];
    sprintf(query, "SELECT * FROM usuarios WHERE login = '%s' AND senha = %d", _login, _password);

    if (
        mysql_query(*_conn, query) != MYSQL_STATUS_READY ||
        ((res = mysql_store_result(*_conn)) && (int)mysql_num_rows(res) == 0))
    {
        _msgDanger("FALHA", (char *)mysql_error(*_conn));
        return _False;
    }

    MYSQL_ROW row = mysql_fetch_row(res);

    _user->id = atoi(row[0]);
    strcpy(_user->name, row[1]);

    _user->genre = row[2][0] == "M"[0] ? M : F;
    strcpy(_user->login, row[3]);
    _user->password = atoi(row[4]);

    return _True;
}

int _dbInsertIMC(tbl_user_t *_user, float _imc, MYSQL **_conn)
{
    if (*_conn == NULL)
        return _False;

    char query[200];
    sprintf(query, "INSERT INTO registros (usuarios_id,imc,datahora) VALUES (%d,%f,'%s')",
            _user->id,
            _imc,
            __DATE__ " - " __TIME__);

    if (
        mysql_query(*_conn, query) != MYSQL_STATUS_READY ||
        (int)mysql_affected_rows(*_conn) == 0)
    {
        _msgDanger("FALHA", (char *)mysql_error(*_conn));
        return _False;
    }

    return _True;
}

int _dbAddUser(tbl_user_t _user, MYSQL **_conn)
{
    if (*_conn == NULL)
        return _False;

    char s = _user.genre == M ? 'M' : 'F';

    char query[200];
    sprintf(query, "INSERT INTO usuarios (nome, sexo, login, senha) VALUES ('%s','%c','%s','%d')",
            _user.name,
            s,
            _user.login,
            _user.password);

    if (
        mysql_query(*_conn, query) != MYSQL_STATUS_READY ||
        (int)mysql_affected_rows(*_conn) == 0)
    {
        _msgDanger("FALHA", (char *)mysql_error(*_conn));
        return _False;
    }

    return _True;
}

int _dbUpdateUser(tbl_user_t *_user, tbl_user_t _updated_user, MYSQL **_conn)
{
    if (*_conn == NULL)
        return _False;

    char s = _updated_user.genre == M ? 'M' : 'F';

    char query[200];
    sprintf(query, "UPDATE usuarios SET nome = '%s', sexo = '%c', login = '%s', senha = %d WHERE id = %d",
            _updated_user.name,
            s,
            _updated_user.login,
            _updated_user.password,
            _user->id);

    if (
        mysql_query(*_conn, query) != MYSQL_STATUS_READY ||
        (int)mysql_affected_rows(*_conn) == 0)
    {
        _msgDanger("FALHA", (char *)mysql_error(*_conn));
        return _False;
    }

    strcpy(_user->name, _updated_user.name);
    strcpy(_user->login, _updated_user.login);
    _user->genre = _updated_user.genre;
    _user->password = _updated_user.password;

    return _True;
}

int _dbDeleteUser(tbl_user_t *_user, MYSQL **_conn)
{
    if (*_conn == NULL)
        return _False;

    char query[200];
    sprintf(query, "DELETE FROM usuarios WHERE id = %d", _user->id);

    if (
        mysql_query(*_conn, query) != MYSQL_STATUS_READY ||
        (int)mysql_affected_rows(*_conn) == 0)
    {
        _msgDanger("FALHA", (char *)mysql_error(*_conn));
        return _False;
    }

    return _True;
}

tbl_imc_t *_dbGetIMCbyUserId(tbl_user_t *_user, MYSQL **_conn)
{
    if (*_conn == NULL)
        return NULL;

    MYSQL_RES *res;

    char query[200];
    sprintf(query, "SELECT * FROM registros WHERE usuarios_id = %d", _user->id);

    if (
        mysql_query(*_conn, query) != MYSQL_STATUS_READY ||
        ((res = mysql_store_result(*_conn)) && (int)mysql_num_rows(res) < 1))
    {
        _msgDanger("FALHA", (char *)mysql_error(*_conn));
        return NULL;
    }

    tbl_imc_t *values = calloc((size_t) mysql_num_rows(res) + 1, sizeof(tbl_imc_t));
    if (!values)
        return NULL;

    MYSQL_ROW row;

    int cont = 0;
    while ((row = mysql_fetch_row(res)))
    {
        tbl_imc_t t;
        t.id = atoi(row[0]);
        t.user_id = atoi(row[1]);
        t.imc = (float)atof(row[2]);
        t.datetime = row[3];
        *(values + cont) = t;
        cont++;
    }

    return values;
}

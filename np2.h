#ifdef _WIN32
#define CMD_CLEAR "cls"
#elif linux
#define CMD_CLEAR "clear"
#endif

#include <mysql/mysql.h>
#include <stdio.h>

enum boolean
{
    _False,
    _True
};

enum status
{
    _Success,
    _Info,
    _Danger
};

enum genres
{
    M,
    F
};

typedef struct
{
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    int qstate;
} t_MySQLConn;

typedef struct
{
    char host[100];
    char user[100];
    char pass[100];
    char database[100];
    int port;
} t_DBInfo;

typedef struct
{
    char name[60];
    int genre;
    char login[20];
    int password;
} t_User;

void _msgSuccess(char *, char *);
void _msgInfo(char *, char *);
void _msgDanger(char *, char *);

int _confirmYesNo(char *, char *, int);
void _confirmOk(char *, char *, int);

char *_dateTime();
void _setPtBRLocale();

void *_sdl2PlayWav(void *);
void _playSound();
void _stopSound();

void _exitNP2();

void _mainMenu();
void _starWarsRobos();
void _startNP2();

void _imcPrincipal();
void _imcTitulo();
void _imcMenu();
void _imcCad();

// void _imcEntrar();
// void _imcRelatorio(char *, int);
// void _imcExibirImc(char *, int);
// void _imcDelCadImc(char *, int);
// void _imcUpdateCadImc(char *, int);
// void _imcSessao(char *, int);

// void load();

void _dbSetup();
void _dbGetConfig(t_DBInfo *);
void _dbUpdateConfig();
void _dbCheckConn();

void _dbCreateUser();
// void _BD_atualizarCad(char *, int);
// void _BD_pegarUserInfo(char *, int);
// void _BD_registrarImc(char *, int);
// void _BD_exibirImc(char *, int);
// void _BD_delCad(char *, int);

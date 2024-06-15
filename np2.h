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

enum dataTypes
{
    _String,
    _Int,
    _Float
};

enum status
{
    _Success,
    _Info,
    _Danger,
    _Warning
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
    unsigned int id;
    char *name;
    int genre;
    char *login;
    unsigned int password;
} t_User;

typedef struct
{
    unsigned int id;
    unsigned int user_id;
    float imc;
    char *datetime;
} t_IMC;

void user_init(t_User *);

void _msgSuccess(char *, char *);
void _msgInfo(char *, char *);
void _msgDanger(char *, char *);
void _msgWarning(char *, char *);
void _msg(char *, char *, int);

int _confirmYesNo(char *, char *, int);
void _confirmOk(char *, char *, int);

void _getData(void *, int, char *, int);

char *_dateTime();
void _setPtBRLocale();

void *_sdl2PlayWav(void *);
void _playSound();
void _stopSound();

void _exitNP2();

void _logoutTxtOption();
void _processLogout();

void _mainMenu();
void _starWarsRobos();
void _startNP2();

void _imcAddIMC();
void _imcLogin();
void _imcMenu();
void _imcReport();
void _imcSession();
void _imcTxtTitle();
void _imcAddUser();
void _imcUpdateUser();

// void _imcDelCadImc(char *, int);

// void load();

void _writeConfig(FILE **);
void _dbSetup();
void _dbGetConfig(t_DBInfo *);
void _dbUpdateConfig();
void _dbCheckConn();
int _dbInit();
int _dbConnect(t_DBInfo *);
int _dbValidateLogin(t_User *, char *, int);
int _dbInsertIMC(t_User *, float);
int _dbAddUser(t_User);
int _dbUpdateUser(t_User *, t_User);
t_IMC *_dbGetIMCbyUserId(t_User *);

void _BD_atualizarCad();
// void _BD_delCad(char *, int);

#ifdef _WIN32
#include <windows.h>
#elif linux
#include <unistd.h>
#endif

#include <locale.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "np2.h"
#include "np2txt.h"
#include "np2ansi-color-codes.h"

const char *fileDb = "configdb";

FILE *_configDb;

t_MySQLConn connObj;
t_DBInfo dbConfig;

pthread_t soundPthreadId;

int playing = _False;

void _msgSuccess(char *_title, char *_message)
{
    printf("%s::: %s:%s %s%s\n", BHGRN, _title, GRN, _message, COLOR_RESET);
}

void _msgInfo(char *_title, char *_message)
{
    printf("%s::: %s:%s %s%s\n", BHBLU, _title, BLU, _message, COLOR_RESET);
}

void _msgDanger(char *_title, char *_message)
{
    printf("%s::: %s:%s %s%s\n", BHRED, _title, RED, _message, COLOR_RESET);
}

void _msgWarning(char *_title, char *_message)
{
    printf("%s::: %s:%s %s%s\n", BHYEL, _title, YEL, _message, COLOR_RESET);
}

int _confirmYesNo(char *_title, char *_message, int _status)
{
    switch (_status)
    {
    case _Success:
        _msgSuccess(_title, _message);
        break;
    case _Info:
        _msgInfo(_title, _message);
        break;
    case _Danger:
        _msgDanger(_title, _message);
        break;
    case _Warning:
        _msgWarning(_title, _message);
        break;
    default:
        break;
    }
    do
    {
        setbuf(stdin, NULL);
        char op[3];
        printf("Confirm (y/n): ");
        scanf("%s", op);
        if (toupper(op[0]) == 'Y')
        {
            return _True;
        }
        else if (toupper(op[0]) == 'N')
        {
            return _False;
        }
        else
        {
            _msgDanger("ERROR!", "Invalid option.");
        }
    } while (1);
}

void _confirmOk(char *_title, char *_message, int _status)
{
    switch (_status)
    {
    case _Success:
        _msgSuccess(_title, _message);
        break;
    case _Info:
        _msgInfo(_title, _message);
        break;
    case _Danger:
        _msgDanger(_title, _message);
        break;
    case _Warning:
        _msgWarning(_title, _message);
        break;
    default:
        break;
    }
    printf("Press any key to continue...");
    setbuf(stdin, NULL);
    getchar();
}

void _getData(void *_var, char *_type, char *_message, int _status)
{
    switch (_status)
    {
    case _Success:
        _msgSuccess(_message, "");
        break;
    case _Info:
        _msgInfo(_message, "");
        break;
    case _Danger:
        _msgDanger(_message, "");
        break;
    case _Warning:
        _msgWarning(_message, "");
        break;
    default:
        break;
    }
    printf("::: ");
    scanf(_type, (char *)_var);
}

char *_dateTime()
{
    return __DATE__ " - " __TIME__;
}

void _setPtBRLocale()
{
    setlocale(LC_ALL, "Portuguese");
}

void *_sdl2PlayWav(void *_wavFilename)
{
    // pthread_t tid;
    // tid = pthread_self();

    SDL_Init(SDL_INIT_AUDIO);

    // load WAV file
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    SDL_LoadWAV(_wavFilename, &wavSpec, &wavBuffer, &wavLength);

    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

    // play audio
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    // keep window open enough to hear the sound
    while (playing)
    {
    }

    // clean up
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
    pthread_exit(NULL); /* terminate the thread */
}

void _playSound()
{
    int rc;                        /* return value                           */
    char *wav = "sound/teste.wav"; /* data passed to the new thread          */

    /* create a new thread that will execute 'playSound' */
    rc = pthread_create(&soundPthreadId, NULL, _sdl2PlayWav, (void *)wav);
    if (rc) /* could not create thread */
    {
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    playing = _True;
}

void _stopSound()
{
    pthread_cancel(soundPthreadId);
    playing = _False;
}

void _exitNP2()
{
    if (_confirmYesNo("SAIR", "Você deseja realmente SAIR?", _Danger) == _True)
    {
        system(CMD_CLEAR);
        txtExit();
        exit(0);
    }
}

void _mainMenu()
{
    system(CMD_CLEAR);
    txtTeam();
    printf("\n");
    printf("\tMENU PRINCÍPAL:\n\n");
    printf("\t[1] - ROBÔS STAR WARS\n");
    printf("\t[2] - IMC COM MySQL\n");
    printf("\n");
    printf("\t[3] - CHECAR CONEXÃO COM O BD\n");
    printf("\t[4] - ALTERAR CONFIG DE ACESSO AO BD\n\n");
    printf("\t[9] - PLAY / STOP MUSICA\n");
    printf("\t[0] - SAIR\n\n");
    printf("\t -> ");

    int op;
    scanf("%d", &op);

    switch (op)
    {
    case 0:
        _exitNP2();
        _mainMenu();
        break;
    case 1:
        _starWarsRobos();
        break;
    case 2:
        _imcPrincipal();
        break;
    case 3:
        _dbCheckConn();
        _mainMenu();
        break;
    case 4:
        _dbUpdateConfig();
        _dbCheckConn();
        _mainMenu();
        break;
    case 9:
        playing ? _stopSound() : _playSound();
        _mainMenu();
        break;
    default:
        _mainMenu();
        break;
    }
}

void _starWarsRobos()
{
    system(CMD_CLEAR);
    txtStarWarsRobos();
    int op;
    do
    {
        printf("\n");
        printf("[1] - RESETAR | [2] - MENU PRINCIPAL | [0] - SAIR\n");

        scanf("%d", &op);
        switch (op)
        {
        case 0:
            _exitNP2();
            _starWarsRobos();
            break;
        case 1:
            _starWarsRobos();
            break;
        case 2:
            _startNP2(0);
            break;
        default:
            _starWarsRobos();
            break;
        }
    } while (op < 0 || op > 2);
}

void _startNP2()
{
    _dbCheckConn();
    _playSound();
    _mainMenu(0);
}

void _imcPrincipal()
{
    _imcTitulo();
    _imcMenu();
}

void _imcTitulo()
{
    system(CMD_CLEAR);
    printf("################################################################################\n");
    printf("#                 SISTEMA - INDICE DE MASSA CORPORAL (com MySQL)               #\n");
    printf("################################################################################\n\n");
}

void _imcMenu()
{
    printf("\t- [1]ENTRAR\n");
    printf("\t- [2]CADASTRE-SE\n");
    printf("\n");
    printf("\t- [9]VOLTAR AO MENU PRINCÍPAL\n");
    printf("\t- [0]SAIR\n");
    printf("\n\t");

    int op;
    scanf("%d", &op);

    switch (op)
    {
    case 0:
        _exitNP2();
        _imcPrincipal();
        break;
    case 1:
        // _imcEntrar();
        break;
    case 2:
        // _imcCad();
        break;
    case 9:
        _mainMenu();
        break;
    default:
        _imcPrincipal();
        break;
    }
}

void _imcCad()
{
    _imcTitulo();
    // _dbCreateUser();
    _imcPrincipal();
}

// // LOGIN DE ACESSO AO SISTEMA
// void _imcEntrar()
// {

//     char login[20];
//     int senha;
//     _imcTitulo();
//     printf(" - LOGIN: ");
//     scanf("%s", login);
//     printf(" - SENHA: ");
//     scanf("%d", &senha);
//     if (_BD_validarLogin(login, senha) == 1)
//     {
//         _imcSessao(login, senha);
//     }
//     else
//     {
//         int op;
//         printf(" LOGIN OU SENHA INV�LIDO!\n");
//         printf(" [1] - Tentar Novamente / [2] - voltar\n");
//         do
//         {
//             scanf("%d", &op);
//             if (op == 1)
//             {
//                 system(CMD_CLEAR);
//                 _imcEntrar();
//             }
//             else
//             {
//                 if (op == 2)
//                 {
//                     _imcPrincipal();
//                 }
//                 else
//                 {
//                     printf("Op��o Inv�lida! :(\n");
//                 }
//             }
//         } while (op != 1 && op != 2);
//     }
// }

// // PEGAR AS INFORMA��ES DO t_User LOGADO
// void _imcRelatorio(char login[20], int senha)
// {

//     _BD_pegarUserInfo(login, senha);
// }

// // EXIBE OS REGISTROS DE IMC
// void _imcExibirImc(char login[20], int senha)
// {

//     _BD_exibirImc(login, senha);
// }

// // DELETA CADASTRO DE USU�RIO
// void _imcDelCadImc(char login[20], int senha)
// {

//     _BD_delCad(login, senha);
// }

// // ATUALIZA O CADASTRO DO USU�RIO
// void _imcUpdateCadImc(char login[20], int senha)
// {

//     system(CMD_CLEAR);
//     _imcTitulo();
//     _BD_atualizarCad(login, senha);
// }

// // ABRE O MENU PRINC�PAL DO USU�RIO
// void _imcSessao(char login[20], int senha)
// {
//     int i;
//     _imcTitulo();
//     printf("\n");
//     _imcRelatorio(login, senha);
//     for (i = 0; i < 80; i++)
//     {
//         printf("_");
//     }
//     printf("\t[1] - REGISTRAR NOVO IMC.\n");
//     printf("\t[2] - EXIBIR TODOS OS REGISTROS\n\n");
//     printf("\t[4] - ALTERAR DADOS PESSOAIS\n\n");
//     printf("\t[9] - VOLTAR AO MENU PRINC�PAL\n");
//     printf("\t[0] - SAIR\n\n");
//     printf("\t[-99] - APAGAR CADASTRO\n\n");
//     printf("\t::");
//     int op;
//     scanf("%d", &op);

//     switch (op)
//     {
//     case 0:
//         if (MessageBox(NULL, "Voc� deseja realmente SAIR?", "SAIR", MB_YESNO | MB_ICONQUESTION) == 6)
//         {
//             sair();
//         }
//         else
//         {
//             _imcSessao(login, senha);
//         }
//         break;
//     case 1:
//         system(CMD_CLEAR);
//         _imcTitulo();
//         _BD_registrarImc(login, senha);
//         system("pause");
//         _imcSessao(login, senha);
//         break;
//     case 2:
//         system(CMD_CLEAR);
//         _imcTitulo();
//         _imcExibirImc(login, senha);
//         system("pause");
//         _imcSessao(login, senha);
//         break;
//     case 4:
//         _imcUpdateCadImc(login, senha);
//         system("pause");
//         _imcPrincipal();
//         break;
//     case 9:
//         _imcPrincipal();
//         break;
//     case -99:
//         system(CMD_CLEAR);
//         _imcTitulo();
//         _BD_delCad(login, senha);
//         system("pause");
//         _imcPrincipal();
//         break;
//     default:
//         MessageBox(NULL, "Op��o inv�lida!", "ERRO!", MB_OK | MB_ICONERROR);
//         _imcSessao(login, senha);
//         break;
//     }
// }

// void _dbCreateUser()
// {
//     _dbSetup();
//     _dbGetConfig(&dbConfig);

//     t_User user;

//     int cont, error, space = 0;

//     do
//     {
//         fflush(stdin);
//         printf(">> DIGITE SEU NOME COMPLETO:\n");
//         fgets(user.nome);
//         strupr(user.nome);
//         for (cont = 0; cont < strlen(user.nome); cont++)
//         {
//             if (user.nome[cont] == ' ')
//             {
//                 space = 1;
//             }
//         }
//         if (space == 0)
//         {
//             printf("ERRO! Nome inválido.\n");
//         }
//     } while (space == 0);

//     char sexo;
//     do
//     {
//         fflush(stdin);
//         printf(">> QUAL SEU SEXO (M / F):\n");
//         scanf("%c", &sexo);

//         if (sexo != 'M' && sexo != 'F')
//         {
//             printf("ERRO! Alternativa inválida.\n");
//         }
//     } while (sexo != 'M' && sexo != 'F');

//     do
//     {
//         int spc;

//         do
//         {
//             spc = 0;
//             do
//             {
//                 fflush(stdin);
//                 printf(">> NOME DE USUÁRIO (MAX - 20):\n");
//                 fgets(user.login);

//                 if (strlen(user.login) > 20)
//                 {
//                     printf("ERRO! Nome de usuário deve ter no maximo 20 caracteres.\n");
//                 }

//             } while (strlen(user.login) > 20);

//             for (cont = 0; cont < strlen(
//         }
//     } while (spc == 1);
//     if (_BD_validarUserName(user.login) == 1)
//     {
//         printf("Login j� utilizado por outro usu�rio :(\n");
//     }
//     else
//     {
//         if (_BD_validarUserName(user.login) == -1)
//         {
//             erro = 1;
//         }
//         else
//         {
//             if (_BD_validarUserName(user.login) == -2)
//             {
//                 erro = 1;
//                 _conStatus02();
//             }
//             else
//             {
//                 if (_BD_validarUserName(user.login) == -3)
//                 {
//                     erro = 1;
//                     _conStatus03();
//                 }
//                 else
//                 {
//                     erro = 0;
//                 }
//             }
//         }
//     }
// }
// while (erro != 0)
//     ;

// int senhaR;
// do
// {
//     do
//     {
//         printf(">> DIGITE UMA SENHA (APENAS N�MEROS, MAX - 5):\n");
//         fflush(stdin);
//         scanf("%d", &user.senha);
//         if (user.senha > 99999)
//         {
//             printf("ERRO! Senha deve ter no maximo 5 digitos.\n");
//         }
//     } while (user.senha > 99999);

//     printf(">> REPITA A SENHA DE ACESSO:\n");
//     fflush(stdin);
//     scanf("%d", &senhaR);
//     if (senhaR != user.senha)
//     {
//         printf("ERRO! Senhas n�o coincidem.\n");
//     }
// } while (senhaR != user.senha);

// if (connObj.conn = mysql_init(0))
// {
//     if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//     {
//         char query[200];
//         sprintf(query, "INSERT INTO t_Users (nome, sexo, login, senha) VALUES ('%s','%c','%s','%d')", user.nome, user.sexo, user.login, user.senha);
//         connObj.qstate = mysql_query(connObj.conn, query);
//         if (!connObj.qstate)
//         {
//             printf("DADOS INSERIDOS COM SUCESSO!\n");
//         }
//         else
//         {
//             int op;
//             printf("ERRO! Algo deu errado...\n");
//             printf(" [1] - Tentar Novamente / [2] - voltar\n");
//             do
//             {
//                 printf(" ");
//                 scanf("%d", &op);
//                 if (op == 1)
//                 {
//                     system(CMD_CLEAR);
//                     _imcCad();
//                 }
//                 else
//                 {
//                     if (op == 2)
//                     {
//                         _imcPrincipal();
//                     }
//                     else
//                     {
//                         printf("Op��o Inv�lida! :(");
//                     }
//                 }
//             } while (op != 1 && op != 2);
//         }
//     }
//     else
//     {
//         _conStatus02();
//     }
// }
// else
// {
//     _conStatus03();
// }
// }

// // ATUALIZAR CADASTRO DE USU�RIO NO BD
// void _BD_atualizarCad(char login[20], int senha)
// {

//     _dbSetup();
//     _dbGetConfig(&dbConfig);

//     t_User update;
//     int cont, op, erro, senhaR;
//     int espaco = 0;
//     char query[200];

//     sprintf(query, "select nome,sexo,login,senha from t_Users where login = '%s' and senha = '%d'", login, senha);

//     if (connObj.conn = mysql_init(0))
//     {
//         if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//         {
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {

//                 connObj.res = mysql_store_result(connObj.conn);
//                 while (connObj.row = mysql_fetch_row(connObj.res))
//                 {
//                     strcpy(update.nome, connObj.row[0]);
//                     if (connObj.row[1] == "M")
//                     {
//                         update.sexo = 'M';
//                     }
//                     else
//                     {
//                         update.sexo = 'F';
//                     }
//                     strcpy(update.login, connObj.row[2]);
//                     update.senha = atoi(connObj.row[3]);
//                 }
//             }
//             else
//             {
//                 _conStatus00(connObj);
//                 mysql_close(connObj.conn);
//             }
//         }
//         else
//         {
//             _conStatus02();
//         }
//     }
//     else
//     {
//         _conStatus03();
//     }

//     printf(">> ATUALIZAR...\n\n");
//     printf(">> [1] - NOME   \n");
//     printf(">> [2] - SEXO   \n");
//     printf(">> [3] - LOGIN  \n");
//     printf(">> [4] - SENHA  \n\n");
//     printf(">> [0] - VOLTAR  \n\n::");
//     scanf("%d", &op);
//     switch (op)
//     {
//     case 0:
//         _imcSessao(login, senha);
//         break;
//     case 1:
//         do
//         {
//             fflush(stdin);
//             printf(">> DIGITE SEU NOME COMPLETO:\n");
//             fgets(update.nome);
//             strupr(update.nome);
//             for (cont = 0; cont < strlen(update.nome); cont++)
//             {
//                 if (update.nome[cont] == ' ')
//                 {
//                     espaco = 1;
//                 }
//             }
//             if (espaco == 0)
//             {
//                 printf("ERRO! Nome inv�lido.\n");
//             }
//         } while (espaco == 0);
//         break;
//     case 2:
//         do
//         {
//             char sexo;
//             fflush(stdin);
//             printf(">> QUAL SEU SEXO (M / F):\n");
//             scanf("%c", &sexo);
//             update.sexo = toupper(sexo);
//             if (update.sexo != 'M' && update.sexo != 'F')
//             {
//                 printf("ERRO! Alternativa inv�lida.\n");
//             }
//         } while (update.sexo != 'M' && update.sexo != 'F');
//         break;
//     case 3:

//         do
//         {
//             int spc;
//             do
//             {
//                 spc = 0;
//                 do
//                 {
//                     fflush(stdin);
//                     printf(">> NOME DE USU�RIO (MAX - 20):\n");
//                     fgets(update.login);
//                     if (strlen(update.login) > 20)
//                     {
//                         printf("ERRO! Nome de usu�rio deve ter no maximo 20 caracteres.\n");
//                     }
//                 } while (strlen(update.login) > 20);

//                 for (cont = 0; cont < strlen(update.login); cont++)
//                 {
//                     if (update.login[cont] == ' ')
//                     {
//                         printf("ERRO! N�o pode haver espa�os.\n");
//                         spc = 1;
//                     }
//                     break;
//                 }
//             } while (spc == 1);
//             if (_BD_validarUserName(update.login) == 1)
//             {
//                 printf("Login j� utilizado por outro usu�rio :(\n");
//             }
//             else
//             {
//                 if (_BD_validarUserName(update.login) == -1)
//                 {
//                     erro = 1;
//                 }
//                 else
//                 {
//                     if (_BD_validarUserName(update.login) == -2)
//                     {
//                         erro = 1;
//                         _conStatus02();
//                     }
//                     else
//                     {
//                         if (_BD_validarUserName(update.login) == -3)
//                         {
//                             erro = 1;
//                             _conStatus03();
//                         }
//                         else
//                         {
//                             erro = 0;
//                         }
//                     }
//                 }
//             }
//         } while (erro != 0);
//         break;
//     case 4:
//         do
//         {
//             do
//             {
//                 printf(">> DIGITE UMA SENHA (APENAS N�MEROS, MAX - 5):\n");
//                 fflush(stdin);
//                 scanf("%d", &update.senha);
//                 if (update.senha > 99999)
//                 {
//                     printf("ERRO! Senha deve ter no maximo 5 digitos.\n");
//                 }
//             } while (update.senha > 99999);

//             printf(">> REPITA A SENHA DE ACESSO:\n");
//             fflush(stdin);
//             scanf("%d", &senhaR);
//             if (senhaR != update.senha)
//             {
//                 printf("ERRO! Senhas n�o coincidem.\n");
//             }
//         } while (senhaR != update.senha);
//         break;
//     default:
//         // MessageBox(NULL, "Op��o inv�lida!", "ERRO!", MB_OK | MB_ICONERROR);
//         system(CMD_CLEAR);
//         _imcUpdateCadImc(login, senha);
//         break;
//     }

//     if (connObj.conn = mysql_init(0))
//     {
//         if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//         {

//             sprintf(query, "UPDATE t_Users SET nome = '%s', sexo = '%c', login ='%s', senha = '%d' WHERE login = '%s' AND senha = '%d'", update.nome, update.sexo, update.login, update.senha, login, senha);
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {
//                 printf(">> CADASTRO ATUALIZADO COM SUCESSO!\n");
//                 mysql_close(connObj.conn);
//             }
//             else
//             {
//                 _conStatus00(connObj);
//                 mysql_close(connObj.conn);
//                 return 0;
//             }
//         }
//         else
//         {
//             _conStatus02();
//         }
//     }
//     else
//     {
//         _conStatus03();
//     }
// }

// // VERIFICA SE O NOME DE t_User JA EXISTE NO BD
// int _BD_validarUserName(char *login)
// {

//     _dbSetup();
//     _dbGetConfig(&dbConfig);

//     if (connObj.conn = mysql_init(0))
//     {
//         if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//         {
//             char query[200];
//             sprintf(query, "select login from t_Users where login = '%s'", login);
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {
//                 connObj.res = mysql_store_result(connObj.conn);
//                 while (connObj.row = mysql_fetch_row(connObj.res))
//                 {
//                     if (connObj.row[0])
//                     {
//                         mysql_close(connObj.conn);
//                         return 1;
//                     }
//                     else
//                     {
//                         return 0;
//                     }
//                     break;
//                 }
//             }
//             else
//             {
//                 _conStatus00(connObj);
//                 mysql_close(connObj.conn);
//                 return -1;
//             }
//         }
//         else
//         {
//             return -2;
//         }
//     }
//     else
//     {
//         return -3;
//     }
// }

// // VALIDAR ACESSO
// int _BD_validarLogin(char login[20], int senha)
// {

//     _dbSetup();
//     _dbGetConfig(&dbConfig);

//     if (connObj.conn = mysql_init(0))
//     {
//         if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//         {
//             char query[200];
//             sprintf(query, "select login,senha from t_Users where login = '%s' and senha = '%d'", login, senha);
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {
//                 connObj.res = mysql_store_result(connObj.conn);
//                 while (connObj.row = mysql_fetch_row(connObj.res))
//                 {
//                     if (connObj.row[0])
//                     {
//                         mysql_close(connObj.conn);
//                         return 1;
//                     }
//                 }
//             }
//             else
//             {
//                 _conStatus00(connObj);
//                 mysql_close(connObj.conn);
//                 return 0;
//             }
//         }
//         else
//         {
//             _conStatus02();
//             return 0;
//         }
//     }
//     else
//     {
//         _conStatus03();
//         return 0;
//     }
// }

void _BD_pegarUserInfo(char *login, int senha)
{
    _dbSetup();
    _dbGetConfig(&dbConfig);

    if ((connObj.conn = mysql_init(0)))
    {
        if ((connObj.conn = mysql_real_connect(
                 connObj.conn,
                 dbConfig.host,
                 dbConfig.user,
                 dbConfig.pass,
                 dbConfig.database,
                 dbConfig.port, NULL, 0)))
        {

            int id;
            int i;
            int contReg = 0;
            float contRegTotal = 0;
            float media;
            char ultimoReg[22];
            char info[80];

            strcpy(ultimoReg, "NULL");

            char query[200];
            sprintf(query, "SELECT id,nome,sexo,login,senha from usuarios where login = '%s' and senha = '%d'", login, senha);
            connObj.qstate = mysql_query(connObj.conn, query);
            if (!connObj.qstate)
            {
                connObj.res = mysql_store_result(connObj.conn);
                while ((connObj.row = mysql_fetch_row(connObj.res)))
                {
                    id = atoi(connObj.row[0]);
                    int charCont = (80 - (10 + strlen(connObj.row[1]))) / 2;
                    for (i = 0; i < charCont; i++)
                    {
                        printf(" ");
                    }
                    printf("BEM-VIND");
                    if (strcmp(connObj.row[2], "M") == 0)
                    {
                        printf("O");
                    }
                    else
                    {
                        printf("A");
                    }
                    printf(" %s", connObj.row[1]);
                    printf("\n");
                }
            }
            else
            {
                // _conStatus00(connObj);
                mysql_close(connObj.conn);
            }

            sprintf(query, "SELECT * FROM registros WHERE usuarios_id = '%d'", id);
            connObj.qstate = mysql_query(connObj.conn, query);
            if (!connObj.qstate)
            {
                connObj.res = mysql_store_result(connObj.conn);
                printf("+-------------------------------------------------------+\n");
                printf("|\tID\t|\tIMC\t|\tDATA HORA\t|\n");
                printf("+-------------------------------------------------------+\n");
                while ((connObj.row = mysql_fetch_row(connObj.res)))
                {
                    printf("|\t%s\t|\tIMC\t|\tDATA HORA\t|\n",connObj.row[0]);
                    contReg++;
                    contRegTotal += atof(connObj.row[2]);
                    strcpy(ultimoReg, connObj.row[3]);
                }

                if (contReg != 0)
                {
                    media = contRegTotal / contReg;
                }
                else
                {
                    media = 0;
                }

                printf("     ");
                for (i = 0; i < 70; i++)
                {
                    printf("-");
                }
                printf("\n");

                char str[24];
                sprintf(info, " %d - Registros | Média: %.2f | Último imc [", contReg, media);
                sprintf(str, "%s]", ultimoReg);
                strcat(info, str);

                int tam = strlen(info);
                tam = (80 - tam) / 2;
                for (i = 0; i < tam; i++)
                {
                    printf(" ");
                }
                printf("%s", info);
                printf("\n");

                printf("     ");
                for (i = 0; i < 70; i++)
                {
                    printf("-");
                }
                printf("\n");
            }
            else
            {
                // _conStatus00(connObj);
                mysql_close(connObj.conn);
            }
            mysql_close(connObj.conn);
        }
        else
        {
            // _conStatus02();
        }
    }
    else
    {
        _confirmOk("ERRO FATAL!", "NÃO foi possivel criar o OBJETO de conexão!", _Danger);
    }
}

// // ADICIONA UM NOVO IMC (REGISTRO) NO BD
// void _BD_registrarImc(char login[20], int senha)
// {

//     _dbSetup();
//     _dbGetConfig(&dbConfig);
//     int i;
//     float peso, altura;
//     char _id[5], imc[10], query[100];

//     fflush(stdin);
//     printf(" (Kg)\tDIGITE SEU PESO:  ");
//     scanf("%f", &peso);
//     printf(" (cm)\tDIGITE SUA ALTURA: ");
//     scanf("%f", &altura);
//     altura /= 100;
//     sprintf(imc, "%.2f", peso = peso / (altura * altura));
//     for (i = 0; i < strlen(imc); i++)
//     {
//         if (imc[i] == ',')
//         {
//             imc[i] = '.';
//         }
//     }

//     if (connObj.conn = mysql_init(0))
//     {
//         if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//         {
//             sprintf(query, "select idt_User from t_Users where login = '%s' and senha = '%d'", login, senha);
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {
//                 connObj.res = mysql_store_result(connObj.conn);
//                 while (connObj.row = mysql_fetch_row(connObj.res))
//                 {
//                     strcpy(_id, connObj.row[0]);
//                 }
//             }
//             else
//             {
//                 _conStatus00(connObj);
//             }

//             sprintf(query, "INSERT INTO registros (t_Users_idt_User,imc,datahora) VALUES (%s,%s,'%s')", _id, imc, _dateTime());
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {
//                 printf("IMC REGISTRADO COM SUCESSO!\n");
//             }
//             else
//             {
//                 _conStatus00(connObj);
//             }
//             mysql_close(connObj.conn);
//         }
//         else
//         {
//             _conStatus02();
//         }
//     }
//     else
//     {
//         _conStatus03();
//     }
// }

// // EXIBIR TODOS OS REGISTROS DE IMC
// void _BD_exibirImc(char login[20], int senha)
// {

//     _dbSetup();
//     _dbGetConfig(&dbConfig);
//     int i;
//     char _id[5];
//     printf("\n");
//     for (i = 0; i < 35; i++)
//     {
//         printf(" ");
//     }
//     printf("REGISTROS:\n\n");
//     if (connObj.conn = mysql_init(0))
//     {
//         if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//         {
//             char query[200];
//             sprintf(query, "select idt_User from t_Users where login = '%s' and senha = '%d'", login, senha);
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {
//                 connObj.res = mysql_store_result(connObj.conn);
//                 while (connObj.row = mysql_fetch_row(connObj.res))
//                 {
//                     strcpy(_id, connObj.row[0]);
//                 }
//             }
//             else
//             {
//                 _conStatus00(connObj);
//             }

//             fflush(stdin);
//             sprintf(query, "select * from registros where t_Users_idt_User = '%s'", _id);
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {
//                 connObj.res = mysql_store_result(connObj.conn);
//                 int cont = 0, tam = 0;
//                 char reg[40];
//                 while (connObj.row = mysql_fetch_row(connObj.res))
//                 {
//                     cont++;
//                     sprintf(reg, "%d - [ %s ] - IMC: %s\n", cont, connObj.row[3], connObj.row[2]);
//                     tam = strlen(reg);
//                     tam = (80 - tam) / 2;
//                     for (i = 0; i < tam; i++)
//                     {
//                         printf(" ");
//                     }
//                     printf("%s", reg);
//                     for (i = 0; i < 80; i++)
//                     {
//                         printf("-");
//                     }
//                     if (cont == 25)
//                     {
//                         break;
//                     }
//                     fflush(stdout);
//                 }
//             }
//             else
//             {
//                 _conStatus00(connObj);
//             }
//             mysql_close(connObj.conn);
//         }
//         else
//         {
//             _conStatus02();
//         }
//     }
//     else
//     {
//         _conStatus03();
//     }
// }

// // DELETA CONTA CADASTRADA
// void _BD_delCad(char login[20], int senha)
// {

//     _dbSetup();
//     _dbGetConfig(&dbConfig);

//     int senhaR;

//     do
//     {
//         printf(">> DIGITE SUA SENHA PARA CONFIRMAR: ");
//         fflush(stdin);
//         scanf("%d", &senhaR);
//         if (senhaR > 99999)
//         {
//             printf("ERRO! Senha INV�LIDA.\n");
//         }
//     } while (senhaR > 99999);

//     if (senhaR == senha)
//     {
//         if (connObj.conn = mysql_init(0))
//         {
//             if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//             {
//                 char query[200];
//                 sprintf(query, "DELETE FROM t_Users WHERE login = '%s' AND senha = '%d'", login, senha);
//                 connObj.qstate = mysql_query(connObj.conn, query);
//                 if (!connObj.qstate)
//                 {
//                     printf(">> CADASTRO APAGADO COM SUCESSO!\n");
//                 }
//                 else
//                 {
//                     _conStatus00(connObj);
//                 }
//                 mysql_close(connObj.conn);
//             }
//             else
//             {
//                 _conStatus02();
//             }
//         }
//         else
//         {
//             _conStatus03();
//         }
//     }
//     else
//     {
//         printf("ERRO! Senha INCORRETA.\n");
//     }
// }

void _writeConfig(FILE **_config)
{
    t_DBInfo db;

    _getData(&db.host, "%s", "HOST IP", _Warning);
    fprintf(*_config, "%s", db.host);
    fprintf(*_config, "\n");

    _getData(&db.user, "%s", "USUÁRIO", _Warning);
    fprintf(*_config, "%s", db.user);
    fprintf(*_config, "\n");

    _msgDanger("** ATENÇÃO! **", "Caso não haja SENHA, digite null");
    _getData(&db.pass, "%s", "SENHA", _Warning);
    fprintf(*_config, "%s", db.pass);
    fprintf(*_config, "\n");

    _getData(&db.database, "%s", "BANCO DE DADOS", _Warning);
    fprintf(*_config, "%s", db.database);
    fprintf(*_config, "\n");

    _getData(&db.port, "%d", "PORTA", _Warning);
    fprintf(*_config, "%d", db.port);
}

void _dbSetup()
{
    system(CMD_CLEAR);

    _configDb = fopen(fileDb, "r");

    if (_configDb == NULL)
    {
        _configDb = fopen(fileDb, "w+");
        _writeConfig(&_configDb);
        fclose(_configDb);
    }
}

void _dbGetConfig(t_DBInfo *_dbConfig)
{
    char host[sizeof(_dbConfig->host)];
    char user[sizeof(_dbConfig->user)];
    char pass[sizeof(_dbConfig->pass)];
    char database[sizeof(_dbConfig->database)];
    int port;

    _configDb = fopen(fileDb, "r");

    fscanf(_configDb, "%s", host);
    strcpy(_dbConfig->host, host);

    fscanf(_configDb, "\n%s", user);
    strcpy(_dbConfig->user, user);

    fscanf(_configDb, "\n\n%s", pass);
    if (strcmp(pass, "null") == 0)
    {
        strcpy(pass, "");
    }
    strcpy(_dbConfig->pass, pass);

    fscanf(_configDb, "\n\n\n%s", database);
    strcpy(_dbConfig->database, database);

    fscanf(_configDb, "\n\n\n\n%d", &port);
    _dbConfig->port = port;

    fclose(_configDb);
}

void _dbUpdateConfig()
{
    system(CMD_CLEAR);

    _configDb = fopen(fileDb, "w");

    _writeConfig(&_configDb);

    if (ferror(_configDb) == 0)
    {
        fclose(_configDb);
        _confirmOk(">> SUCESSO!", "CONFIGURAÇÕES ALTERADAS.", _Info);
    }
    else
    {
        fclose(_configDb);
        _confirmOk(">> ERRO!", "NÃO FOI POSSIVEL ALTERAR AS CONFIGURAÇÕES.", _Danger);
        sleep(1);
    }
}

void _dbCheckConn()
{
    _dbSetup();
    _dbGetConfig(&dbConfig);

    if ((connObj.conn = mysql_init(0)))
    {
        if ((connObj.conn = mysql_real_connect(
                 connObj.conn,
                 dbConfig.host,
                 dbConfig.user,
                 dbConfig.pass,
                 dbConfig.database,
                 dbConfig.port,
                 NULL,
                 0)))
        {
            char msg[132];
            sprintf(msg, "CONEXÃO OK! BASE DE DADOS: %s\n(%s)", dbConfig.database, _dateTime());
            _confirmOk("Sucesso!", msg, _Info);
            mysql_close(connObj.conn);
        }
        else
        {
            char msg[206];
            sprintf(msg, "IMPOSSÍVEL ESTABELECER CONEXÃO!\n- Verifique se há conexão com a internet.\n- Verifique se as configurações de ACESSO ao BANCO DE DADOS estão CORRETAS.\n- Verifique se o MySQL está ativo (localhost).");
            _confirmOk("ERRO FATAL!", msg, _Danger);
        }
    }
    else
    {
        _confirmOk("ERRO FATAL!", "NÃO foi possivel criar o OBJETO de conexão!", _Danger);
    }
}

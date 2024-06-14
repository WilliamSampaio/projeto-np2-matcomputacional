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
t_User user;

pthread_t soundPthreadId;

int playing = _False;

void user_init(t_User *_user)
{
    _user->id = 0;
    _user->name = "";
    _user->genre = 0;
    _user->login = "";
    _user->password = 0;
}

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

void _msg(char *_title, char *_message, int _status)
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
    }
}

int _confirmYesNo(char *_title, char *_message, int _status)
{
    _msg(_title, _message, _status);
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
    _msg(_title, _message, _status);
    printf("Press any key to continue...");
    setbuf(stdin, NULL);
    getchar();
}

void _getData(void *_var, int _type, char *_message, int _status)
{
    _msg(_message, "", _status);
    printf("::: ");
    switch (_type)
    {
    case _String:
        scanf("%s", (char *)_var);
        break;
    case _Int:
        scanf("%d", (int *)_var);
        break;
    case _Float:
        scanf("%f", (float *)_var);
        break;
    default:
        _msgDanger("ERRO", "Tipo de dado inválido.");
        break;
    }
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
    int rc;                                               /* return value                           */
    char *wav = "sound/Blue (Da Ba Dee) - Eiffel 65.wav"; /* data passed to the new thread          */

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
        // txtExit();
        exit(0);
    }
}

void _logoutTxtOption()
{
    if (user.id != 0)
    {
        char label[29];
        sprintf(label, "LOGOUT (%s%s%s)", BHYEL, user.login, COLOR_RESET);
        _msgSuccess("[10]", label);
        printf("\n");
    }
}

void _processLogout()
{
    if (user.id != 0 && _confirmYesNo("LOGOUT", "Finalizar sessão?", _Warning))
    {
        user_init(&user);
    }
}

void _mainMenu()
{
    system(CMD_CLEAR);
    printf("\n");
    _msgSuccess("MENU PRINCÍPAL", "\n");
    _msgSuccess("[1]", "ROBÔS STAR WARS");
    _msgSuccess("[2]", "IMC COM MySQL");
    printf("\n");
    _msgSuccess("[3]", "CHECAR CONEXÃO COM O BD");
    _msgSuccess("[4]", "ALTERAR CONFIG DE ACESSO AO BD");
    printf("\n");
    _msgSuccess("[5]", "PLAY / STOP MUSICA");
    printf("\n");
    _msgSuccess("[9]", "SOBRE");

    _logoutTxtOption();

    _msgSuccess("[0]", "SAIR");
    printf("\n");

    int op;
    _getData(&op, _Int, "Digite o número da opção", _Success);
    printf("\n");

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
        _imcMenu();
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
    case 5:
        playing ? _stopSound() : _playSound();
        _mainMenu();
        break;
    case 9:
        system(CMD_CLEAR);
        txtTeam();
        _confirmOk("Data/Hora", _dateTime(), _Danger);
        _mainMenu();
        break;
    case 10:
        _processLogout();
        _mainMenu();
        break;
    default:
        _confirmOk("Erro", "Opção inválida.", _Danger);
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
        _msgSuccess("[1]", "RESETAR");
        _msgSuccess("[2]", "MENU PRINCIPAL");
        printf("\n");
        _msgSuccess("[0]", "SAIR");
        printf("\n");

        _getData(&op, _Int, "Digite o número da opção", _Success);
        printf("\n");

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
            _mainMenu();
            break;
        default:
            _confirmOk("Erro", "Opção inválida.", _Danger);
            _starWarsRobos();
            break;
        }
    } while (op < 0 || op > 2);
}

void _startNP2()
{
    user_init(&user);
    _playSound();
    _mainMenu();
}

void _imcTxtTitle()
{
    system(CMD_CLEAR);
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf(":: : : : : : : : SISTEMA - INDICE DE MASSA CORPORAL (com MySQL) : : : : : : : ::\n");
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
}

void _imcMenu()
{
    _imcTxtTitle();
    _msgSuccess("[1]", "ENTRAR");
    _msgSuccess("[2]", "CADASTRE-SE");
    printf("\n");
    _msgSuccess("[9]", "VOLTAR AO MENU PRINCÍPAL");
    printf("\n");

    _logoutTxtOption();

    _msgSuccess("[0]", "SAIR");
    printf("\n");

    int op;
    _getData(&op, _Int, "Digite o número da opção", _Success);
    printf("\n");

    switch (op)
    {
    case 0:
        _exitNP2();
        _imcMenu();
        break;
    case 1:
        _imcLogin();
        _imcMenu();
        break;
    case 2:
        // _imcCad();
        break;
    case 9:
        _mainMenu();
        break;
    case 10:
        _processLogout();
        _imcMenu();
        break;
    default:
        _confirmOk("Erro", "Opção inválida.", _Danger);
        _imcMenu();
        break;
    }
}

void _imcCad()
{
    _imcTxtTitle();
    // _dbCreateUser();
    _imcMenu();
}

void _imcLogin()
{
    char login[20];
    int senha;

    _imcTxtTitle();

    _getData(&login, _String, "LOGIN", _Warning);
    _getData(&senha, _Int, "SENHA", _Warning);

    if (_dbValidateLogin(&user, login, senha))
    {
        return _imcSession();
    }

    printf("\n");
    if (_confirmYesNo("ERRO!", "Login ou senha inválida. Tentar novamente?", _Danger))
    {
        return _imcLogin();
    }
}

void _imcExibirImc()
{

    _BD_exibirImc();
}

// // DELETA CADASTRO DE USU�RIO
// void _imcDelCadImc(char login[20], int senha)
// {

//     _BD_delCad(login, senha);
// }

void _imcSession()
{
    _imcTxtTitle();
    _msgSuccess("[1]", "REGISTRAR NOVO IMC");
    _msgSuccess("[2]", "RELATÓRIO");
    printf("\n");
    _msgSuccess("[4]", "ALTERAR DADOS PESSOAIS");
    printf("\n");
    _msgSuccess("[9]", "VOLTAR AO MENU PRINCÍPAL");
    _msgSuccess("[0]", "SAIR");
    printf("\n");

    _logoutTxtOption();

    _msgSuccess("[-99]", "APAGAR CADASTRO");
    printf("\n");

    int op;
    _getData(&op, _Int, "Digite o número da opção", _Success);
    printf("\n");

    switch (op)
    {
    case 0:
        _exitNP2();
        break;
    case 1:
        _imcAddIMC();
        _imcSession();
        break;
    case 2:
        _imcReport();
        _imcSession();
        break;
    case 4:
        _imcUpdateUser();
        _imcSession();
        break;
    case 9:
        _imcMenu();
        break;
    case 10:
        _processLogout();
        _imcMenu();
        break;
    case -99:
        system(CMD_CLEAR);
        _imcTxtTitle();
        // _BD_delCad(login, senha);
        _confirmOk("Data/Hora", _dateTime(), _Danger);
        _imcSession();
        break;
    default:
        _confirmOk("Erro", "Opção inválida.", _Danger);
        _imcSession();
        break;
    }
}

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
//                         _imcMenu();
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

void _imcUpdateUser()
{
    t_User u;
    u.name = user.name;
    u.genre = user.genre;
    u.login = user.login;
    u.password = user.password;

    _imcTxtTitle();
    _msgSuccess("ATUALIZAR...", "");
    printf("\n");
    _msgInfo("[1] NOME", user.name);
    _msgInfo("[2] SEXO", user.genre == M ? "Masculino" : "Feminino");
    _msgInfo("[3] LOGIN", user.login);
    _msgInfo("[4] SENHA", "***");
    printf("\n");
    _msgSuccess("[0] VOLTAR", "");
    printf("\n");

    int op;
    _getData(&op, _Int, "Digite o número da opção", _Success);
    printf("\n");

    switch (op)
    {
    case 0:
        _imcSession();
        break;
    case 1:
        char n[60];
        _getData(&n, _String, "DIGITE SEU NOME COMPLETO", _Warning);
        u.name = n;
        if (_dbUpdateUser(&user, u))
        {
            printf("\n");
            _confirmOk("SUCESSO!", "Nome do usuário atualizado.", _Success);
            _imcUpdateUser();
        }
        break;
    // case 2:
    //     do
    //     {
    //         char sexo;
    //         fflush(stdin);
    //         printf(">> QUAL SEU SEXO (M / F):\n");
    //         scanf("%c", &sexo);
    //         update.sexo = toupper(sexo);
    //         if (update.sexo != 'M' && update.sexo != 'F')
    //         {
    //             printf("ERRO! Alternativa inv�lida.\n");
    //         }
    //     } while (update.sexo != 'M' && update.sexo != 'F');
    //     break;
    // case 3:

    //     do
    //     {
    //         int spc;
    //         do
    //         {
    //             spc = 0;
    //             do
    //             {
    //                 fflush(stdin);
    //                 printf(">> NOME DE USU�RIO (MAX - 20):\n");
    //                 fgets(update.login);
    //                 if (strlen(update.login) > 20)
    //                 {
    //                     printf("ERRO! Nome de usu�rio deve ter no maximo 20 caracteres.\n");
    //                 }
    //             } while (strlen(update.login) > 20);

    //             for (cont = 0; cont < strlen(update.login); cont++)
    //             {
    //                 if (update.login[cont] == ' ')
    //                 {
    //                     printf("ERRO! N�o pode haver espa�os.\n");
    //                     spc = 1;
    //                 }
    //                 break;
    //             }
    //         } while (spc == 1);
    //         if (_BD_validarUserName(update.login) == 1)
    //         {
    //             printf("Login j� utilizado por outro usu�rio :(\n");
    //         }
    //         else
    //         {
    //             if (_BD_validarUserName(update.login) == -1)
    //             {
    //                 erro = 1;
    //             }
    //             else
    //             {
    //                 if (_BD_validarUserName(update.login) == -2)
    //                 {
    //                     erro = 1;
    //                     _conStatus02();
    //                 }
    //                 else
    //                 {
    //                     if (_BD_validarUserName(update.login) == -3)
    //                     {
    //                         erro = 1;
    //                         _conStatus03();
    //                     }
    //                     else
    //                     {
    //                         erro = 0;
    //                     }
    //                 }
    //             }
    //         }
    //     } while (erro != 0);
    //     break;
    // case 4:
    //     do
    //     {
    //         do
    //         {
    //             printf(">> DIGITE UMA SENHA (APENAS N�MEROS, MAX - 5):\n");
    //             fflush(stdin);
    //             scanf("%d", &update.senha);
    //             if (update.senha > 99999)
    //             {
    //                 printf("ERRO! Senha deve ter no maximo 5 digitos.\n");
    //             }
    //         } while (update.senha > 99999);

    //         printf(">> REPITA A SENHA DE ACESSO:\n");
    //         fflush(stdin);
    //         scanf("%d", &senhaR);
    //         if (senhaR != update.senha)
    //         {
    //             printf("ERRO! Senhas n�o coincidem.\n");
    //         }
    //     } while (senhaR != update.senha);
    //     break;
    default:
        _confirmOk("Erro", "Opção inválida.", _Danger);
        _imcUpdateUser();
        break;
    }
}

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

void _imcReport()
{
    _imcTxtTitle();

    t_IMC *values = _dbGetIMCbyUserId(&user);

    printf("+----------------------------------------------------------------+\n");
    printf("| %sNOME: %s%s%s\t\t\t\t\t\t |\n", BHCYN, BHYEL, user.name, COLOR_RESET);

    if (values != NULL)
    {
        int contReg = 0;
        float contRegTotal = 0;
        float media;
        char ultimo_reg[22];

        strcpy(ultimo_reg, "NULL");

        printf("+----------------------------------------------------------------+\n");
        printf("|%s\tID\t%s|%s\tIMC\t%s|%s           DATA HORA            %s|\n",
               BHCYN,
               COLOR_RESET,
               BHCYN,
               COLOR_RESET,
               BHCYN,
               COLOR_RESET);
        printf("+----------------------------------------------------------------+\n");

        for (int i = 0; i < sizeof(values); i++)
        {
            printf("|%s\t%d\t%s| %s%.2f\t\t%s|     %s%s%s     |\n",
                   BHYEL,
                   values[i].id,
                   COLOR_RESET,
                   BHYEL,
                   values[i].imc,
                   COLOR_RESET,
                   BHYEL,
                   values[i].datetime,
                   COLOR_RESET);

            contReg++;
            contRegTotal += values[i].imc;
            strcpy(ultimo_reg, values[i].datetime);
        }

        if (contReg != 0)
        {
            media = contRegTotal / contReg;
        }
        else
        {
            media = 0;
        }

        printf("+----------------------------------------------------------------+\n");
        printf("| %sRegistros: %s%d%s\t| %sMédia: %s%.2f%s \t| %sÚltimo: %s%s%s |\n",
               BHCYN,
               BHYEL,
               contReg,
               COLOR_RESET,
               BHCYN,
               BHYEL,
               media,
               COLOR_RESET,
               BHCYN,
               BHYEL,
               ultimo_reg,
               COLOR_RESET);
    }

    printf("+----------------------------------------------------------------+\n");
    printf("\n");
    _confirmOk("Data/Hora", _dateTime(), _Danger);
}

void _imcAddIMC()
{
    _imcTxtTitle();

    float peso, altura, IMC;

    fflush(stdin);

    _getData(&peso, _Float, "IMC - (Kg)\tDIGITE SEU PESO", _Warning);
    _getData(&altura, _Float, "IMC - (cm)\tDIGITE SUA ALTURA", _Warning);

    altura /= 100;

    IMC = peso / (altura * altura);

    if (!_dbInsertIMC(&user, IMC))
    {
        _msgDanger("ERRO!", "Falha em inserir novo IMC.");
    }
    else
    {
        _msgSuccess("OBA!", "IMC registrado com sucesso.");
    }

    printf("\n");
    _confirmOk("Data/Hora", _dateTime(), _Danger);
}

void _BD_exibirImc()
{
    _dbSetup();
    _dbGetConfig(&dbConfig);

    if (!_dbInit() || !_dbConnect(&dbConfig))
    {
        return;
    }

    printf("\tREGISTROS:\n\n");

    char query[200];

    fflush(stdin);
    sprintf(query, "SELECT * FROM registros WHERE usuarios_id = '%d'", user.id);

    if (
        mysql_query(connObj.conn, query) != MYSQL_STATUS_READY ||
        ((connObj.res = mysql_store_result(connObj.conn)) && (int)mysql_num_rows(connObj.res) == 0))
    {
        _msgDanger("ERRO!", "Nenhum registro encontrado.");
        mysql_close(connObj.conn);
        return;
    }

    int cont = 1;
    char reg[40];

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(connObj.res)))
    {
        sprintf(reg, "\t%d - [ %s ] - IMC: %s\n", cont, row[3], row[2]);
        printf("%s", reg);
        fflush(stdout);
        cont++;
    }
    printf("\n");
    mysql_close(connObj.conn);
}

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

    _getData(&db.host, _String, "HOST IP", _Warning);
    fprintf(*_config, "%s", db.host);
    fprintf(*_config, "\n");

    _getData(&db.user, _String, "USUÁRIO", _Warning);
    fprintf(*_config, "%s", db.user);
    fprintf(*_config, "\n");

    _msgDanger("** ATENÇÃO! **", "Caso não haja SENHA, digite null");
    _getData(&db.pass, _String, "SENHA", _Warning);
    fprintf(*_config, "%s", db.pass);
    fprintf(*_config, "\n");

    _getData(&db.database, _String, "BANCO DE DADOS", _Warning);
    fprintf(*_config, "%s", db.database);
    fprintf(*_config, "\n");

    _getData(&db.port, _Int, "PORTA", _Warning);
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

int _dbInit()
{
    connObj.conn = mysql_init(0);
    if (!connObj.conn)
    {
        _confirmOk("ERRO FATAL!", "NÃO foi possivel criar o OBJETO de conexão!", _Danger);
        return _False;
    }
    return _True;
}

int _dbConnect(t_DBInfo *_dbConfig)
{
    connObj.conn = mysql_real_connect(
        connObj.conn,
        _dbConfig->host,
        _dbConfig->user,
        _dbConfig->pass,
        _dbConfig->database,
        _dbConfig->port,
        NULL,
        0);
    if (!connObj.conn)
    {
        char msg[206];
        sprintf(msg, "IMPOSSÍVEL ESTABELECER CONEXÃO!\n- Verifique se há conexão com a internet.\n- Verifique se as configurações de ACESSO ao BANCO DE DADOS estão CORRETAS.\n- Verifique se o MySQL está ativo (localhost).");
        _confirmOk("ERRO FATAL!", msg, _Danger);
        return _False;
    }
    return _True;
}

void _dbCheckConn()
{
    _dbSetup();
    _dbGetConfig(&dbConfig);

    if (!_dbInit() || !_dbConnect(&dbConfig))
    {
        return;
    }

    char msg[132];
    sprintf(msg, "CONEXÃO OK! BASE DE DADOS: %s\n(%s)", dbConfig.database, _dateTime());
    _confirmOk("Sucesso!", msg, _Info);

    mysql_close(connObj.conn);
}

int _dbValidateLogin(t_User *_user, char *_login, int _password)
{
    // _dbSetup();
    _dbGetConfig(&dbConfig);

    if (!_dbInit() || !_dbConnect(&dbConfig))
    {
        return _False;
    }

    char query[200];
    sprintf(query, "SELECT * FROM usuarios WHERE login = '%s' AND senha = %d", _login, _password);

    if (
        mysql_query(connObj.conn, query) != MYSQL_STATUS_READY ||
        ((connObj.res = mysql_store_result(connObj.conn)) && (int)mysql_num_rows(connObj.res) == 0))
    {
        mysql_close(connObj.conn);
        return _False;
    }

    MYSQL_ROW row = mysql_fetch_row(connObj.res);

    _user->id = atoi(row[0]);
    _user->name = row[1];

    _user->genre = row[2][0] == "M"[0] ? M : F;
    _user->login = row[3];
    _user->password = atoi(row[4]);

    return _True;
}

int _dbInsertIMC(t_User *_user, float _imc)
{
    // _dbSetup();
    _dbGetConfig(&dbConfig);

    if (!_dbInit() || !_dbConnect(&dbConfig))
    {
        return _False;
    }

    char query[200];
    sprintf(query, "INSERT INTO registros (usuarios_id,imc,datahora) VALUES (%d,%f,'%s')",
            _user->id,
            _imc,
            _dateTime());

    if (
        mysql_query(connObj.conn, query) != MYSQL_STATUS_READY ||
        (int)mysql_affected_rows(connObj.conn) == 0)
    {
        mysql_close(connObj.conn);
        return _False;
    }

    mysql_close(connObj.conn);
    return _True;
}

int _dbUpdateUser(t_User *_user, t_User _updated_user)
{
    // _dbSetup();
    _dbGetConfig(&dbConfig);

    if (!_dbInit() || !_dbConnect(&dbConfig))
    {
        return _False;
    }

    char s = _updated_user.genre == M ? 'M' : 'F';

    char query[200];
    sprintf(query, "UPDATE usuarios SET nome = '%s', sexo = '%c', login = '%s', senha = %d WHERE id = %d",
            _updated_user.name,
            s,
            _updated_user.login,
            _updated_user.password,
            _user->id);

    if (
        mysql_query(connObj.conn, query) != MYSQL_STATUS_READY ||
        (int)mysql_affected_rows(connObj.conn) == 0)
    {
        mysql_close(connObj.conn);
        return _False;
    }

    _user->name = _updated_user.name;
    _user->genre = _updated_user.genre;
    _user->login = _updated_user.login;
    _user->password = _updated_user.password;

    return _True;
}

t_IMC *_dbGetIMCbyUserId(t_User *_user)
{
    // _dbSetup();
    _dbGetConfig(&dbConfig);

    if (!_dbInit() || !_dbConnect(&dbConfig))
    {
        return NULL;
    }

    char query[200];
    sprintf(query, "SELECT * FROM registros WHERE usuarios_id = %d", _user->id);

    if (
        mysql_query(connObj.conn, query) != MYSQL_STATUS_READY ||
        ((connObj.res = mysql_store_result(connObj.conn)) && (int)mysql_num_rows(connObj.res) == 0))
    {
        mysql_close(connObj.conn);
        return NULL;
    }

    t_IMC *values = malloc(sizeof(t_IMC) * mysql_num_rows(connObj.res));
    if (!values)
        return NULL;

    MYSQL_ROW row;

    int cont = 0;
    while ((row = mysql_fetch_row(connObj.res)))
    {
        t_IMC t;
        t.id = atoi(row[0]);
        t.user_id = atoi(row[1]);
        t.imc = (float)atof(row[2]);
        t.datetime = row[3];
        values[cont] = t;
        cont++;
    }

    mysql_close(connObj.conn);
    return values;
}

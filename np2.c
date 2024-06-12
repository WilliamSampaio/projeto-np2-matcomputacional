#ifdef _WIN32
#include <windows.h>
#elif linux
#include <unistd.h>
#endif

#include <time.h>
#include <stdio.h>
#include <locale.h>
#include <mysql/mysql.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include "np2.h"
#include "np2txt.h"

const SDL_MessageBoxColorScheme _colorScheme = {
    {/* .colors (.r, .g, .b) */
     /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
     {255, 255, 255},
     /* [SDL_MESSAGEBOX_COLOR_TEXT] */
     {0, 0, 0},
     /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
     {240, 240, 240},
     /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
     {240, 240, 240},
     /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
     {200, 200, 200}}};

const char *fileDb = "configdb";

FILE *_configDb;

t_MySQLConn connObj;
t_DBInfo dbConfig;

int _confirmMessageBox(char *title, char *message)
{
    SDL_MessageBoxButtonData btns[] = {
        {/* .flags, .buttonid, .text */ 0, 0, "Não"},
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Sim"},
        {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancelar"},
    };
    SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL,                       /* .window */
        title,                      /* .title */
        message,                    /* .message */
        SDL_arraysize(btns),        /* .numbuttons */
        btns,                       /* .buttons */
        &_colorScheme               /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
    {
        SDL_Log("error displaying message box");
        exit(1);
    }
    if (buttonid == -1)
    {
        SDL_Log("no selection");
    }
    return buttonid;
}

void _okMessageBox(char *title, char *message)
{
    SDL_MessageBoxButtonData btns[] = {
        {/* .flags, .buttonid, .text */ 0, 0, "OK"},
    };
    SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL,                       /* .window */
        title,                      /* .title */
        message,                    /* .message */
        SDL_arraysize(btns),        /* .numbuttons */
        btns,                       /* .buttons */
        &_colorScheme               /* .colorScheme */
    };
    int buttonid;
    SDL_ShowMessageBox(&messageboxdata, &buttonid);
}

char *dataHora()
{
    return __DATE__ " - " __TIME__;
}

void ptBrCaracteres()
{
    setlocale(LC_ALL, "Portuguese");
}

// int _conStatus01(char *_database)
// {

//     char str[100];
//     sprintf(str, "CONEX�O OK! BASE DE DADOS: %s\n(%s)", _database, dataHora());
//     // MessageBox(NULL, str, "Conex�o Status", MB_OK | MB_ICONINFORMATION);
//     return 1;
// }

// int _conStatus02()
// {

//     char str[200];
//     sprintf(str, "IMPOSS�VEL ESTABELECER CONEX�O!\n- Verifique se h� conex�o com a internet.\n- Verifique se as configura��es de ACESSO ao BANCO DE DADOS est�o CORRETAS.\n- Verifique se o MySQL est� ativo (localhost).");
//     // MessageBox(NULL, str, "Conex�o Status", MB_OK | MB_ICONSTOP);
//     return 0;
// }

// int _conStatus03()
// {

//     char str[100];
//     sprintf(str, "ERRO! N�O foi possivel criar o OBJETO de conex�o.");
//     // MessageBox(NULL, str, "Conex�o Status", MB_OK | MB_ICONWARNING);
//     return -1;
// }

// void _conStatus00(t_MySQLConn _con)
// {

//     char str[100];
//     sprintf(str, "ERRO: %s\n", mysql_error(_con.conn));
//     // MessageBox(NULL, str, "Conex�o Status", MB_OK | MB_ICONWARNING);
// }

void _exitNP2()
{
    system(CMD_CLEAR);
    txtExit();
    exit(0);
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
        if (_confirmMessageBox("SAIR", "Você deseja realmente SAIR?") == 1)
        {
            _exitNP2();
        }
        _mainMenu();
        break;
    case 1:
        _starWarsRobos();
        break;
    // case 2:
    //     _imcPrincipal();
    //     break;
    case 3:
        _dbCheckConn();
        _mainMenu();
        break;
    case 4:
        _dbUpdateConfig();
        _mainMenu();
        break;
    // case 9:
    //     playPause();
    //     _startNP2(0);
    //     break;
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
            if (_confirmMessageBox("SAIR", "Você deseja realmente SAIR?") == 1)
            {
                _exitNP2();
            }
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

// // INICIA / PARA A MUSICA
// void playPause(void)
// {

//     int pid = 0;
//     FILE *pid_;

//     pid_ = fopen("sound/status", "r");

//     fscanf(pid_, "%d", &pid);

//     if (pid == 0)
//     {
//         WinExec("sound/sound.exe", SW_HIDE);
//         fclose(pid_);
//         return;
//     }
//     else
//     {
//         char kill[100];
//         sprintf(kill, "taskkill /f /pid %d", pid);
//         system(kill);
//         system(CMD_CLEAR);
//         pid_ = fopen("sound/status", "w");
//         fprintf(pid_, "");
//         fclose(pid_);
//         return;
//     }
// }

void _startNP2()
{
    _dbCheckConn();
    _mainMenu(0);
}

// /////////////////////////////////////////////////////////////////////////////////////////////
// //
// //      FUN��ES COM O PREFIXO "_imc" SE REFEREM AO SISTEMA IMC.
// //
// /////////////////////////////////////////////////////////////////////////////////////////////

// // IMPRIME A TELA INICIAL DO SISTEMA
// void _imcPrincipal(void)
// {

//     _imcTitulo();
//     _imcMenu();
// }

// // IMPRIME TITULO DO SISTEMA
// void _imcTitulo(void)
// {
//     int i;
//     system(CMD_CLEAR);
//     for (i = 0; i < 80; i++)
//     {
//         printf("%c", 26);
//     }
//     printf("%c                 SISTEMA - INDICE DE MASSA CORPORAL (com MySQL)               %c", 24, 25);
//     for (i = 0; i < 80; i++)
//     {
//         printf("%c", 27);
//     }
// }

// // IMPRIME MENU PRINC�PAL DO SISTEMAS
// void _imcMenu(void)
// {

//     int op;
//     printf("\t- [1]ENTRAR\n");
//     printf("\t- [2]CADASTRE-SE\n");
//     printf("\n");
//     printf("\t- [9]VOLTAR AO MENU PRINC�PAL\n");
//     printf("\t- [0]SAIR\n");
//     printf("\n\t");
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
//             _imcPrincipal();
//         }
//         break;
//     case 1:
//         _imcEntrar();
//         break;
//     case 2:
//         _imcCad();
//         break;
//     case 9:
//         _startNP2(0);
//         break;
//     default:
//         MessageBox(NULL, "Op��o inv�lida!", "ERRO!", MB_OK | MB_ICONERROR);
//         _imcPrincipal();
//         break;
//     }
// }

// // TELA DE CADASTRO DE NOVOS USU�RIOS
// void _imcCad(void)
// {

//     _imcTitulo();
//     _BD_cadastrarUser();
//     system("pause");
//     _imcPrincipal();
// }

// // LOGIN DE ACESSO AO SISTEMA
// void _imcEntrar(void)
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

// /////////////////////////////////////////////////////////////////////////////////////////////
// //
// //      FUN��ES COM O PREFIXO "_BD_" ACESSAM O BANCO DE DADOS.
// //
// /////////////////////////////////////////////////////////////////////////////////////////////

// // CADASTRAR NO BD UM NOVO USU�RIO
// int _BD_cadastrarUser(void)
// {

//     t_MySQLConn con;
//     t_DBInfo bd;
//     _dbSetup();
//     _dbGetConfig(&dbConfig);

//     t_User novo;
//     int cont;

//     int espaco = 0;
//     do
//     {
//         fflush(stdin);
//         printf(">> DIGITE SEU NOME COMPLETO:\n");
//         fgets(novo.nome);
//         strupr(novo.nome);
//         for (cont = 0; cont < strlen(novo.nome); cont++)
//         {
//             if (novo.nome[cont] == ' ')
//             {
//                 espaco = 1;
//             }
//         }
//         if (espaco == 0)
//         {
//             printf("ERRO! Nome inv�lido.\n");
//         }
//     } while (espaco == 0);
//     do
//     {
//         char sexo;
//         fflush(stdin);
//         printf(">> QUAL SEU SEXO (M / F):\n");
//         scanf("%c", &sexo);
//         novo.sexo = toupper(sexo);
//         if (novo.sexo != 'M' && novo.sexo != 'F')
//         {
//             printf("ERRO! Alternativa inv�lida.\n");
//         }
//     } while (novo.sexo != 'M' && novo.sexo != 'F');

//     int erro;
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
//                 fgets(novo.login);
//                 if (strlen(novo.login) > 20)
//                 {
//                     printf("ERRO! Nome de usu�rio deve ter no maximo 20 caracteres.\n");
//                 }
//             } while (strlen(novo.login) > 20);

//             for (cont = 0; cont < strlen(novo.login); cont++)
//             {
//                 if (novo.login[cont] == ' ')
//                 {
//                     printf("ERRO! N�o pode haver espa�os.\n");
//                     spc = 1;
//                 }
//                 break;
//             }
//         } while (spc == 1);
//         if (_BD_validarUserName(novo.login) == 1)
//         {
//             printf("Login j� utilizado por outro usu�rio :(\n");
//         }
//         else
//         {
//             if (_BD_validarUserName(novo.login) == -1)
//             {
//                 erro = 1;
//             }
//             else
//             {
//                 if (_BD_validarUserName(novo.login) == -2)
//                 {
//                     erro = 1;
//                     _conStatus02();
//                 }
//                 else
//                 {
//                     if (_BD_validarUserName(novo.login) == -3)
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

//     int senhaR;
//     do
//     {
//         do
//         {
//             printf(">> DIGITE UMA SENHA (APENAS N�MEROS, MAX - 5):\n");
//             fflush(stdin);
//             scanf("%d", &novo.senha);
//             if (novo.senha > 99999)
//             {
//                 printf("ERRO! Senha deve ter no maximo 5 digitos.\n");
//             }
//         } while (novo.senha > 99999);

//         printf(">> REPITA A SENHA DE ACESSO:\n");
//         fflush(stdin);
//         scanf("%d", &senhaR);
//         if (senhaR != novo.senha)
//         {
//             printf("ERRO! Senhas n�o coincidem.\n");
//         }
//     } while (senhaR != novo.senha);

//     if (connObj.conn = mysql_init(0))
//     {
//         if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//         {
//             char query[200];
//             sprintf(query, "INSERT INTO t_Users (nome, sexo, login, senha) VALUES ('%s','%c','%s','%d')", novo.nome, novo.sexo, novo.login, novo.senha);
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {
//                 printf("DADOS INSERIDOS COM SUCESSO!\n");
//             }
//             else
//             {
//                 int op;
//                 printf("ERRO! Algo deu errado...\n");
//                 printf(" [1] - Tentar Novamente / [2] - voltar\n");
//                 do
//                 {
//                     printf(" ");
//                     scanf("%d", &op);
//                     if (op == 1)
//                     {
//                         system(CMD_CLEAR);
//                         _imcCad();
//                     }
//                     else
//                     {
//                         if (op == 2)
//                         {
//                             _imcPrincipal();
//                         }
//                         else
//                         {
//                             printf("Op��o Inv�lida! :(");
//                         }
//                     }
//                 } while (op != 1 && op != 2);
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

// // PEGA DADOS DO t_User LOGADO
// void _BD_pegarUserInfo(char login[20], int senha)
// {

//     _dbSetup();
//     _dbGetConfig(&dbConfig);

//     if (connObj.conn = mysql_init(0))
//     {
//         if (connObj.conn = mysql_real_connect(connObj.conn, dbConfig.host, dbConfig.user, dbConfig.pass, dbConfig.database, dbConfig.port, NULL, 0))
//         {

//             int id;
//             int i;
//             int contReg = 0;
//             float contRegTotal = 0;
//             float media;
//             char ultimoReg[22];
//             char info[80];

//             strcpy(ultimoReg, "NULL");

//             char query[200];
//             sprintf(query, "select idt_User,nome,sexo,login,senha from t_Users where login = '%s' and senha = '%d'", login, senha);
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {
//                 connObj.res = mysql_store_result(connObj.conn);
//                 while (connObj.row = mysql_fetch_row(connObj.res))
//                 {
//                     id = atoi(connObj.row[0]);
//                     int charCont = (80 - (10 + strlen(connObj.row[1]))) / 2;
//                     for (i = 0; i < charCont; i++)
//                     {
//                         printf(" ");
//                     }
//                     printf("BEM-VIND");
//                     if (strcmp(connObj.row[2], "M") == 0)
//                     {
//                         printf("O");
//                     }
//                     else
//                     {
//                         printf("A");
//                     }
//                     printf(" %s", connObj.row[1]);
//                     printf("\n");
//                 }
//             }
//             else
//             {
//                 _conStatus00(connObj);
//                 mysql_close(connObj.conn);
//             }

//             sprintf(query, "SELECT * FROM registros WHERE t_Users_idt_User = '%d'", id);
//             connObj.qstate = mysql_query(connObj.conn, query);
//             if (!connObj.qstate)
//             {

//                 connObj.res = mysql_store_result(connObj.conn);
//                 while (connObj.row = mysql_fetch_row(connObj.res))
//                 {
//                     contReg++;
//                     contRegTotal += atof(connObj.row[2]);
//                     strcpy(ultimoReg, connObj.row[3]);
//                 }

//                 if (contReg != 0)
//                 {
//                     media = contRegTotal / contReg;
//                 }
//                 else
//                 {
//                     media = 0;
//                 }

//                 printf("     ");
//                 for (i = 0; i < 70; i++)
//                 {
//                     printf("-");
//                 }
//                 printf("\n");

//                 char str[24];
//                 sprintf(info, " %d - Registros | M�dia: %.2f | �ltimo imc [", contReg, media);
//                 sprintf(str, "%s]", ultimoReg);
//                 strcat(info, str);

//                 int tam = strlen(info);
//                 tam = (80 - tam) / 2;
//                 for (i = 0; i < tam; i++)
//                 {
//                     printf(" ");
//                 }
//                 printf("%s", info);
//                 printf("\n");

//                 printf("     ");
//                 for (i = 0; i < 70; i++)
//                 {
//                     printf("-");
//                 }
//                 printf("\n");
//             }
//             else
//             {
//                 _conStatus00(connObj);
//                 mysql_close(connObj.conn);
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

//             sprintf(query, "INSERT INTO registros (t_Users_idt_User,imc,datahora) VALUES (%s,%s,'%s')", _id, imc, dataHora());
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

void _dbSetup()
{
    t_DBInfo db;
    _configDb = fopen(fileDb, "r");

    if (_configDb == NULL)
    {
        _configDb = fopen(fileDb, "w+");

        printf("-- SERVIDOR / IP:  ");
        scanf("%s", db.host);
        fprintf(_configDb, "%s", db.host);
        fprintf(_configDb, "\n");

        printf("-- USUÁRIO:        ");
        scanf("%s", db.user);
        fprintf(_configDb, "%s", db.user);
        fprintf(_configDb, "\n");

        printf("! * Caso não haja SENHA, digite null\n");
        printf("-- SENHA:          ");
        scanf("%s", db.pass);
        fprintf(_configDb, "%s", db.pass);
        fprintf(_configDb, "\n");

        printf("-- BANCO DE DADOS: ");
        scanf("%s", db.database);
        fprintf(_configDb, "%s", db.database);
        fprintf(_configDb, "\n");

        printf("-- PORTA:          ");
        scanf("%d", &db.port);
        fprintf(_configDb, "%d", db.port);

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
    t_DBInfo db;
    _configDb = fopen(fileDb, "w");

    printf("-- SERVIDOR / IP:  ");
    scanf("%s", db.host);
    fprintf(_configDb, "%s", db.host);
    fprintf(_configDb, "\n");

    printf("-- USUÁRIO:        ");
    scanf("%s", db.user);
    fprintf(_configDb, "%s", db.user);
    fprintf(_configDb, "\n");

    printf("! * Caso não haja SENHA, digite null\n");
    printf("-- SENHA:          ");
    scanf("%s", db.pass);
    fprintf(_configDb, "%s", db.pass);
    fprintf(_configDb, "\n");

    printf("-- BANCO DE DADOS: ");
    scanf("%s", db.database);
    fprintf(_configDb, "%s", db.database);
    fprintf(_configDb, "\n");

    printf("-- PORTA:          ");
    scanf("%d", &db.port);
    fprintf(_configDb, "%d", db.port);

    if (ferror(_configDb) == 0)
    {
        fclose(_configDb);
        printf(">> CONFIGURAÇÕES ALTERADAS COM SUCESSO!\n");
        _dbGetConfig(&dbConfig);
    }
    else
    {
        fclose(_configDb);
        printf(">> ERRO! NÃO FOI POSSIVEL ALTERAR AS CONFIGURAÇÕES.\n");
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
            sprintf(msg, "CONEXÃO OK! BASE DE DADOS: %s\n(%s)", dbConfig.database, dataHora());
            _okMessageBox("Sucesso!", msg);
            mysql_close(connObj.conn);
        }
        else
        {
            char msg[206];
            sprintf(msg, "IMPOSSÍVEL ESTABELECER CONEXÃO!\n- Verifique se há conexão com a internet.\n- Verifique se as configurações de ACESSO ao BANCO DE DADOS estão CORRETAS.\n- Verifique se o MySQL está ativo (localhost).");
            _okMessageBox("ERRO FATAL!", msg);
        }
    }
    else
    {
        _okMessageBox("ERRO FATAL!", "NÃO foi possivel criar o OBJETO de conexão!");
    }
}

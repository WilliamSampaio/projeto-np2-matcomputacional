#include <locale.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "constants.h"
#include "database.h"
#include "np2.h"
#include "np2txt.h"
#include "terminal.h"

const char *CONFIG_DB_FILENAME = "configdb";

FILE *_config_db_file;

conn_info_t conn_info;
MYSQL *conn;
tbl_user_t user;

pthread_t sound_pthread_id;

int playing = _False;

void _user_init(tbl_user_t *_user)
{
    strcpy(_user->name, "");
    strcpy(_user->login, "");
    _user->id = 0;
    _user->genre = 0;
    _user->password = 0;
}

void _connect()
{
    _dbSetup();
    _dbGetConfig(&conn_info);
    conn = get_conn(&conn_info);
    if (conn == NULL)
    {
        _confirm("ERRO!", "Conexão falhou.", "Pressione qualquer tecla para continuar...", _Danger);
        return;
    }
    _confirm("SUCESSO!", "Conexão estabelecida. " _DATETIME_, "Pressione qualquer tecla para continuar...", _Success);
}

void _get_data(void *_var, int _type, char *_message, int _status)
{
    setbuf(stdin, NULL);
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

void _set_ptbr_locale()
{
    setlocale(LC_ALL, "Portuguese");
}

void *_sdl2_play_sound(void *_wavFilename)
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

void _play_sound()
{
    int rc;                                               /* return value                           */
    char *wav = "sound/Blue (Da Ba Dee) - Eiffel 65.wav"; /* data passed to the new thread          */

    /* create a new thread that will execute 'playSound' */
    rc = pthread_create(&sound_pthread_id, NULL, _sdl2_play_sound, (void *)wav);
    if (rc) /* could not create thread */
    {
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    playing = _True;
}

void _stop_sound()
{
    pthread_cancel(sound_pthread_id);
    playing = _False;
}

void _exit_()
{
    if (_confirm_options("SAIR", "Você deseja realmente SAIR?", "Confirmar", 'S', 'N', _Danger) == _True)
    {
        close_conn(&conn);
        _clear_terminal();
        txtExit();
        exit(0);
    }
}

void _logout_txt_option()
{
    if (user.id != 0)
    {
        char label[60];
        sprintf(label, "LOGOUT (%s%s%s)", BHYEL, user.login, COLOR_RESET);
        _msgSuccess("[10]", label);
        printf("\n");
    }
}

void _process_logout()
{
    if (user.id != 0 && _confirm_options("LOGOUT", "Finalizar sessão?", "Confirmar", 'S', 'N', _Warning) == _True)
    {
        _user_init(&user);
    }
}

void _main_menu()
{
    _clear_terminal();
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

    _logout_txt_option();

    _msgSuccess("[0]", "SAIR");
    printf("\n");

    int op;
    _get_data(&op, _Int, "Digite o número da opção", _Success);
    printf("\n");

    switch (op)
    {
    case 0:
        _exit_();
        _main_menu();
        break;
    case 1:
        _star_wars_robos();
        break;
    case 2:
        (user.id != 0) ? _imcSession() : _imcMenu();
        break;
    case 3:
        _connect();
        _main_menu();
        break;
    case 4:
        _dbUpdateConfig();
        _connect();
        _main_menu();
        break;
    case 5:
        playing ? _stop_sound() : _play_sound();
        _main_menu();
        break;
    case 9:
        _clear_terminal();
        txtTeam();
        _confirm("Data/Hora", _DATETIME_, "Continuar", _Danger);
        _main_menu();
        break;
    case 10:
        _process_logout();
        _main_menu();
        break;
    default:
        _confirm("Erro", "Opção inválida.", "Continuar", _Danger);
        _main_menu();
        break;
    }
}

void _star_wars_robos()
{
    _clear_terminal();
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

        _get_data(&op, _Int, "Digite o número da opção", _Success);
        printf("\n");

        switch (op)
        {
        case 0:
            _exit_();
            _star_wars_robos();
            break;
        case 1:
            _star_wars_robos();
            break;
        case 2:
            _main_menu();
            break;
        default:
            _confirm("Erro", "Opção inválida.", "Continuar", _Danger);
            _star_wars_robos();
            break;
        }
    } while (op < 0 || op > 2);
}

void _start_()
{
    _connect();
    _user_init(&user);
    _play_sound();
    _main_menu();
}

void _imcTxtTitle()
{
    _clear_terminal();
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf(":: : : : : : : : SISTEMA - INDICE DE MASSA CORPORAL (com MySQL) : : : : : : : ::\n");
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
}

void _imcLogin()
{
    char login[21];
    int senha;

    _imcTxtTitle();

    _get_data(&login, _String, "LOGIN", _Warning);
    _get_data(&senha, _Int, "SENHA", _Warning);

    if (_dbValidateLogin(&user, login, senha, &conn))
    {
        return _imcSession();
    }

    printf("\n");
    if (_confirm_options("ERRO!", "Login ou senha inválida.", "Tentar novamente?", 'S', 'N', _Danger))
    {
        return _imcLogin();
    }
}

void _imcMenu()
{
    _imcTxtTitle();
    _msgSuccess("[1]", "ENTRAR");
    _msgSuccess("[2]", "CADASTRE-SE");
    printf("\n");
    _msgSuccess("[9]", "VOLTAR AO MENU PRINCÍPAL");
    printf("\n");

    _logout_txt_option();

    _msgSuccess("[0]", "SAIR");
    printf("\n");

    int op;
    _get_data(&op, _Int, "Digite o número da opção", _Success);
    printf("\n");

    switch (op)
    {
    case 0:
        _exit_();
        _imcMenu();
        break;
    case 1:
        _imcLogin();
        _imcMenu();
        break;
    case 2:
        _imcAddUser();
        break;
    case 9:
        _main_menu();
        break;
    default:
        _confirm("Erro", "Opção inválida.", "Continuar", _Danger);
        _imcMenu();
        break;
    }
}

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

    _logout_txt_option();

    _msgSuccess("[-99]", "APAGAR CADASTRO");
    printf("\n");

    int op;
    _get_data(&op, _Int, "Digite o número da opção", _Success);
    printf("\n");

    switch (op)
    {
    case 0:
        _exit_();
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
        (user.id != 0) ? _main_menu() : _imcMenu();
        break;
    case 10:
        _process_logout();
        _imcMenu();
        break;
    case -99:
        _imcDeleteUser();
        break;
    default:
        _confirm("Erro", "Opção inválida.", "Continuar", _Danger);
        _imcSession();
        break;
    }
}

void _imcAddUser()
{
    setbuf(stdin, NULL);
    tbl_user_t n_user;

    _imcTxtTitle();
    _msgSuccess("NOVO USUÁRIO", "");
    printf("\n");

    do
    {
        char n1[61], n2[61], fn[122];
        _get_data(&n1, _String, "DIGITE SEU NOME", _Warning);
        _get_data(&n2, _String, "DIGITE SEU SOBRENOME", _Warning);
        sprintf(fn, "%s %s", n1, n2);
        if (strlen(fn) > 61)
        {
            printf("\n");
            _msgDanger("ERRO!", "Nome maior que 60 letras.");
            continue;
        }
        for (int i = 0; i < strlen(fn); i++)
        {
            fn[i] = toupper(fn[i]);
        }
        strcpy(n_user.name, fn);
        break;
    } while (_True);

    do
    {
        char sexo[2];
        _get_data(&sexo, _String, "QUAL SEU SEXO (M / F)", _Warning);
        if (toupper(sexo[0]) != 'M' && toupper(sexo[0]) != 'F')
        {
            printf("\n");
            _msgDanger("ERRO!", "Alternativa inválida.");
            continue;
        }
        n_user.genre = (toupper(sexo[0]) == 'M') ? M : F;
        break;
    } while (_True);

    do
    {
        char login[40];
        _get_data(&login, _String, "DIGITE SEU LOGIN", _Warning);
        if (strlen(login) > 21)
        {
            printf("\n");
            _msgDanger("ERRO!", "Login maior que 20 letras.");
            continue;
        }
        strcpy(n_user.login, login);
        break;
    } while (_True);

    do
    {
        int senha1, senha2;

        _get_data(&senha1, _Int, "DIGITE UMA SENHA", _Warning);
        _get_data(&senha2, _Int, "DIGITE NOVAMENTE A SENHA", _Warning);

        if ((senha1 != senha2) || (senha1 > 99999))
        {
            printf("\n");
            _msgDanger("ERRO!", "Senhas diferentes ou maior que 99.999.");
            continue;
        }

        n_user.password = senha1;
        break;
    } while (_True);

    if (_dbAddUser(n_user, &conn))
    {
        printf("\n");
        _confirm("SUCESSO!", "Usuário cadastrado.", "Continuar", _Success);
        return _imcMenu();
    }

    if (_confirm_options("ERRO!", "Falha em cadastrar novo usuário.", "Tentar novamente?", 'S', 'N', _Danger))
    {
        return _imcAddUser();
    }
    return _imcMenu();
}

void _imcUpdateUser()
{
    setbuf(stdin, NULL);
    tbl_user_t u;
    u.genre = user.genre;
    u.id = user.id;
    u.password = user.password;
    strcpy(u.login, user.login);
    strcpy(u.name, user.name);

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
    _get_data(&op, _Int, "Digite o número da opção", _Success);
    printf("\n");

    switch (op)
    {
    case 0:
        _imcSession();
        break;
    case 1:
        do
        {
            char n1[61], n2[61], fn[122];
            _get_data(&n1, _String, "DIGITE SEU NOME", _Warning);
            _get_data(&n2, _String, "DIGITE SEU SOBRENOME", _Warning);
            sprintf(fn, "%s %s", n1, n2);
            if (strlen(fn) > 60)
            {
                printf("\n");
                _msgDanger("ERRO!", "Nome maior que 60 letras.");
                continue;
            }
            for (int i = 0; i < strlen(fn); i++)
            {
                fn[i] = toupper(fn[i]);
            }
            strcpy(u.name, fn);
            break;
        } while (_True);
        if (_dbUpdateUser(&user, u, &conn))
        {
            printf("\n");
            _confirm("SUCESSO!", "Nome do usuário atualizado.", "Continuar", _Success);
            _imcUpdateUser();
        }
        break;
    case 2:
        do
        {
            char sexo[1];
            _get_data(&sexo, _String, "QUAL SEU SEXO (M / F)", _Warning);
            if (toupper(sexo[0]) != 'M' && toupper(sexo[0]) != 'F')
            {
                printf("\n");
                _msgDanger("ERRO!", "Alternativa inválida.");
                continue;
            }
            u.genre = (toupper(sexo[0]) == 'M') ? M : F;
            break;
        } while (_True);
        if (_dbUpdateUser(&user, u, &conn))
        {
            printf("\n");
            _confirm("SUCESSO!", "Nome do usuário atualizado.", "Continuar", _Success);
            _imcUpdateUser();
        }
        break;
        break;
    case 3:
        do
        {
            char login[40];
            _get_data(&login, _String, "DIGITE NOVO LOGIN", _Warning);
            if (strlen(login) > 21)
            {
                printf("\n");
                _msgDanger("ERRO!", "Login maior que 20 letras.");
                continue;
            }
            strcpy(u.login, login);
            break;
        } while (_True);
        if (_dbUpdateUser(&user, u, &conn))
        {
            printf("\n");
            _confirm("SUCESSO!", "Login atualizado.", "Continuar", _Success);
            _imcUpdateUser();
        }
        break;
    case 4:
        do
        {
            int senha_atual, senha1, senha2;
            _get_data(&senha_atual, _Int, "DIGITE SEU SENHA ATUAL", _Warning);

            if (user.password != senha_atual)
            {
                printf("\n");
                _msgDanger("ERRO!", "Senha atual inválida.");
                continue;
            }

            _get_data(&senha1, _Int, "DIGITE SEU NOVA SENHA", _Warning);
            _get_data(&senha2, _Int, "DIGITE NOVAMENTE A SENHA", _Warning);

            if ((senha1 != senha2) || (senha1 > 99999))
            {
                printf("\n");
                _msgDanger("ERRO!", "Senhas diferentes ou maior que 99.999.");
                continue;
            }

            u.password = senha1;
            break;
        } while (_True);
        if (_dbUpdateUser(&user, u, &conn))
        {
            printf("\n");
            _confirm("SUCESSO!", "Senha atualizado.", "Continuar", _Success);
            _imcUpdateUser();
        }
        break;
    default:
        _confirm("Erro", "Opção inválida.", "Continuar", _Danger);
        _imcUpdateUser();
        break;
    }
}

void _imcReport()
{
    _imcTxtTitle();

    tbl_imc_result_t *result = _dbGetIMCbyUserId(&user, &conn);

    if (result == NULL)
    {
        _confirm("OOPS!", "Ainda não há IMC registrado.", "Voltar", _Warning);
        return;
    }

    printf("+----------------------------------------------------------------+\n");

    printf("|%sNOME: %s", BHCYN, BHYEL);

    if (strlen(user.name) > 54)
    {
        for (int i = 0; i <= 54; i++)
        {
            printf("%c", user.name[i]);
        }
        printf("...%s|\n", COLOR_RESET);
    }
    else
    {
        int fill = 58 - strlen(user.name);
        printf("%s", user.name);
        for (int i = 0; i < fill; i++)
        {
            printf("%c", ' ');
        }
        printf("%s|\n", COLOR_RESET);
    }

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

    for (int i = 0; i < result->num_rows; i++)
    {
        printf("|%s\t%d\t%s| %s%.2f\t\t%s|     %s%s%s     |\n",
               BHYEL,
               result->values[i].id,
               COLOR_RESET,
               BHYEL,
               result->values[i].imc,
               COLOR_RESET,
               BHYEL,
               result->values[i].datetime,
               COLOR_RESET);

        contReg++;
        contRegTotal += result->values[i].imc;
        strcpy(ultimo_reg, result->values[i].datetime);
    }

    free(result->values);
    free(result);

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

    printf("+----------------------------------------------------------------+\n");
    printf("\n");
    _confirm("Data/Hora", _DATETIME_, "Continuar", _Danger);
}

void _imcAddIMC()
{
    _imcTxtTitle();

    float peso, altura, IMC;

    fflush(stdin);

    _get_data(&peso, _Float, "IMC - (Kg)\tDIGITE SEU PESO", _Warning);
    _get_data(&altura, _Float, "IMC - (cm)\tDIGITE SUA ALTURA", _Warning);

    altura /= 100;

    IMC = peso / (altura * altura);

    printf("\n");
    if (!_dbInsertIMC(&user, IMC, &conn))
    {
        _confirm("ERRO!", "Falha em inserir novo IMC.", "Continuar", _Danger);
        return;
    }
    _confirm("OBA!", "IMC registrado com sucesso.", "Continuar", _Success);
}

void _imcDeleteUser()
{
    _imcTxtTitle();
    if (_confirm_options("!ATENÇÃO!", "Ao remoção é irreversivél.", "Prosseguir?", 'S', 'N', _Danger) == _True)
    {
        int senha;
        printf("\n");
        _get_data(&senha, _Int, "CONFIRME SUA SENHA", _Warning);

        if (senha != user.password)
        {
            printf("\n");
            _confirm("ERRO!", "Senha incorreta.", "Continuar", _Warning);
            _imcSession();
        }

        if (!_dbDeleteUser(&user, &conn))
        {
            printf("\n");
            _confirm("ERRO!", "Falha em deletar usuário.", "Continuar", _Danger);
            _imcSession();
        }

        _user_init(&user);
        printf("\n");
        _confirm("OK!", "Usuário removido com sucesso.", "Continuar", _Success);
        _imcMenu();
    }
    _imcSession();
}

// // DELETA CONTA CADASTRADA
// void _BD_delCad(char login[20], int senha)
// {

//     _dbSetup();
//     _dbGetConfig(&conn_info);

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
//             if (connObj.conn = mysql_real_connect(connObj.conn, conn_info.host, conn_info.user, conn_info.pass, conn_info.database, conn_info.port, NULL, 0))
//             {
//                 char query[200];
//                 sprintf(query, "DELETE FROM tbl_user_ts WHERE login = '%s' AND senha = '%d'", login, senha);
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
    conn_info_t db;

    _get_data(&db.host, _String, "HOST IP", _Warning);
    fprintf(*_config, "%s", db.host);
    fprintf(*_config, "\n");

    _get_data(&db.user, _String, "USUÁRIO", _Warning);
    fprintf(*_config, "%s", db.user);
    fprintf(*_config, "\n");

    _msgDanger("** ATENÇÃO! **", "Caso não haja SENHA, digite null");
    _get_data(&db.pass, _String, "SENHA", _Warning);
    fprintf(*_config, "%s", db.pass);
    fprintf(*_config, "\n");

    _get_data(&db.database, _String, "BANCO DE DADOS", _Warning);
    fprintf(*_config, "%s", db.database);
    fprintf(*_config, "\n");

    _get_data(&db.port, _Int, "PORTA", _Warning);
    fprintf(*_config, "%d", db.port);
}

void _dbSetup()
{
    _clear_terminal();

    _config_db_file = fopen(CONFIG_DB_FILENAME, "r");

    if (_config_db_file == NULL)
    {
        _config_db_file = fopen(CONFIG_DB_FILENAME, "w+");
        _writeConfig(&_config_db_file);
        fclose(_config_db_file);
    }
}

void _dbGetConfig(conn_info_t *_conn_info)
{
    char host[sizeof(_conn_info->host)];
    char user[sizeof(_conn_info->user)];
    char pass[sizeof(_conn_info->pass)];
    char database[sizeof(_conn_info->database)];
    int port;

    _config_db_file = fopen(CONFIG_DB_FILENAME, "r");

    fscanf(_config_db_file, "%s", host);
    strcpy(_conn_info->host, host);

    fscanf(_config_db_file, "\n%s", user);
    strcpy(_conn_info->user, user);

    fscanf(_config_db_file, "\n\n%s", pass);
    if (strcmp(pass, "null") == 0)
    {
        strcpy(pass, "");
    }
    strcpy(_conn_info->pass, pass);

    fscanf(_config_db_file, "\n\n\n%s", database);
    strcpy(_conn_info->database, database);

    fscanf(_config_db_file, "\n\n\n\n%d", &port);
    _conn_info->port = port;

    fclose(_config_db_file);
}

void _dbUpdateConfig()
{
    _clear_terminal();

    _config_db_file = fopen(CONFIG_DB_FILENAME, "w");

    _writeConfig(&_config_db_file);

    if (ferror(_config_db_file) == 0)
    {
        fclose(_config_db_file);
        printf("\n");
        _confirm("SUCESSO!", "CONFIGURAÇÕES ALTERADAS.", "Continuar", _Info);
    }
    else
    {
        fclose(_config_db_file);
        printf("\n");
        _confirm("ERRO!", "NÃO FOI POSSIVEL ALTERAR AS CONFIGURAÇÕES.", "Continuar", _Danger);
    }
}
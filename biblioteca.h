/**
 *   17 DE OUTUBRO DE 2018, MANAUS - AM / UNIVERSIDADE PAULISTA - UNIP
 *   SUP TEC ANÁLISE DES SISTEMAS / TURMA: DS1A34 / TURNO: MATUTINO
 *
 *   - AUTOR:           WILLIAM BENJAMIM M SAMPAIO / RA: D7534B-7
 *   - CONTRIBUIRAM:    FELIPE MATEUS B NASCIMENTO / RA: N372HD-8
 *                      JOSE R C CARDOSO JUNIOR    / RA: N256BJ-3
 *                      LEVY DE LIRA GOMES         / RA: D7533H-9
 *                      LISVANETE RODRIGUES GARCIA / RA: N2572H-7
 *                      VENNER MANOEL BERTINO      / RA: N33618-8
 *
 */

#include <locale.h>     //
#include <mysql.h>      //
#include <stdio.h>      //
#include <stdlib.h>     //
#include <string.h>     //
#include <windows.h>    //

// ESTRUTURA COM AS VARIÁVEIS DE CONEXÃO
typedef struct
{

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int qstate;

} MYSQLCONN;

// ESTRUTURA COM AS INFO DE ACESSO AO BD
typedef struct
{

    char    host[100];
    char    user[100];
    char    pass[100];
    char    datb[100];
    int     port;

} BASEDEDADOS;

// ESTRUTURA COM INFORNAÇÕES DO USUÁRIO
typedef struct
{

    char  nome[60];
    char  sexo;
    char  login[20];
    int   senha;

} USUARIO;

// CONSTANTES E VARIÁVEIS GLOBAIS
const FILE* configdb;
const char* fileBd = "configdb";

MYSQLCONN conObj;
BASEDEDADOS bdConfig;

// RETORNA UMA STRING COM DATA E HORA ATUAIS
char* dataHora(void)
{

    return __DATE__ " - " __TIME__;

}

// CONFIGURA O IDIOMA DA APLICAÇÃO PARA PORTUGUÊS
void ptBrCaracteres(void)
{

    setlocale(LC_ALL, "Portuguese");

}

// CONEXÃO OK!
int _conStatus01(char* datb)
{

    char str[100];
    sprintf(str,"CONEXÃO OK! BASE DE DADOS: %s\n(%s)",datb,dataHora());
    MessageBox(NULL,str,"Conexão Status", MB_OK | MB_ICONINFORMATION);
    return 1;

}

// CONEXÃO COM PROBLEMA!
int _conStatus02(void)
{

    char str[200];
    sprintf(str,"IMPOSSÍVEL ESTABELECER CONEXÃO!\n- Verifique se há conexão com a internet.\n- Verifique se as configurações de ACESSO ao BANCO DE DADOS estão CORRETAS.\n- Verifique se o MySQL está ativo (localhost).");
    MessageBox(NULL,str,"Conexão Status", MB_OK | MB_ICONSTOP);
    return 0;

}

// CONEXÃO, PROBLEMA COM A CRIAÇÃO DO OBJETO!
int _conStatus03(void)
{

    char str[100];
    sprintf(str,"ERRO! NÃO foi possivel criar o OBJETO de conexão.");
    MessageBox(NULL,str,"Conexão Status", MB_OK | MB_ICONWARNING);
    return -1;

}

// CONEXÃO, OUTROS PROBLEMAS!
void _conStatus00(MYSQLCONN con)
{

    char str[100];
    sprintf(str,"ERRO: %s\n",mysql_error(conObj.conn));
    MessageBox(NULL,str,"Conexão Status", MB_OK | MB_ICONWARNING);

}

// IMPRIME O NOME DOS INTEGRANTES DA EQUIPE
void equipe(int primeiraVez)
{

    int tan,i;

    char lin1[]  = "________________________________________________________________________________\n";
    char lin2[]  = "                          UNIVERSIDADE PAULISTA - UNIP\n";
    char lin3[]  = "                          SUP TEC ANÁLISE DES SISTEMAS\n\n";
    char lin4[]  = "                         TURMA: DS1A34\tTURNO: MATUTINO\n\n";
    char lin5[]  = "                    FELIPE MATEUS B NASCIMENTO / RA: N372HD-8\n";
    char lin6[]  = "                    JOSE R C CARDOSO JUNIOR    / RA: N256BJ-3\n";
    char lin7[]  = "                    LEVY DE LIRA GOMES         / RA: D7533H-9\n";
    char lin8[]  = "                    LISVANETE RODRIGUES GARCIA / RA: N2572H-7\n";
    char lin9[]  = "                    VENNER MANOEL BERTINO      / RA: N33618-8\n";
    char lin10[] = "                    WILLIAM BENJAMIM M SAMPAIO / RA: D7534B-7\n";
    char lin11[] = "________________________________________________________________________________";

    if(primeiraVez == 1)
    {
        Sleep(1000);

        tan = strlen(lin1);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin1[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin2);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin2[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin3);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin3[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin4);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin4[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin5);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin5[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin6);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin6[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin7);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin7[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin8);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin8[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin9);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin9[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin10);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin10[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
        tan = strlen(lin11);
        for(i=0; i<tan; i++)
        {
            printf("%c",lin11[i]);
            i % 5 == 0?system("color 0F"):system("color 0E");
        }
    }
    else
    {
        if(primeiraVez == 0)
        {
            printf("%s%s%s%s%s%s%s%s%s%s%s",lin1,lin2,lin3,lin4,lin5,lin6,lin7,lin8,lin9,lin10,lin11);
        }
    }

}

// IMPRIME "OBRIGADO" E SAIR DO PROGRAMA
void sair(void)
{

    system("cls");
    system("color 0c");
    printf("                                                                                ");
    printf("                                                                                ");
    printf("                                                                       b$GO     ");
    printf("                                                                       @@@G     ");
    printf("      L@@@@@: ,@@@@@@: E@@@@@$. @@  1@@@@@,    @@;   @@@@@@,   G@@@@U  @@@      ");
    printf("     i@@. ,@@  @E   @@ b@;  ,@@ @@ S@N  ;@@   N@@@   @@..;@@: @@7  K@WL@@G      ");
    printf("     @@     @O @K  .@2 Z@.   @@ @$ @$         @T:@r  @@    @G:@1    b@@$@:      ");
    printf("     @$     @g @@@@@@r Z@@@@@i  @0 @2  G@$$: D@  @@  @@    @By@:    r@0$g       ");
    printf("     @@    .@K @r   j@.T@. W@T  @$ @@   .W@. @@@@@@z @@    @W.@E    G@          ");
    printf("     L@@r,n@@ .@8,;r@@ K@.  8@S @@ y@@;.;@@.$@,,,.@@ @@r;7@@. @@G,,0@@$@        ");
    printf("      :g@@@G  :@@@@@$; j@:   D@;$$  ;$@@@8:.@K    r@yS@@@@B.   n@@@@SB@@        ");
    printf("                                                                                ");
    printf("                                                                                ");
    Sleep(1000);
    system("exit");

}

// IMPRIME (DESENHA) OS ROBÔS DO STAR-WARS
void starWarsRobos(int primeiraVez)
{

    int op;
    if(primeiraVez == 1)
    {
        system("color 0e");
        printf("                                                                                ");
        system("color 0e");
        printf("                      v@@@@@@@@@@@@@@@@@@uk@@@@@i@@@@@@@@@q                     ");
        system("color 0e");
        printf("                     @@@@@@@@@@@@@@@@@@@@v@@@@@@7O@@@@@@@@@@:                   ");
        system("color 0e");
        printf("                    @@@@@J       G@@@@   @@@@@@@G,@@@@  E@@@@L                  ");
        system("color 0e");
        printf("                   @@@@@@@@@@@@L @@@@@  O@@@@@@@@ B@@@@8@@@@@@j                 ");
        system("color 0e");
        printf("                  .@@@@@@@@@@@@7i@@@@q 7@@@@:N@@@7;@@@@@@@@@@@@                 ");
        system("color 0e");
        printf("                         1@@@@@ @@@@@. @@@@@ q@@@@ @@@@@8@@@@@i                 ");
        system("color 0e");
        printf("                P@@@@@0  @@@@@J @@@@@ O@@@@@@@@@@@.S@@@@i:@@@@M,                ");
        system("color 0e");
        printf("               @@@@@@@@@@@@@@@ P@@@@OJ@@@@@EEB@@@@F.@@@@@  @@@@@8               ");
        system("color 0e");
        printf("              :@@@@@@@@@@@@@@5 @@@@@@@@@@@    @@@@@ @@@@@@  O@@@@@L             ");
        system("color 0e");
        printf("               :7L:. iii7::,   7rv.:ii:i;:    riiir .: .iY   iiiiv1.            ");
        system("color 0e");
        printf("            i@@@@.  i@@@@   r@@@@, BBMMB@F:@@@@BB@@@@B. B@@@@@@@@@@@@           ");
        system("color 0e");
        printf("           i@@@@7 .@@@@@Y  Z@@@@:.@@@@@@@E,@@@@@@@@@@@@8@@@@@@@@@@@@@@          ");
        system("color 0e");
        printf("          :@@@@7 U@@@@@@  @@@@@.,@@@@@@@@N @@@@@. 0@@@@@@@@@@@; F@@@@@@         ");
        system("color 0e");
        printf("         :@@@@u @@@@@@@Y @@@@@ :@@@@@@@@@0 @@@@@. 1@@@@@@@@@@@S  ,...:i         ");
        system("color 0e");
        printf("        :@@@@Bk@@@@@@@@F@@@@@ i@@@@@@@@@@E @@@@@@@@@@@@@@@@@@@@@@@@@@@@@F       ");
        system("color 0e");
        printf("       ,@@@@@@@@@@@@@@@@@@@@ r@@@@@7U@@@@G @@@@@@@@@@@@@@ 5@@@@@@@@@@@@@@@      ");
        system("color 0e");
        printf("      ,@@@@@@@@@.M@@@@@@@@@ v@@@@@k k@@@@8 @@@@@@@@@@@@v    ...   :G@@@@@@@     ");
        system("color 0e");
        printf("     .@@@@@@@@M  @@@@@@@@@ j@@@@@@@@@@@@@O @@@@@@ @@@@@@   @@BMB@,  8@@@@@@M    ");
        system("color 0e");
        printf("    .@@@@@@@@L  E@@@@@@@M 5@@@@@@@@@@@@@@M @@@@@@  @@@@@@v ;@@@@@@BG@@@@@@@@X   ");
        system("color 0e");
        printf("   ,@@@@@@@@.   @@@@@@@M E@@@@@B    @@@@@@ @@@@@@L .@@@@@@S @@@@@@@@@@@@@@@@@F  ");
        system("color 0e");
        printf("  7@@@@@@@G    1@@@@@@@ @@@@@@O    ,@@@@@@ @@@@@@@  :@@@@@@@u@@@@@@@@@@@@@@@@@  ");
        system("color 0e");
        printf("  7r::::::     :i::::: .r:::::      i::::: i::::ii   .::::ir. ,:::::::::::::,   ");
        system("color 0e");

        system("color 0b");
        printf("                                                                                ");
        system("color 0f");
        printf("                                                                                ");
        system("color 0e");
        printf("                                                          ,:::,                 ");
        system("color 0b");
        printf("                                                        ,Ms,  BX                ");
        system("color 0f");
        printf("                                                        sBs2s 9B:               ");
        system("color 0e");
        printf("                                                        iMrGss9@r               ");
        system("color 0b");
        printf("                                                         S@29S5B,               ");
        system("color 0f");
        printf("                                                          B295GB,               ");
        system("color 0e");
        printf("                                                          SBsXs9                ");
        system("color 0b");
        printf("                                                     ,:,,:MM,Srrs,,r            ");
        system("color 0f");
        printf("                                                   :9si  :Xsrsr:  is,r,         ");
        system("color 0e");
        printf("                                                   @MHB5   :,   sisi2r2i        ");
        system("color 0b");
        printf("                                                 ,s:MM@9ri,    s@XGHMMG2        ");
        system("color 0f");
        printf("                                                2s SX s@BMGSrXB@:sBGG@B@:       ");
        system("color 0e");
        printf("                                              i2s;@B  2@s:rssS@2 GB  BMM@S      ");
        system("color 0b");
        printf("                                             rB: @Br  MG ,,,rG9  @s  SBMM@M     ");
        system("color 0f");
        printf("                                              9X rs   9Bi:, sBG 2B   sHM99@B,   ");
        system("color 0e");
        printf("                  ,sG@BB92i                   r@ :2    @G2i5B@G9Bi   iG92MBS:   ");
        system("color 0b");
        printf("                :H2:XBG9MsrSs                  Bi G   sBMB@B@MBB@r   :@5XBs     ");
        system("color 0f");
        printf("               sG5r:sHX22:iXB@                 2M,Mr  rM9M99HSssX@   BX9BM      ");
        system("color 0e");
        printf("              ,B@92issHrssXSGBB                 Xiss  2B9S,:i2SGS@  @BBBG       ");
        system("color 0b");
        printf("              G@BG92sss229X99GB,               s9:,,:rB99Hss9@BMrXM@M@Bs        ");
        system("color 0f");
        printf("              MBSsi:222s2222Hss;               ,HHH   Mr22sM@@M999@B@B          ");
        system("color 0e");
        printf("              :s,,,,,s: isss:::Xr ,             ,s,   25sXs99siB9sGGB           ");
        system("color 0b");
        printf("           rS   ri,::irHS2s,ss:rS :,                  5GsBG9Mr 92:9             ");
        system("color 0f");
        printf("           sX, ,2r,:::,:r2sr,ir;Mrrs        ;         XH:@99B5,2XrG             ");
        system("color 0e");
        printf("           XS;rs9:,::   r952, r:M5sS        r         9XrB99@2siGrM             ");
        system("color 0b");
        printf("          ,@Brrs2:,,:r:,,GXG: :;sS59    ,   ,,,       9Gr@S9@S2:5rG             ");
        system("color 0f");
        printf("           BB:ir2::,isi  9MS2 ,rsSB:   ::,i: ,::      :BrMX9Ss2 SSS             ");
        system("color 0e");
        printf("           GMssHs:: :ri: sssr,:rr@M   ,  @B@G   ,      GsSsGX5i:Gsi             ");
        system("color 0b");
        printf("           s@2sB5is2r  ,,  ,,,,,:MX  ri, rGGiS@:ri    SM2ssXMr,sssH2            ");
        system("color 0f");
        printf("           2B;:@2rMM2,srr:GMG  ,i@s  ;S2:  ,,ssr2:    s@BGHS2HX2sGB9            ");
        system("color 0e");
        printf("           9@rsBGiG92::,r:ss2:::iMs   rGGS22XXGGr      r@BMMG9GGGG@5            ");
        system("color 0b");
        printf("          ,BB:s@B,rssrssissrssrs2G2  :Hs:ri:r:,i5s,     sBGB9@9XB99r            ");
        system("color 0f");
        printf("          :r2ssHGsG2sr:i,:srsrrrSBs  r2, ,    , sH,,,    B@B52G2GX2             ");
        system("color 0e");
        printf("          B5SGssHXs9s9GBM9XHG@MGB9   ,22ss  ,:222s,,:    MB@9s9XG@r             ");
        system("color 0b");
        printf("          r9GGXH@X rMB@BMXs2M@BMG,  , ,s22S2H552s, ,::   s@MG:9HGM              ");
        system("color 0f");
        printf("         sssS2rXMX      rGrs9@BM::ssi,,  :irrr:, ::sH9   sMG5 Xss9              ");
        system("color 0e");
        printf("        s2r,s2rGMG     29r5s,X@@GHG5XSs,,,,,,,,,:s9SGB   5GGHiXssS              ");
        system("color 0b");
        printf("       ,MGr,,M9MBX    5Sr,is  B@BXrsHsHSr:::::,sXXr;22 ,,is9r9GssM              ");
        system("color 0f");
        printf("         sGi:9MSMS    @Si ,s: iiiis2@r2GGsrrris9G2rsM9X2sX@Bss@5 Gr             ");
        system("color 0e");
        printf("           ssr::::    iM9ssGG9s   :XBHrr9GrrrsG922XSSGGGMG5s: G@HsMS            ");
        system("color 0b");
        printf("                        rX5ss2,     9BMsMB2rs9@B@G2            :G9sH            ");
        system("color 0f");
        printf("                                      sGMM9GGMB9s                               ");
        system("color 0e");
        printf("                                                                                ");
        system("color 0b");
        printf("                R2-D2                    BB-8             C-3PO                 ");
        system("color 0f");
        system("color 0e");
        printf("\n________________________________________________________________________________\n\n");
        printf("                **** Arte gerada com ASCII Generator v2.0.0 ****\n");
        printf("                     - http://ascgendotnet.jmsoftware.co.uk \n");
        printf("                        - http://ascgen2.sourceforge.net\n\n");
        printf("________________________________________________________________________________\n");

        do
        {
            printf("\n");
            printf("[1] - RESETAR | [2] - MENU PRINCÍPAL | [0] - SAIR\n");
            scanf("%d",&op);
            switch(op)
            {
            case 0:
                if(MessageBox(NULL,"Você deseja realmente SAIR?","SAIR", MB_YESNO | MB_ICONQUESTION) == 6)
                {
                    sair();
                }
                else
                {
                    starWarsRobos(0);
                }
                break;
            case 1:
                system("cls");
                starWarsRobos(1);
                break;
            case 2:
                system("cls");
                iniciar(0);
                break;
            default:
                MessageBox(NULL,"Opção inválida!","ERRO!", MB_OK | MB_ICONERROR);
                starWarsRobos(0);
                break;
            }
        }
        while(op < 0 || op > 2);
    }
    else
    {
        do
        {
            scanf("%d",&op);
            switch(op)
            {
            case 0:
                if(MessageBox(NULL,"Você deseja realmente SAIR?","SAIR", MB_YESNO | MB_ICONQUESTION) == 6)
                {
                    sair();
                }
                else
                {
                    starWarsRobos(0);
                }
                break;
            case 1:
                system("cls");
                starWarsRobos(1);
                break;
            case 2:
                system("cls");
                iniciar(0);
                break;
            default:
                MessageBox(NULL,"Opção inválida!","ERRO!", MB_OK | MB_ICONERROR);
                starWarsRobos(0);
                break;
            }
        }
        while(op < 0 || op > 2);
    }

}

// MENU PRINCÍPAL
void menuPrincipal(int erro)
{
    int i;
    system("color 0A");
    int op;
    if(erro == 0)
    {
        for(i=0; i<80; i++)
        {
            printf("%c",277);
        }
        printf("\n");
        printf("\t\tMENU PRINCÍPAL:\n\n");
        printf("\t\t[1] - ROBÔS STAR WARS\n");
        printf("\t\t[2] - IMC COM MySQL\n");
        printf("\n");
        printf("\t\t[3] - CHECAR CONEXÃO COM O BD\n");
        printf("\t\t[4] - ALTERAR CONFIG DE ACESSO AO BD\n\n");
        printf("\t\t[9] - PLAY / STOP MUSICA\n");
        printf("\t\t[0] - SAIR\n\n");
    }
    printf("\t\t ->");
    scanf("%d",&op);
    switch(op)
    {
    case 0:
        if(MessageBox(NULL,"Você deseja realmente SAIR?","SAIR", MB_YESNO | MB_ICONQUESTION) == 6)
        {
            sair();
        }
        else
        {
            system("cls");
            equipe(0);
            menuPrincipal(0);
        }
        break;
    case 1:
        system("cls");
        starWarsRobos(1);
        break;
    case 2:
        _imcPrincipal();
        break;
    case 3:
        _BD_checarCon();
        iniciar(0);
        break;
    case 4:
        system("cls");
        _BD_altConfig();
        iniciar(0);
        break;
    case 9:
        playPause();
        iniciar(0);
        break;
    default:
        MessageBox(NULL,"Opção inválida!","ERRO!", MB_OK | MB_ICONERROR);
        iniciar(0);
        break;
    }

}

// INICIA / PARA A MUSICA
void playPause(void)
{

    int pid = 0;
    FILE *pid_;

    pid_ = fopen("sound/status","r");

    fscanf(pid_,"%d",&pid);

    if(pid == 0)
    {
        WinExec("sound/sound.exe",SW_HIDE);
        fclose(pid_);
        return;
    }
    else
    {
        char kill[100];
        sprintf(kill,"taskkill /f /pid %d",pid);
        system(kill);
        system("cls");
        pid_ = fopen("sound/status","w");
        fprintf(pid_,"");
        fclose(pid_);
        return;
    }

}

// FUNÇÃO INICIAL
void iniciar(int primeiraVez)
{

    if(primeiraVez==1)
    {
        _BD_checarCon();
    }
    system("cls");
    equipe(primeiraVez);
    menuPrincipal(0);

}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//      FUNÇÕES COM O PREFIXO "_imc" SE REFEREM AO SISTEMA IMC.                            //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

// IMPRIME A TELA INICIAL DO SISTEMA
void _imcPrincipal(void)
{

    _imcTitulo();
    _imcMenu();

}

// IMPRIME TITULO DO SISTEMA
void _imcTitulo(void)
{
    int i;
    system("cls");
    for(i=0; i<80; i++)
    {
        printf("%c",26);
    }
    printf("%c                 SISTEMA - INDICE DE MASSA CORPORAL (com MySQL)               %c",24,25);
    for(i=0; i<80; i++)
    {
        printf("%c",27);
    }

}

// IMPRIME MENU PRINCÍPAL DO SISTEMAS
void _imcMenu(void)
{

    int op;
    printf("\t- [1]ENTRAR\n");
    printf("\t- [2]CADASTRE-SE\n");
    printf("\n");
    printf("\t- [9]VOLTAR AO MENU PRINCÍPAL\n");
    printf("\t- [0]SAIR\n");
    printf("\n\t");
    scanf("%d",&op);
    switch(op)
    {
    case 0:
        if(MessageBox(NULL,"Você deseja realmente SAIR?","SAIR", MB_YESNO | MB_ICONQUESTION) == 6)
        {
            sair();
        }
        else
        {
            _imcPrincipal();
        }
        break;
    case 1:
        _imcEntrar();
        break;
    case 2:
        _imcCad();
        break;
    case 9:
        iniciar(0);
        break;
    default:
        MessageBox(NULL,"Opção inválida!","ERRO!", MB_OK | MB_ICONERROR);
        _imcPrincipal();
        break;
    }

}

// TELA DE CADASTRO DE NOVOS USUÁRIOS
void _imcCad(void)
{

    _imcTitulo();
    _BD_cadastrarUser();
    system("pause");
    _imcPrincipal();

}

// LOGIN DE ACESSO AO SISTEMA
void _imcEntrar(void)
{

    char login[20];
    int  senha;
    _imcTitulo();
    printf(" - LOGIN: ");
    scanf("%s",login);
    printf(" - SENHA: ");
    scanf("%d",&senha);
    if(_BD_validarLogin(login,senha) == 1)
    {
        _imcSessao(login,senha);
    }
    else
    {
        int op;
        printf(" LOGIN OU SENHA INVÁLIDO!\n");
        printf(" [1] - Tentar Novamente / [2] - voltar\n");
        do
        {
            scanf("%d",&op);
            if(op == 1)
            {
                system("cls");
                _imcEntrar();
            }
            else
            {
                if(op == 2)
                {
                    _imcPrincipal();
                }
                else
                {
                    printf("Opção Inválida! :(\n");
                }
            }
        }
        while(op != 1 && op != 2);
    }

}

// PEGAR AS INFORMAÇÕES DO USUARIO LOGADO
void _imcRelatorio(char login[20], int senha)
{

    _BD_pegarUserInfo(login,senha);

}

// EXIBE OS REGISTROS DE IMC
void _imcExibirImc(char login[20], int senha)
{

    _BD_exibirImc(login,senha);

}

// DELETA CADASTRO DE USUÁRIO
void _imcDelCadImc(char login[20], int senha)
{

    _BD_delCad(login,senha);

}

// ATUALIZA O CADASTRO DO USUÁRIO
void _imcUpdateCadImc(char login[20], int senha)
{

    system("cls");
    _imcTitulo();
    _BD_atualizarCad(login,senha);

}

// ABRE O MENU PRINCÍPAL DO USUÁRIO
void _imcSessao(char login[20], int senha)
{
    int i;
    _imcTitulo();
    printf("\n");
    _imcRelatorio(login,senha);
    for(i=0; i<80; i++)
    {
        printf("_");
    }
    printf("\t[1] - REGISTRAR NOVO IMC.\n");
    printf("\t[2] - EXIBIR TODOS OS REGISTROS\n\n");
    printf("\t[4] - ALTERAR DADOS PESSOAIS\n\n");
    printf("\t[9] - VOLTAR AO MENU PRINCÍPAL\n");
    printf("\t[0] - SAIR\n\n");
    printf("\t[-99] - APAGAR CADASTRO\n\n");
    printf("\t::");
    int op;
    scanf("%d",&op);

    switch(op)
    {
    case 0:
        if(MessageBox(NULL,"Você deseja realmente SAIR?","SAIR", MB_YESNO | MB_ICONQUESTION) == 6)
        {
            sair();
        }
        else
        {
            _imcSessao(login,senha);
        }
        break;
    case 1:
        system("cls");
        _imcTitulo();
        _BD_registrarImc(login,senha);
        system("pause");
        _imcSessao(login,senha);
        break;
    case 2:
        system("cls");
        _imcTitulo();
        _imcExibirImc(login,senha);
        system("pause");
        _imcSessao(login,senha);
        break;
    case 4:
        _imcUpdateCadImc(login,senha);
        system("pause");
        _imcPrincipal();
        break;
    case 9:
        _imcPrincipal();
        break;
    case -99:
        system("cls");
        _imcTitulo();
        _BD_delCad(login,senha);
        system("pause");
        _imcPrincipal();
        break;
    default:
        MessageBox(NULL,"Opção inválida!","ERRO!", MB_OK | MB_ICONERROR);
        _imcSessao(login,senha);
        break;
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         //
//      FUNÇÕES COM O PREFIXO "_BD_" ACESSAM O BANCO DE DADOS.                             //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

// VERIFICA CONEXÃO COM O BANCO DE DADOS
void _BD_checarCon(void)
{
    int i;
    void load(void)
    {
        system("cls");
        printf("CONECTANDO ");
        srand((unsigned)time(NULL));
        for(i=0; i<69; i++)
        {
            printf("%c",134);
            Sleep(rand()%10);
        }
    }

    system("cls");

    _BD_configura();
    _BD_pegarConfig(&bdConfig);

    if(conObj.conn = mysql_init(0))
    {
        load();
        if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
        {
            _conStatus01(bdConfig.datb);
            mysql_close(conObj.conn);
        }
        else
        {
            _conStatus02();
        }
    }
    else
    {
        _conStatus03();
    }
    system("pause");

}

// CADASTRAR NO BD UM NOVO USUÁRIO
int _BD_cadastrarUser(void)
{

    MYSQLCONN con;
    BASEDEDADOS bd;
    _BD_configura();
    _BD_pegarConfig(&bdConfig);

    USUARIO novo;
    int cont;

    int espaco = 0;
    do
    {
        fflush(stdin);
        printf(">> DIGITE SEU NOME COMPLETO:\n");
        gets(novo.nome);
        strupr(novo.nome);
        for(cont=0; cont<strlen(novo.nome); cont++)
        {
            if(novo.nome[cont] == ' ')
            {
                espaco = 1;
            }
        }
        if(espaco == 0)
        {
            printf("ERRO! Nome inválido.\n");
        }
    }
    while(espaco == 0);
    do
    {
        char sexo;
        fflush(stdin);
        printf(">> QUAL SEU SEXO (M / F):\n");
        scanf("%c",&sexo);
        novo.sexo = toupper(sexo);
        if(novo.sexo != 'M' && novo.sexo != 'F')
        {
            printf("ERRO! Alternativa inválida.\n");
        }
    }
    while(novo.sexo != 'M' && novo.sexo != 'F');

    int erro;
    do
    {
        int spc;
        do
        {
            spc = 0;
            do
            {
                fflush(stdin);
                printf(">> NOME DE USUÁRIO (MAX - 20):\n");
                gets(novo.login);
                if(strlen(novo.login) > 20)
                {
                    printf("ERRO! Nome de usuário deve ter no maximo 20 caracteres.\n");
                }
            }
            while(strlen(novo.login) > 20);

            for(cont=0; cont<strlen(novo.login); cont++)
            {
                if(novo.login[cont] == ' ')
                {
                    printf("ERRO! Não pode haver espaços.\n");
                    spc = 1;
                }
                break;
            }
        }
        while(spc == 1);
        if(_BD_validarUserName(novo.login) == 1)
        {
            printf("Login já utilizado por outro usuário :(\n");
        }
        else
        {
            if(_BD_validarUserName(novo.login) == -1)
            {
                erro = 1;
            }
            else
            {
                if(_BD_validarUserName(novo.login) == -2)
                {
                    erro = 1;
                    _conStatus02();
                }
                else
                {
                    if(_BD_validarUserName(novo.login) == -3)
                    {
                        erro = 1;
                        _conStatus03();
                    }
                    else
                    {
                        erro = 0;
                    }
                }
            }
        }
    }
    while(erro != 0);

    int senhaR;
    do
    {
        do
        {
            printf(">> DIGITE UMA SENHA (APENAS NÚMEROS, MAX - 5):\n");
            fflush(stdin);
            scanf("%d",&novo.senha);
            if(novo.senha > 99999)
            {
                printf("ERRO! Senha deve ter no maximo 5 digitos.\n");
            }
        }
        while(novo.senha > 99999);

        printf(">> REPITA A SENHA DE ACESSO:\n");
        fflush(stdin);
        scanf("%d",&senhaR);
        if(senhaR != novo.senha)
        {
            printf("ERRO! Senhas não coincidem.\n");
        }
    }
    while(senhaR != novo.senha);

    if(conObj.conn = mysql_init(0))
    {
        if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
        {
            char query[200];
            sprintf(query,"INSERT INTO usuarios (nome, sexo, login, senha) VALUES ('%s','%c','%s','%d')",novo.nome,novo.sexo,novo.login,novo.senha);
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {
                printf("DADOS INSERIDOS COM SUCESSO!\n");
            }
            else
            {
                int op;
                printf("ERRO! Algo deu errado...\n");
                printf(" [1] - Tentar Novamente / [2] - voltar\n");
                do
                {
                    printf(" ");
                    scanf("%d",&op);
                    if(op == 1)
                    {
                        system("cls");
                        _imcCad();
                    }
                    else
                    {
                        if(op == 2)
                        {
                            _imcPrincipal();
                        }
                        else
                        {
                            printf("Opção Inválida! :(");
                        }
                    }
                }
                while(op != 1 && op != 2);
            }
        }
        else
        {
            _conStatus02();
        }
    }
    else
    {
        _conStatus03();
    }

}

// ATUALIZAR CADASTRO DE USUÁRIO NO BD
void _BD_atualizarCad(char login[20], int senha)
{

    _BD_configura();
    _BD_pegarConfig(&bdConfig);

    USUARIO update;
    int cont, op, erro, senhaR;
    int espaco = 0;
    char query[200];

    sprintf(query,"select nome,sexo,login,senha from usuarios where login = '%s' and senha = '%d'",login,senha);

    if(conObj.conn = mysql_init(0))
    {
        if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
        {
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {

                conObj.res = mysql_store_result(conObj.conn);
                while(conObj.row = mysql_fetch_row(conObj.res))
                {
                    strcpy(update.nome,conObj.row[0]);
                    if(conObj.row[1] == "M")
                    {
                        update.sexo = 'M';
                    }
                    else
                    {
                        update.sexo = 'F';
                    }
                    strcpy(update.login,conObj.row[2]);
                    update.senha = atoi(conObj.row[3]);
                }
            }
            else
            {
                _conStatus00(conObj);
                mysql_close(conObj.conn);
            }
        }
        else
        {
            _conStatus02();
        }
    }
    else
    {
        _conStatus03();
    }

    printf(">> ATUALIZAR...\n\n");
    printf(">> [1] - NOME   \n");
    printf(">> [2] - SEXO   \n");
    printf(">> [3] - LOGIN  \n");
    printf(">> [4] - SENHA  \n\n");
    printf(">> [0] - VOLTAR  \n\n::");
    scanf("%d",&op);
    switch(op)
    {
    case 0:
        _imcSessao(login,senha);
        break;
    case 1:
        do
        {
            fflush(stdin);
            printf(">> DIGITE SEU NOME COMPLETO:\n");
            gets(update.nome);
            strupr(update.nome);
            for(cont=0; cont<strlen(update.nome); cont++)
            {
                if(update.nome[cont] == ' ')
                {
                    espaco = 1;
                }
            }
            if(espaco == 0)
            {
                printf("ERRO! Nome inválido.\n");
            }
        }
        while(espaco == 0);
        break;
    case 2:
        do
        {
            char sexo;
            fflush(stdin);
            printf(">> QUAL SEU SEXO (M / F):\n");
            scanf("%c",&sexo);
            update.sexo = toupper(sexo);
            if(update.sexo != 'M' && update.sexo != 'F')
            {
                printf("ERRO! Alternativa inválida.\n");
            }
        }
        while(update.sexo != 'M' && update.sexo != 'F');
        break;
    case 3:

        do
        {
            int spc;
            do
            {
                spc = 0;
                do
                {
                    fflush(stdin);
                    printf(">> NOME DE USUÁRIO (MAX - 20):\n");
                    gets(update.login);
                    if(strlen(update.login) > 20)
                    {
                        printf("ERRO! Nome de usuário deve ter no maximo 20 caracteres.\n");
                    }
                }
                while(strlen(update.login) > 20);

                for(cont=0; cont<strlen(update.login); cont++)
                {
                    if(update.login[cont] == ' ')
                    {
                        printf("ERRO! Não pode haver espaços.\n");
                        spc = 1;
                    }
                    break;
                }
            }
            while(spc == 1);
            if(_BD_validarUserName(update.login) == 1)
            {
                printf("Login já utilizado por outro usuário :(\n");
            }
            else
            {
                if(_BD_validarUserName(update.login) == -1)
                {
                    erro = 1;
                }
                else
                {
                    if(_BD_validarUserName(update.login) == -2)
                    {
                        erro = 1;
                        _conStatus02();
                    }
                    else
                    {
                        if(_BD_validarUserName(update.login) == -3)
                        {
                            erro = 1;
                            _conStatus03();
                        }
                        else
                        {
                            erro = 0;
                        }
                    }
                }
            }
        }
        while(erro != 0);
        break;
    case 4:
        do
        {
            do
            {
                printf(">> DIGITE UMA SENHA (APENAS NÚMEROS, MAX - 5):\n");
                fflush(stdin);
                scanf("%d",&update.senha);
                if(update.senha > 99999)
                {
                    printf("ERRO! Senha deve ter no maximo 5 digitos.\n");
                }
            }
            while(update.senha > 99999);

            printf(">> REPITA A SENHA DE ACESSO:\n");
            fflush(stdin);
            scanf("%d",&senhaR);
            if(senhaR != update.senha)
            {
                printf("ERRO! Senhas não coincidem.\n");
            }
        }
        while(senhaR != update.senha);
        break;
    default:
        MessageBox(NULL,"Opção inválida!","ERRO!", MB_OK | MB_ICONERROR);
        system("cls");
        _imcUpdateCadImc(login,senha);
        break;
    }

    if(conObj.conn = mysql_init(0))
    {
        if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
        {

            sprintf(query,"UPDATE usuarios SET nome = '%s', sexo = '%c', login ='%s', senha = '%d' WHERE login = '%s' AND senha = '%d'",update.nome,update.sexo,update.login,update.senha,login,senha);
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {
                printf(">> CADASTRO ATUALIZADO COM SUCESSO!\n");
                mysql_close(conObj.conn);
            }
            else
            {
                _conStatus00(conObj);
                mysql_close(conObj.conn);
                return 0;
            }
        }
        else
        {
            _conStatus02();
        }
    }
    else
    {
        _conStatus03();
    }

}

// VERIFICA SE O NOME DE USUARIO JA EXISTE NO BD
int _BD_validarUserName(char* login)
{

    _BD_configura();
    _BD_pegarConfig(&bdConfig);

    if(conObj.conn = mysql_init(0))
    {
        if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
        {
            char query[200];
            sprintf(query,"select login from usuarios where login = '%s'",login);
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {
                conObj.res = mysql_store_result(conObj.conn);
                while(conObj.row = mysql_fetch_row(conObj.res))
                {
                    if(conObj.row[0])
                    {
                        mysql_close(conObj.conn);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                    break;
                }
            }
            else
            {
                _conStatus00(conObj);
                mysql_close(conObj.conn);
                return -1;
            }
        }
        else
        {
            return -2;
        }
    }
    else
    {
        return -3;
    }

}

// VALIDAR ACESSO
int _BD_validarLogin(char login[20], int senha)
{

    _BD_configura();
    _BD_pegarConfig(&bdConfig);

    if(conObj.conn = mysql_init(0))
    {
        if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
        {
            char query[200];
            sprintf(query,"select login,senha from usuarios where login = '%s' and senha = '%d'",login,senha);
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {
                conObj.res = mysql_store_result(conObj.conn);
                while(conObj.row = mysql_fetch_row(conObj.res))
                {
                    if(conObj.row[0])
                    {
                        mysql_close(conObj.conn);
                        return 1;
                    }
                }
            }
            else
            {
                _conStatus00(conObj);
                mysql_close(conObj.conn);
                return 0;
            }
        }
        else
        {
            _conStatus02();
            return 0;
        }
    }
    else
    {
        _conStatus03();
        return 0;
    }
}

// PEGA DADOS DO USUARIO LOGADO
void _BD_pegarUserInfo(char login[20], int senha)
{

    _BD_configura();
    _BD_pegarConfig(&bdConfig);

    if(conObj.conn = mysql_init(0))
    {
        if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
        {

            int id;
            int i;
            int contReg = 0;
            float contRegTotal = 0;
            float media;
            char ultimoReg[22];
            char info[80];

            strcpy(ultimoReg,"NULL");

            char query[200];
            sprintf(query,"select idusuario,nome,sexo,login,senha from usuarios where login = '%s' and senha = '%d'",login,senha);
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {
                conObj.res = mysql_store_result(conObj.conn);
                while(conObj.row = mysql_fetch_row(conObj.res))
                {
                    id = atoi(conObj.row[0]);
                    int charCont = (80 - (10 + strlen(conObj.row[1]))) / 2;
                    for(i=0; i<charCont; i++)
                    {
                        printf(" ");
                    }
                    printf("BEM-VIND");
                    if(strcmp(conObj.row[2],"M") == 0)
                    {
                        printf("O");
                    }
                    else
                    {
                        printf("A");
                    }
                    printf(" %s",conObj.row[1]);
                    printf("\n");
                }
            }
            else
            {
                _conStatus00(conObj);
                mysql_close(conObj.conn);
            }

            sprintf(query,"SELECT * FROM registros WHERE usuarios_idusuario = '%d'",id);
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {

                conObj.res = mysql_store_result(conObj.conn);
                while(conObj.row = mysql_fetch_row(conObj.res))
                {
                    contReg++;
                    contRegTotal += atof(conObj.row[2]);
                    strcpy(ultimoReg,conObj.row[3]);
                }

                if(contReg != 0)
                {
                    media = contRegTotal/contReg;
                }
                else
                {
                    media = 0;
                }

                printf("     ");
                for(i=0; i<70; i++)
                {
                    printf("-");
                }
                printf("\n");

                char str[24];
                sprintf(info," %d - Registros | Média: %.2f | Último imc [",contReg,media);
                sprintf(str,"%s]",ultimoReg);
                strcat(info,str);

                int tam = strlen(info);
                tam = (80 - tam ) / 2;
                for(i=0; i<tam; i++)
                {
                    printf(" ");
                }
                printf("%s",info);
                printf("\n");

                printf("     ");
                for(i=0; i<70; i++)
                {
                    printf("-");
                }
                printf("\n");

            }
            else
            {
                _conStatus00(conObj);
                mysql_close(conObj.conn);
            }
            mysql_close(conObj.conn);
        }
        else
        {
            _conStatus02();
        }
    }
    else
    {
        _conStatus03();
    }
}

// ADICIONA UM NOVO IMC (REGISTRO) NO BD
void _BD_registrarImc(char login[20], int senha)
{

    _BD_configura();
    _BD_pegarConfig(&bdConfig);
    int i;
    float peso, altura;
    char _id[5], imc[10], query[100];

    fflush(stdin);
    printf(" (Kg)\tDIGITE SEU PESO:  ");
    scanf("%f",&peso);
    printf(" (cm)\tDIGITE SUA ALTURA: ");
    scanf("%f",&altura);
    altura /= 100;
    sprintf(imc,"%.2f",peso = peso / (altura * altura));
    for(i=0; i<strlen(imc); i++)
    {
        if(imc[i] == ',')
        {
            imc[i] = '.';
        }
    }

    if(conObj.conn = mysql_init(0))
    {
        if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
        {
            sprintf(query,"select idusuario from usuarios where login = '%s' and senha = '%d'",login,senha);
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {
                conObj.res = mysql_store_result(conObj.conn);
                while(conObj.row = mysql_fetch_row(conObj.res))
                {
                    strcpy(_id,conObj.row[0]);
                }
            }
            else
            {
                _conStatus00(conObj);
            }

            sprintf(query,"INSERT INTO registros (usuarios_idusuario,imc,datahora) VALUES (%s,%s,'%s')",_id,imc,dataHora());
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {
                printf("IMC REGISTRADO COM SUCESSO!\n");
            }
            else
            {
                _conStatus00(conObj);
            }
            mysql_close(conObj.conn);
        }
        else
        {
            _conStatus02();
        }
    }
    else
    {
        _conStatus03();
    }

}

// EXIBIR TODOS OS REGISTROS DE IMC
void _BD_exibirImc(char login[20], int senha)
{

    _BD_configura();
    _BD_pegarConfig(&bdConfig);
    int i;
    char _id[5];
    printf("\n");
    for(i=0; i<35; i++)
    {
        printf(" ");
    }
    printf("REGISTROS:\n\n");
    if(conObj.conn = mysql_init(0))
    {
        if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
        {
            char query[200];
            sprintf(query,"select idusuario from usuarios where login = '%s' and senha = '%d'",login,senha);
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {
                conObj.res = mysql_store_result(conObj.conn);
                while(conObj.row = mysql_fetch_row(conObj.res))
                {
                    strcpy(_id,conObj.row[0]);
                }
            }
            else
            {
                _conStatus00(conObj);
            }

            fflush(stdin);
            sprintf(query,"select * from registros where usuarios_idusuario = '%s'",_id);
            conObj.qstate = mysql_query(conObj.conn,query);
            if(!conObj.qstate)
            {
                conObj.res = mysql_store_result(conObj.conn);
                int cont = 0,tam = 0;
                char reg[40];
                while(conObj.row = mysql_fetch_row(conObj.res))
                {
                    cont++;
                    sprintf(reg,"%d - [ %s ] - IMC: %s\n",cont,conObj.row[3],conObj.row[2]);
                    tam = strlen(reg);
                    tam = (80 - tam) / 2;
                    for(i=0; i<tam; i++)
                    {
                        printf(" ");
                    }
                    printf("%s",reg);
                    for(i=0; i<80; i++)
                    {
                        printf("-");
                    }
                    if(cont == 25)
                    {
                        break;
                    }
                    fflush(stdout);
                }
            }
            else
            {
                _conStatus00(conObj);
            }
            mysql_close(conObj.conn);
        }
        else
        {
            _conStatus02();
        }
    }
    else
    {
        _conStatus03();
    }

}

// DELETA CONTA CADASTRADA
void _BD_delCad(char login[20], int senha)
{

    _BD_configura();
    _BD_pegarConfig(&bdConfig);

    int senhaR;

    do
    {
        printf(">> DIGITE SUA SENHA PARA CONFIRMAR: ");
        fflush(stdin);
        scanf("%d",&senhaR);
        if(senhaR > 99999)
        {
            printf("ERRO! Senha INVÁLIDA.\n");
        }
    }
    while(senhaR > 99999);

    if(senhaR == senha)
    {
        if(conObj.conn = mysql_init(0))
        {
            if(conObj.conn = mysql_real_connect(conObj.conn,bdConfig.host,bdConfig.user,bdConfig.pass,bdConfig.datb,bdConfig.port,NULL,0))
            {
                char query[200];
                sprintf(query,"DELETE FROM usuarios WHERE login = '%s' AND senha = '%d'",login,senha);
                conObj.qstate = mysql_query(conObj.conn,query);
                if(!conObj.qstate)
                {
                    printf(">> CADASTRO APAGADO COM SUCESSO!\n");
                }
                else
                {
                    _conStatus00(conObj);
                }
                mysql_close(conObj.conn);
            }
            else
            {
                _conStatus02();
            }
        }
        else
        {
            _conStatus03();
        }
    }
    else
    {
        printf("ERRO! Senha INCORRETA.\n");
    }

}

// CRIA E CONFIGURA O ARQ.: "configdb" COM AS INFORMAÇÕES DE ACESSO AO BD
void _BD_configura(void)
{

    char    host[100];
    char    user[100];
    char    pass[100];
    char    datb[100];
    int     port;

    configdb = fopen(fileBd,"r");
    if(configdb == NULL)
    {
        configdb = fopen(fileBd,"w+");

        printf("-- SERVIDOR / IP:  ");
        scanf("%s",host);
        printf("-- USUÁRIO:        ");
        scanf("%s",user);
        printf("! * Caso não haja SENHA, digite null\n");
        printf("-- SENHA:          ");
        fflush(stdin);
        gets(pass);
        printf("-- BANCO DE DADOS: ");
        scanf("%s",datb);
        printf("-- PORTA:          ");
        scanf("%d",&port);

        fprintf(configdb,host);
        fprintf(configdb,"\n");
        fprintf(configdb,user);
        fprintf(configdb,"\n");
        fprintf(configdb,pass);
        fprintf(configdb,"\n");
        fprintf(configdb,datb);
        fprintf(configdb,"\n");
        fprintf(configdb,"%d",port);

        fclose(configdb);
    }
    return;

}

// ALTERA AS CONFIGURAÇÕES DO ARQ.: "configdb" COM AS INFORMAÇÕES DE ACESSO AO BD
void _BD_altConfig(void)
{

    char    host[100];
    char    user[100];
    char    pass[100];
    char    datb[100];
    int     port;

    configdb = fopen(fileBd,"w");

    printf("-- SERVIDOR / IP:  ");
    scanf("%s",host);
    printf("-- USUÁRIO:        ");
    scanf("%s",user);
    printf("! * Caso não haja SENHA, digite null\n");
    printf("-- SENHA:          ");
    fflush(stdin);
    gets(pass);
    printf("-- BANCO DE DADOS: ");
    scanf("%s",datb);
    printf("-- PORTA:          ");
    scanf("%d",&port);

    fprintf(configdb,host);
    fprintf(configdb,"\n");
    fprintf(configdb,user);
    fprintf(configdb,"\n");
    fprintf(configdb,pass);
    fprintf(configdb,"\n");
    fprintf(configdb,datb);
    fprintf(configdb,"\n");
    fprintf(configdb,"%d",port);

    if(ferror(configdb) == 0)
    {
        fclose(configdb);
        printf(">> CONFIGURAÇÕES ALTERADAS COM SUCESSO!\n");
        system("pause");
        return;
    }
    else
    {
        fclose(configdb);
        printf(">> ERRO! NÃO FOI POSSIVEL ALTERAR AS CONFIGURAÇÕES.\n");
        Sleep(1000);
        return;
    }

}

// PEGA AS CONFIGURAÇÕES DE ACESSO DO BD NO ARQUIVO: "configdb"
void _BD_pegarConfig(BASEDEDADOS* bd)
{

    char    host[100];
    char    user[100];
    char    pass[100];
    char    datb[100];
    int     port;

    configdb = fopen(fileBd,"r");
    fscanf(configdb,"%s",host);
    strcpy(bd->host,host);
    fscanf(configdb,"\n%s",user);
    strcpy(bd->user,user);
    fscanf(configdb,"\n\n%s",pass);
    if(strcmp(pass,"null") == 0)
    {
        strcpy(pass,"");
    }
    strcpy(bd->pass,pass);
    fscanf(configdb,"\n\n\n%s",datb);
    strcpy(bd->datb,datb);
    fscanf(configdb,"\n\n\n\n%d",&port);
    bd->port = port;
    fclose(configdb);
    return;

}

#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "np2txt.h"

void txtTeam()
{
    char *lines[] = {
        "________________________________________________________________________________\n",
        "                          UNIVERSIDADE PAULISTA - UNIP\n",
        "                          SUP TEC ANÁLISE DES SISTEMAS\n\n",
        "                         TURMA: DS1A34\tTURNO: MATUTINO\n\n",
        "                    FELIPE MATEUS B NASCIMENTO / RA: N372HD-8\n",
        "                    JOSE R C CARDOSO JUNIOR    / RA: N256BJ-3\n",
        "                    LEVY DE LIRA GOMES         / RA: D7533H-9\n",
        "                    LISVANETE RODRIGUES GARCIA / RA: N2572H-7\n",
        "                    VENNER MANOEL BERTINO      / RA: N33618-8\n",
        "                    WILLIAM BENJAMIM M SAMPAIO / RA: D7534B-7\n",
        "________________________________________________________________________________\n"};

    printf(BHCYN);
    for (int i = 0; i < sizeof(lines) / sizeof(lines[0]); i++)
    {
        for (int c = 0; c < strlen(lines[i]); c++)
        {
            printf("%c", lines[i][c]);
        }
    }

    printf(COLOR_RESET);
}

void txtExit()
{
    printf(BHRED);
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                       b$GO     \n");
    printf("                                                                       @@@G     \n");
    printf("      L@@@@@: ,@@@@@@: E@@@@@$. @@  1@@@@@,    @@;   @@@@@@,   G@@@@U  @@@      \n");
    printf("     i@@. ,@@  @E   @@ b@;  ,@@ @@ S@N  ;@@   N@@@   @@..;@@: @@7  K@WL@@G      \n");
    printf("     @@     @O @K  .@2 Z@.   @@ @$ @$         @T:@r  @@    @G:@1    b@@$@:      \n");
    printf("     @$     @g @@@@@@r Z@@@@@i  @0 @2  G@$$: D@  @@  @@    @By@:    r@0$g       \n");
    printf("     @@    .@K @r   j@.T@. W@T  @$ @@   .W@. @@@@@@z @@    @W.@E    G@          \n");
    printf("     L@@r,n@@ .@8,;r@@ K@.  8@S @@ y@@;.;@@.$@,,,.@@ @@r;7@@. @@G,,0@@$@        \n");
    printf("      :g@@@G  :@@@@@$; j@:   D@;$$  ;$@@@8:.@K    r@yS@@@@B.   n@@@@SB@@        \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf(COLOR_RESET);
}

void txtStarWarsRobos()
{
    printf(BHBLU);
    printf("                                                                                \n");
    printf("                      v@@@@@@@@@@@@@@@@@@uk@@@@@i@@@@@@@@@q                     \n");
    printf("                     @@@@@@@@@@@@@@@@@@@@v@@@@@@7O@@@@@@@@@@:                   \n");
    printf("                    @@@@@J       G@@@@   @@@@@@@G,@@@@  E@@@@L                  \n");
    printf("                   @@@@@@@@@@@@L @@@@@  O@@@@@@@@ B@@@@8@@@@@@j                 \n");
    printf("                  .@@@@@@@@@@@@7i@@@@q 7@@@@:N@@@7;@@@@@@@@@@@@                 \n");
    printf("                         1@@@@@ @@@@@. @@@@@ q@@@@ @@@@@8@@@@@i                 \n");
    printf("                P@@@@@0  @@@@@J @@@@@ O@@@@@@@@@@@.S@@@@i:@@@@M,                \n");
    printf("               @@@@@@@@@@@@@@@ P@@@@OJ@@@@@EEB@@@@F.@@@@@  @@@@@8               \n");
    printf("              :@@@@@@@@@@@@@@5 @@@@@@@@@@@    @@@@@ @@@@@@  O@@@@@L             \n");
    printf("               :7L:. iii7::,   7rv.:ii:i;:    riiir .: .iY   iiiiv1.            \n");
    printf("            i@@@@.  i@@@@   r@@@@, BBMMB@F:@@@@BB@@@@B. B@@@@@@@@@@@@           \n");
    printf("           i@@@@7 .@@@@@Y  Z@@@@:.@@@@@@@E,@@@@@@@@@@@@8@@@@@@@@@@@@@@          \n");
    printf("          :@@@@7 U@@@@@@  @@@@@.,@@@@@@@@N @@@@@. 0@@@@@@@@@@@; F@@@@@@         \n");
    printf("         :@@@@u @@@@@@@Y @@@@@ :@@@@@@@@@0 @@@@@. 1@@@@@@@@@@@S  ,...:i         \n");
    printf("        :@@@@Bk@@@@@@@@F@@@@@ i@@@@@@@@@@E @@@@@@@@@@@@@@@@@@@@@@@@@@@@@F       \n");
    printf("       ,@@@@@@@@@@@@@@@@@@@@ r@@@@@7U@@@@G @@@@@@@@@@@@@@ 5@@@@@@@@@@@@@@@      \n");
    printf("      ,@@@@@@@@@.M@@@@@@@@@ v@@@@@k k@@@@8 @@@@@@@@@@@@v    ...   :G@@@@@@@     \n");
    printf("     .@@@@@@@@M  @@@@@@@@@ j@@@@@@@@@@@@@O @@@@@@ @@@@@@   @@BMB@,  8@@@@@@M    \n");
    printf("    .@@@@@@@@L  E@@@@@@@M 5@@@@@@@@@@@@@@M @@@@@@  @@@@@@v ;@@@@@@BG@@@@@@@@X   \n");
    printf("   ,@@@@@@@@.   @@@@@@@M E@@@@@B    @@@@@@ @@@@@@L .@@@@@@S @@@@@@@@@@@@@@@@@F  \n");
    printf("  7@@@@@@@G    1@@@@@@@ @@@@@@O    ,@@@@@@ @@@@@@@  :@@@@@@@u@@@@@@@@@@@@@@@@@  \n");
    printf("  7r::::::     :i::::: .r:::::      i::::: i::::ii   .::::ir. ,:::::::::::::,   \n");
    printf(BHWHT);
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                          ,:::,                 \n");
    printf("                                                        ,Ms,  BX                \n");
    printf("                                                        sBs2s 9B:               \n");
    printf("                                                        iMrGss9@r               \n");
    printf("                                                         S@29S5B,               \n");
    printf("                                                          B295GB,               \n");
    printf("                                                          SBsXs9                \n");
    printf("                                                     ,:,,:MM,Srrs,,r            \n");
    printf("                                                   :9si  :Xsrsr:  is,r,         \n");
    printf("                                                   @MHB5   :,   sisi2r2i        \n");
    printf("                                                 ,s:MM@9ri,    s@XGHMMG2        \n");
    printf("                                                2s SX s@BMGSrXB@:sBGG@B@:       \n");
    printf("                                              i2s;@B  2@s:rssS@2 GB  BMM@S      \n");
    printf("                                             rB: @Br  MG ,,,rG9  @s  SBMM@M     \n");
    printf("                                              9X rs   9Bi:, sBG 2B   sHM99@B,   \n");
    printf("                  ,sG@BB92i                   r@ :2    @G2i5B@G9Bi   iG92MBS:   \n");
    printf("                :H2:XBG9MsrSs                  Bi G   sBMB@B@MBB@r   :@5XBs     \n");
    printf("               sG5r:sHX22:iXB@                 2M,Mr  rM9M99HSssX@   BX9BM      \n");
    printf("              ,B@92issHrssXSGBB                 Xiss  2B9S,:i2SGS@  @BBBG       \n");
    printf("              G@BG92sss229X99GB,               s9:,,:rB99Hss9@BMrXM@M@Bs        \n");
    printf("              MBSsi:222s2222Hss;               ,HHH   Mr22sM@@M999@B@B          \n");
    printf("              :s,,,,,s: isss:::Xr ,             ,s,   25sXs99siB9sGGB           \n");
    printf("           rS   ri,::irHS2s,ss:rS :,                  5GsBG9Mr 92:9             \n");
    printf("           sX, ,2r,:::,:r2sr,ir;Mrrs        ;         XH:@99B5,2XrG             \n");
    printf("           XS;rs9:,::   r952, r:M5sS        r         9XrB99@2siGrM             \n");
    printf("          ,@Brrs2:,,:r:,,GXG: :;sS59    ,   ,,,       9Gr@S9@S2:5rG             \n");
    printf("           BB:ir2::,isi  9MS2 ,rsSB:   ::,i: ,::      :BrMX9Ss2 SSS             \n");
    printf("           GMssHs:: :ri: sssr,:rr@M   ,  @B@G   ,      GsSsGX5i:Gsi             \n");
    printf("           s@2sB5is2r  ,,  ,,,,,:MX  ri, rGGiS@:ri    SM2ssXMr,sssH2            \n");
    printf("           2B;:@2rMM2,srr:GMG  ,i@s  ;S2:  ,,ssr2:    s@BGHS2HX2sGB9            \n");
    printf("           9@rsBGiG92::,r:ss2:::iMs   rGGS22XXGGr      r@BMMG9GGGG@5            \n");
    printf("          ,BB:s@B,rssrssissrssrs2G2  :Hs:ri:r:,i5s,     sBGB9@9XB99r            \n");
    printf("          :r2ssHGsG2sr:i,:srsrrrSBs  r2, ,    , sH,,,    B@B52G2GX2             \n");
    printf("          B5SGssHXs9s9GBM9XHG@MGB9   ,22ss  ,:222s,,:    MB@9s9XG@r             \n");
    printf("          r9GGXH@X rMB@BMXs2M@BMG,  , ,s22S2H552s, ,::   s@MG:9HGM              \n");
    printf("         sssS2rXMX      rGrs9@BM::ssi,,  :irrr:, ::sH9   sMG5 Xss9              \n");
    printf("        s2r,s2rGMG     29r5s,X@@GHG5XSs,,,,,,,,,:s9SGB   5GGHiXssS              \n");
    printf("       ,MGr,,M9MBX    5Sr,is  B@BXrsHsHSr:::::,sXXr;22 ,,is9r9GssM              \n");
    printf("         sGi:9MSMS    @Si ,s: iiiis2@r2GGsrrris9G2rsM9X2sX@Bss@5 Gr             \n");
    printf("           ssr::::    iM9ssGG9s   :XBHrr9GrrrsG922XSSGGGMG5s: G@HsMS            \n");
    printf("                        rX5ss2,     9BMsMB2rs9@B@G2            :G9sH            \n");
    printf("                                      sGMM9GGMB9s                               \n");
    printf("                                                                                \n");
    printf("                R2-D2                    BB-8             C-3PO                 \n");
    printf("________________________________________________________________________________\n\n");
    printf("                **** Arte gerada com ASCII Generator v2.0.0 ****\n");
    printf("                     - http://ascgendotnet.jmsoftware.co.uk \n");
    printf("                        - http://ascgen2.sourceforge.net\n");
    printf("________________________________________________________________________________\n");
    printf(COLOR_RESET);
}

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "terminal.h"

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

int _confirm_options(char *_title, char *_message, char *_label, char _option_a, char _option_b, int _status)
{
    _msg(_title, _message, _status);
    char op[5];
    printf("%s (%c/%c): ", _label, _option_a, _option_b);
    setbuf(stdin, NULL);
    scanf("%s", op);
    if (toupper(op[0]) == toupper(_option_a))
    {
        return _True;
    }
    else if (toupper(op[0]) == toupper(_option_b))
    {
        return _False;
    }
    return -1;
}

void _confirm(char *_title, char *_message, char *_label, int _status)
{
    _msg(_title, _message, _status);
    printf("%s...", _label);
    setbuf(stdin, NULL);
    getchar();
}

void _clear_terminal()
{
    system(CMD_CLEAR);
}

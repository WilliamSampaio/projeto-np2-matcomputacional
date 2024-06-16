#pragma once

void _msgSuccess(char *title, char *message);
void _msgInfo(char *title, char *message);
void _msgDanger(char *title, char *message);
void _msgWarning(char *title, char *message);
void _msg(char *title, char *message, int status);

int _confirm_options(char *title, char *message, char *label, char option_a, char option_b, int status);
void _confirm(char *title, char *message, char *label, int status);

void _clear_terminal();
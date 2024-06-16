#pragma once

#include <stdio.h>

#include "database.h"

void _user_init(tbl_user_t *);

void _connect();

void _get_data(void *, int, char *, int);

void _set_ptbr_locale();

void *_sdl2_play_sound(void *);
void _play_sound();
void _stop_sound();

void _exit_();

void _logout_txt_option();
void _process_logout();

void _main_menu();
void _star_wars_robos();
void _start_();

void _imcAddIMC();
void _imcLogin();
void _imc_menu();
void _imcReport();
void _imc_session();
void _imcTxtTitle();
void _imcAddUser();
void _imcUpdateUser();

// void _imcDelCadImc(char *, int);

// void load();

void _writeConfig(FILE **);
void _dbSetup();
void _dbGetConfig(conn_info_t *);
void _dbUpdateConfig();
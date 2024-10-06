#ifndef _MY_READKEY_H
#define _MY_READKEY_H

#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include "word/def.h"
#include "word/word.h"

static struct termios lastSavedTermios;
static int lastSavedTermios_echoMode;
static int lastSavedTermios_signalValue;

enum Keys
{
	Key_Esc,
	Key_L,
	Key_S,
	Key_R,
	Key_T,
	Key_I,
	Key_F5,
	Key_F6,
	Key_Up,
	Key_Down,
	Key_Left,
	Key_Right,
	Key_Enter,
	Key_Empty,
};

int rk_readKey(enum Keys *);

int rk_readValue(int *value, int timeout);

int rk_terminal_save();

int rk_terminal_restore();

int rk_terminalMode_set(int isCannonicalMode, int inputTimeoutValue,
						int minChars, int isEchoEnabled, int isSignalProcessed);

#endif // _MY_READKEY_H
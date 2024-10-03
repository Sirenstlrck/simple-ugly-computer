#ifndef _MY_READKEY_H
#define _MY_READKEY_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "simple_computer.h"

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

int rk_readValue();

int rk_terminal_save();

int rk_terminal_restore();

int rk_terminalMode_set(int isCannonicalMode, int inputTimeoutValue,
						int minChars, int isEchoEnabled, int isSignalProcessed);

#endif // _MY_READKEY_H
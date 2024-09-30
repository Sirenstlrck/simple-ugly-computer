#pragma once

#include "mySimpleComputer.h"
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
enum keys
{
	ESC_KEY,
	L_KEY,
	S_KEY,
	R_KEY,
	T_KEY,
	I_KEY,
	F5_KEY,
	F6_KEY,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ENTER,
	EMPTY_KEY,
};

int rk_readkey(enum keys *);
int rk_myTermSave(void);
int rk_myTermRestore(void);
int rk_myTermRegime(int, int, int, int, int);

int rk_readvalue(int *value, int timeout);

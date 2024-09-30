#ifndef _MY_GRAPHICS_H
#define _MY_GRAPHICS_H

#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
/**
 * @brief checks if it's a terminal
 * @return 0 if it's a terminal else -1
 */
int gr_checkTerm();

/**
 * @brief checks if it's a usable size of terminal
 * @return 0 if it's a size of usable terminal else -1
 */
int gr_checkSize();

/**
 * @brief draws memory box
 */
void gr_memoryBox();

/**
 * @brief draws a modified box with the given parameters
 */
void gr_modBox();

void gr_accumulatorBox();
/**
 * @brief draws memory screen
 */
void gr_showMemoryScreen();

void gr_commandCounterBox();

void gr_commandBox();

void gr_flagsBox();

void gr_cpuBox();

void gr_termBox();

void gr_buttonsBox();

void gr_editBox();

int gr_makeFont(int (*arr)[2], int x, int y, char symbol);

void gr_setMinus(int (*arr)[2], int x, int y);

void gr_setPlus(int (*arr)[2], int x, int y);

void gr_setOne(int (*arr)[2], int x, int y);

void gr_setTwo(int (*arr)[2], int x, int y);

void gr_setThree(int (*arr)[2], int x, int y);

void gr_setFour(int (*arr)[2], int x, int y);

void gr_setFive(int (*arr)[2], int x, int y);

void gr_setSix(int (*arr)[2], int x, int y);

void gr_setSeven(int (*arr)[2], int x, int y);

void gr_setEight(int (*arr)[2], int x, int y);

void gr_setNine(int (*arr)[2], int x, int y);

void gr_setZero(int (*arr)[2], int x, int y);

void gr_setA(int (*arr)[2], int x, int y);

void gr_setB(int (*arr)[2], int x, int y);

void gr_setC(int (*arr)[2], int x, int y);

void gr_setD(int (*arr)[2], int x, int y);

void gr_setE(int (*arr)[2], int x, int y);

void gr_setF(int (*arr)[2], int x, int y);

void gr_initFonts(int (*big_arr)[2]);

int gr_writeFont(int (*arr)[2]);

void gr_clearScreen(int start_x, int start_y, int end_x, int end_y);

void gr_workingConsole();

void gr_drawAll();

void gr_initComputerMenu();

void gr_terminalOutput(char *text);
#endif // _MY_GRAPHICS_H
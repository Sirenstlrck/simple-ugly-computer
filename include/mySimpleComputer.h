#ifndef _MY_SIMPLE_COMPUTER_H
#define _MY_SIMPLE_COMPUTER_H

#include "myBigChars.h"
#include "myReadKey.h"
#include "myTerm.h"
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 128
#define CACHE_DATA 10
#define CACHE_SIZE 5
#define FLAGS_SIZE 5

#define OVERFLOW_MASK 0b00001
#define ZERO_DIV_MASK 0b00010
#define MEM_BOUND_ERR_MASK 0b00100
#define IGNORE_IMPULSE_MASK 0b01000
#define WRONG_COMMAND_MASK 0b10000

#define MAX_MEM_NUM_SIZE 0x7FFF

#define MAX_COMMAND_SIZE 0x7F
#define MAX_OPERAND_SIZE 0x7F

typedef void (*sighandler_t)(int);

typedef struct CacheLine
{
	int data[CACHE_DATA];
	int tag;
	int last_access;
	int valid;
	int dirty;
} CacheLine_t;

typedef enum Commands
{
    // clang-format off
	Nop         = 0x00,     // No command
	CpuInfo     = 0x01,     // Author information
	Read        = 0x10,     // Load into accumulator
	Write       = 0x11,     // Get info out of accumulator
	Load        = 0x14,     // Load into accumulator
	Store       = 0x15,     // Get info out of accumulator
	Aad         = 0x1E,     // Sum in accumulator
	Sub         = 0x1F,     // Difference in accumulator
	Divide      = 0x20,     // Divide in accumualtor
	Mul         = 0x21,     // Multiplication in acumualator
	Jump        = 0x28,     // Jump in memory
	Jneg        = 0x29,     // Jump in memory if negative in accumulator
	Jz          = 0x2A,     // Jump in memory if 0 in accumalator
	Halt        = 0x2B,     // Exit
	Not         = 0x33,     // Inversion and getting into mem
	And         = 0x34,     // Logic operation and between accum and mem block
	Or          = 0x35,     // Logic operation or between accum and mem block
	Xor         = 0x36,     // Logic operation xor between accum and mem block
	Jns         = 0x37,     // Go to mem if positive in accumulator
	Jc          = 0x38,     // Go to mem when in add is overflow
	Jnc         = 0x39,     // Go to mem when in add is not overflow
	Jp          = 0x3A,     // Go to mem when last op is even
	Jnp         = 0x3B,     // Go to mem when last op is odd
	Chl         = 0x3C,     // Logical << in accum
	Shr         = 0x3D,     // Logical >> in accum
	Rcl         = 0x3E,     // Logical cycle <<
	Rcr         = 0x3F,     // Logical cycle >>
	Neg         = 0x40,
	Addc        = 0x41,     // addres in accum adds with mem n mem
	Subc        = 0x42,     // addres in accum subtracts with mem n mem
	Loglc       = 0x43,     // logical <<<<
	Logrc       = 0x44,     // logical >>>>
	Rccl        = 0x45,     // Cycle <<<<
	Rccr        = 0x46,     // Cycle >>>>
	Mova        = 0x47,     // from mem to mem in source of accum
	Movr        = 0x48,  
	Movca       = 0x49,
	Movcr       = 0x4A,
	Aaddc2      = 0x4B,
	Subc2       = 0x4C,
    // clang-format on
} Commands_t;


/**
 * @brief Initializes the memory of the SC_COMPUTER.
 */
int sc_memoryInit();
/**
 * @brief Sets the value of the memory at the given address.
 * @return if adress or value are out of bounds, the function returns -1, if
 * fine 0
 * @param address Address of the memory to be set.
 * @param value Value of the memory to be set.
 */
int sc_memorySet(int address, int value);
/**
 * @brief Gets the value of the memory at the given address.
 * @return if adress is out of bounds, the function returns -1, if fine 0
 * @param address Address of the memory to be read.
 * @param value of the memory at the given address.
 */
int sc_memoryGet(int address, int *value);
/**
 * @brief Saves the memory of the SC_COMPUTER to a file.
 * @return 0 if fine, -1 if error (no file or can't write mem).
 * @param filename Name of the file to save the memory to.
 */
int sc_memorySave(char *filename);
/**
 * @brief Loads the memory of the SC_COMPUTER from a file.
 * @return 0 if fine, -1 if error (no file or can't read mem).
 * @param filename Name of the file to load the memory from.
 */
int sc_memoryLoad(char *filename);
/**
 * @brief Initializes the registers of the SC_COMPUTER.
 */
int sc_regInit();
/**
 * @brief Sets the value of the register at the given address.
 * @param reg Address of the register to be set.
 * @param value Value of the register to be set.
 */
int sc_regSet(int reg, int value);
/**
 * @brief Gets the value of the register at the given address.
 * @param reg Address of the register to be read.
 * @param value of the register at the given address.
 */
int sc_regGet(int reg, int *value);
/**
 * @brief Initializes the accumulator of the SC_COMPUTER.
 */
int sc_accumulatorInit();
/**
 * @brief Sets the value of the accumulator.
 * @param value Value of the accumulator to be set.
 */
int sc_accumulatorSet(int value);
/**
 * @brief Gets the value of the accumulator.
 * @param value Value of the accumulator.
 */
int sc_accumulatorGet();
/**
 * @brief Initializes the command counter of the SC_COMPUTER.
 */
int sc_icounterInit(void);
/**
 * @brief Sets the value of the command counter.
 * @param value Value of the command counter to be set.
 */
int sc_icounterSet(int value);
/**
 * @brief Gets the value of the command counter.
 * @param value Value of the command counter.
 */
int sc_icounterGet();
/**
 * @brief encodes command
 * @param sign sign of the command
 * @param command command to be encoded
 * @param operand operand of the command
 * @param value value of the command
 */
int sc_commandEncode(int sign, int command, int operand, int *value);
/**
 * @brief decodes command
 * @param value value of the command
 * @param sign sign of the command
 * @param command command to be decoded
 * @param operand operand of the command
 */
int sc_commandDecode(int value, int *sign, int *command, int *operand);
/**
 * @brief validates command
 * @param command command to be validated
 */
int sc_commandValidate(int command);
/**
 * @brief prints value of cell at given address
 * @param address address of the cell to be printed
 */

void sc_termSet(int address, int input);

int ALU(int command, int operand);

int sc_clockcounterInit();
int sc_clockcounterGet();
int sc_clockcounterSet(int value);

sighandler_t signal(int signum, sighandler_t handler);

void irc(int signum);

void CU(void);

void sc_cacheWrite(int address, int value);
void sc_cacheInit();

int sc_cacheRead(int address);

void printL1();

#endif //  _MY_SIMPLE_COMPUTER_H

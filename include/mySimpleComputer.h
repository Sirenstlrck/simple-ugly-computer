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

// clang-format off

#define MEMORY_SIZE         128
#define CACHE_DATA          10
#define CACHE_SIZE          5
#define FLAGS_SIZE          5

#define OVERFLOW_MASK       0b00001
#define ZERO_DIV_MASK       0b00010
#define MEM_BOUND_ERR_MASK  0b00100
#define IGNORE_IMPULSE_MASK 0b01000
#define WRONG_COMMAND_MASK  0b10000

#define WORD_BITS_COUNT     15

typedef int Word_t;

#define SIGN_OFFSET         (WORD_BITS_COUNT) - 1
#define COMMAND_OFFSET      7
#define OPERAND_OFFSET      0
                                            //0123456789ABCDEF
#define MAX_WORD            0b00000000000000000111111111111111
#define SIGN_MASK           0b00000000000000000100000000000000
#define COMMAND_MASK        0b00000000000000000011111110000000
#define OPERAND_MASK        0b00000000000000000000000001111111


#define MAX_COMMAND_SIZE    0x7F
#define MAX_OPERAND_SIZE    0x7F

// clang-format on

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

static int memory[MEMORY_SIZE];
static int accumulator;
static int instructionCounter;
static int clockCounter;
static int flags;

void sc_memoryInit();

int sc_memorySet(int address, int value);

int sc_memoryGet(int address, int *value);

int sc_memorySave(const char *filename);

int sc_memoryLoad(const char *filename);

void sc_regInit();

int sc_regSet(int reg, int value);

int sc_regGet(int reg, int *value);

void sc_accumulatorInit();

int sc_accumulatorSet(int value);

int sc_accumulatorGet();

void sc_icounterInit();

int sc_icounterSet(int value);

int sc_icounterGet();

int sc_commandEncode(int sign, int command, int operand, int *value);

int sc_commandDecode(int value, int *sign, int *command, int *operand);

int sc_commandValidate(int command);

#endif //  _MY_SIMPLE_COMPUTER_H

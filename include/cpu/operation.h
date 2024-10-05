#ifndef SC_OPERATION_H
#define SC_OPERATION_H

#define IS_OP_IN_RANGE(name, op) op >= name##_FIRST_OP &&op <= name##_LAST_OP

#define DEFINE_OPERATIONS_RANGE(name, first, last)                             \
	name##_FIRST_OP = first, name##_LAST_OP = last,

typedef enum Operation
{

	// MISC OPS
	Nop		= 0x00, // No command
	CpuInfo = 0x01, // Author information
	DEFINE_OPERATIONS_RANGE(MISC, Nop, CpuInfo)

	// IO OPS
	Read  = 0x10, // Load into accumulator
	Write = 0x11, // Get info out of accumulator
	DEFINE_OPERATIONS_RANGE(IO, Read, Write)

	// IO_ACCUM OPS
	Load  = 0x14, // Load into accumulator
	Store = 0x15, // Get info out of accumulator
	DEFINE_OPERATIONS_RANGE(IO_ACCUM, Load, Store)

	// ARITHMETIC OPS
	Add	   = 0x1E, // Sum in accumulator
	Sub	   = 0x1F, // Difference in accumulator
	Divide = 0x20, // Divide in accumualtor
	Mul	   = 0x21, // Multiplication in acumualator
	DEFINE_OPERATIONS_RANGE(ARITHMETIC, Add, Mul)

	// CONTROL OPS
	Jump = 0x28, // Jump in memory
	Jneg = 0x29, // Jump in memory if negative in accumulator
	Jz	 = 0x2A, // Jump in memory if 0 in accumalator
	Halt = 0x2B, // Exit
	DEFINE_OPERATIONS_RANGE(CONTROL, Jump, Halt)

	// USER OPS
	Not	   = 0x33, // Bitwise not. Result in operand cell
	And	   = 0x34, // Op between accum and mem block
	Or	   = 0x35, // Op between accum and mem block
	Xor	   = 0x36, // Op between accum and mem block
	Jns	   = 0x37, // Go to mem if positive in accumulator
	Jc	   = 0x38, // Go to mem when in add is overflow
	Jnc	   = 0x39, // Go to mem when in add is not overflow
	Jp	   = 0x3A, // Go to mem when last op is even
	Jnp	   = 0x3B, // Go to mem when last op is odd
	Chl	   = 0x3C, // Logical << in accum
	Shr	   = 0x3D, // Logical >> in accum
	Rcl	   = 0x3E, // Logical cycle <<
	Rcr	   = 0x3F, // Logical cycle >>
	Neg	   = 0x40,
	Addc   = 0x41, // addres in accum adds with mem n mem
	Subc   = 0x42, // addres in accum subtracts with mem n mem
	Loglc  = 0x43, // logical <<<<
	Logrc  = 0x44, // logical >>>>
	Rccl   = 0x45, // Cycle <<<<
	Rccr   = 0x46, // Cycle >>>>
	Mova   = 0x47, // from mem to mem in source of accum
	Movr   = 0x48,
	Movca  = 0x49,
	Movcr  = 0x4A,
	Aaddc2 = 0x4B,
	Subc2  = 0x4C,
	DEFINE_OPERATIONS_RANGE(USER, Not, Subc2)
} Operation_t;

int sc_operation_isValid(Operation_t command)
{
	return IS_OP_IN_RANGE(MISC, command)	   //
		|| IS_OP_IN_RANGE(IO, command)		   //
		|| IS_OP_IN_RANGE(IO_ACCUM, command)   //
		|| IS_OP_IN_RANGE(ARITHMETIC, command) //
		|| IS_OP_IN_RANGE(CONTROL, command)	   //
		|| IS_OP_IN_RANGE(USER, command);
}

#endif

#ifndef SC_OPERATION_H
#define SC_OPERATION_H

#define IS_OP_IN_RANGE(name, op) (op >= name##_FIRST_OP && op <= name##_LAST_OP)

#define DEFINE_OPERATIONS_RANGE(name, first, last)                             \
	name##_FIRST_OP = first, name##_LAST_OP = last,

typedef enum Operation
{
	Nop		= 0x00, // No command
	CpuInfo = 0x01, // Author information

	// IO OPS
	Read  = 0x10, // Load into accumulator
	Write = 0x11, // Get info out of accumulator
	DEFINE_OPERATIONS_RANGE(IO, Read, Write)

		Load = 0x14, // Load into accumulator
	Store	 = 0x15, // Get info out of accumulator

	// ALU OPS
	Add	   = 0x1E, // Sum in accumulator
	Sub	   = 0x1F, // Difference in accumulator
	Divide = 0x20, // Divide in accumualtor
	Mul	   = 0x21, // Multiplication in acumualator
	DEFINE_OPERATIONS_RANGE(ALU, Add, Mul)

	// CONTROL OPS
	Jump = 0x28, // Jump in memory
	Jneg = 0x29, // Jump in memory if negative in accumulator
	Jz	 = 0x2A, // Jump in memory if 0 in accumalator
	Halt = 0x2B, // Exit
	DEFINE_OPERATIONS_RANGE(CONTROL, Jump, Halt)

	// USER OPS
	// USER ALU OPS 1
	Not = 0x33, // Bitwise not. Result in operand cell
	And = 0x34, // Op between accum and mem block
	Or	= 0x35, // Op between accum and mem block
	Xor = 0x36, // Op between accum and mem block
	DEFINE_OPERATIONS_RANGE(USER_ALU_1, Not, Xor)

	// USER CONTROL OPS 1
	Jns = 0x37, // Go to mem if positive in accumulator
	Jc	= 0x38, // Go to mem when in add is overflow
	Jnc = 0x39, // Go to mem when in add is not overflow
	Jp	= 0x3A, // Go to mem when last op is even
	Jnp = 0x3B, // Go to mem when last op is odd
	DEFINE_OPERATIONS_RANGE(USER_CONTROL_1, Jns, Jnp)

	// USER ALU OPS 2
	Chl	  = 0x3C, // Logical << in accum
	Shr	  = 0x3D, // Logical >> in accum
	Rcl	  = 0x3E, // Logical cycle <<
	Rcr	  = 0x3F, // Logical cycle >>
	Neg	  = 0x40,
	Addc  = 0x41, // addres in accum adds with mem n mem
	Subc  = 0x42, // addres in accum subtracts with mem n mem
	Loglc = 0x43, // logical <<<<
	Logrc = 0x44, // logical >>>>
	Rccl  = 0x45, // Cycle <<<<
	Rccr  = 0x46, // Cycle >>>>
	DEFINE_OPERATIONS_RANGE(USER_ALU_2, Chl, Rccr)

	// USER CONTROL OPS 2
	Mova  = 0x47, // from mem to mem in source of accum
	Movr  = 0x48,
	Movca = 0x49,
	Movcr = 0x4A,
	DEFINE_OPERATIONS_RANGE(USER_CONTROL_2, Mova, Movcr)

	// USER ALU OPS 3 FUUUUUUUUUUUUUUUUUUUUUUUUU
	Aaddc2 = 0x4B,
	Subc2  = 0x4C,
	DEFINE_OPERATIONS_RANGE(USER_ALU_3, Aaddc2, Subc2)
} Operation_t;

static int sc_operation_isIO(Operation_t op)
{
	return IS_OP_IN_RANGE(IO, op) //
		|| op == CpuInfo;
}

static int sc_operation_isControl(Operation_t op)
{
	return IS_OP_IN_RANGE(CONTROL, op)		  //
		|| IS_OP_IN_RANGE(USER_CONTROL_1, op) //
		|| IS_OP_IN_RANGE(USER_CONTROL_2, op) //
		|| op == Load						  //
		|| op == Store;
}

static int sc_operation_isAlu(Operation_t op)
{
	return IS_OP_IN_RANGE(ALU, op)		  //
		|| IS_OP_IN_RANGE(USER_ALU_1, op) //
		|| IS_OP_IN_RANGE(USER_ALU_2, op) //
		|| IS_OP_IN_RANGE(USER_ALU_3, op);
}

static int sc_operation_isValid(Operation_t op)
{
	return op == Nop				  //
		|| sc_operation_isAlu(op)	  //
		|| sc_operation_isControl(op) //
		|| sc_operation_isIO(op);
}

#endif

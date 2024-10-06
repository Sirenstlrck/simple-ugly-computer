#include <ctype.h>
#include <string.h>

#include "cpu/operation.h"

#define SAT_OP(op) {op, #op}

typedef struct
{
	int code;
	char *str;
} StrOpCodePair_t;

static void convertInMatchableCase(char *str)
{
	*str = toupper(*str);

	for (int i = 1; str[i]; ++i)
	{
		str[i] = tolower(str[i]);
	}
}

static StrOpCodePair_t strOpPairs[] = {
	SAT_OP(Nop),	SAT_OP(CpuInfo), SAT_OP(Read),	 SAT_OP(Write),
	SAT_OP(Load),	SAT_OP(Store),	 SAT_OP(Add),	 SAT_OP(Sub),
	SAT_OP(Divide), SAT_OP(Mul),	 SAT_OP(Jump),	 SAT_OP(Jneg),
	SAT_OP(Jz),		SAT_OP(Halt),	 SAT_OP(Not),	 SAT_OP(And),
	SAT_OP(Or),		SAT_OP(Xor),	 SAT_OP(Jns),	 SAT_OP(Jc),
	SAT_OP(Jnc),	SAT_OP(Jp),		 SAT_OP(Jnp),	 SAT_OP(Chl),
	SAT_OP(Shr),	SAT_OP(Rcl),	 SAT_OP(Rcr),	 SAT_OP(Neg),
	SAT_OP(Addc),	SAT_OP(Subc),	 SAT_OP(Loglc),	 SAT_OP(Logrc),
	SAT_OP(Rccl),	SAT_OP(Rccr),	 SAT_OP(Mova),	 SAT_OP(Movr),
	SAT_OP(Movca),	SAT_OP(Movcr),	 SAT_OP(Aaddc2), SAT_OP(Subc2),
};

#define OPERATIONS_COUNT sizeof(strOpPairs) / sizeof(*strOpPairs)

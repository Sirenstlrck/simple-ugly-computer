#include "memory/controller.h"
#include "registers.h"

static void sc_cpu_reset()
{
	sc_reg_reset();
	sc_memoryController_init();
}
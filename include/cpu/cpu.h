#ifndef SC_CENTRAL_PROCESSING_UNIT_H
#define SC_CENTRAL_PROCESSING_UNIT_H

#include "int_handler.h"
#include "memory/controller.h"
#include "registers.h"

static void sc_cpu_reset()
{
	sc_reg_reset();
	sc_memoryController_init();
}

#endif
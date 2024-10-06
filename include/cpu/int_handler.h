#ifndef SC_INTERRUPTION_HANDLER_H
#define SC_INTERRUPTION_HANDLER_H

#include <assert.h>

#include "word/def.h"

int sc_intHandler_wantsToWriteCpuInfo();

void sc_intHandler_reportCpuInfoWrited();

int sc_intHandler_wantsToWrite();

int sc_intHandlet_getWriteData();

int sc_intHandler_isPendingInput();

void sc_intHandler_writeInput(Word_t input);

void sc_intHandler_reset();

void sc_intHandler_tick();

#endif

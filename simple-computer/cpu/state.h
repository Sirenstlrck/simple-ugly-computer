#ifndef SC_CPU_STATE_H
#define SC_CPU_STATE_H

#include <word/def.h>

enum EvaluationState
{
	es_shouldLoadOp,

	es_pendingData,
	es_working,
	es_opHandled,

	es_pendingInput,
	es_wantsToWrite,
	es_wantsToWriteCpuInfo,

	es_halt,
};

struct EvaluationStateData
{
	enum EvaluationState state;
	Word_t loadedOp;
	Word_t loadedData;
	Word_t inputedData;

	struct
	{
		unsigned char requested;
		int address;
	} jump;
};

extern struct EvaluationStateData tickData;

#endif

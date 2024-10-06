#ifndef SC_CPU_STATE_H
#define SC_CPU_STATE_H

#include <word/def.h>

enum EvaluationState
{
	es_working,
	es_shouldLoadOp,
	es_pendingData,
	es_halt,
	es_opHandled,
};

struct EvaluationStateData
{
	enum EvaluationState state;
	Word_t loadedOp;
	Word_t loadedData;
};

extern struct EvaluationStateData tickData;

#endif

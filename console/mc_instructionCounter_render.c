#include "console.h"

void mc_instructionCounter_render()
{
	Label_t label = {103, 18, (Word_t)sc_reg_getInstructionCounter(), Black,
					 White};
	mc_label_render(label);
}
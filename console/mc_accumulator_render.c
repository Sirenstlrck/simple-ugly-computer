#include "console.h"

void mc_accumulator_render()
{
	Label_t label = {78, 18, sc_reg_getAccumulator(), Black, White};
	mc_label_render(label);
}
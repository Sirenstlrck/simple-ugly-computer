#include "console.h"

void mc_accumulator_init()
{
	Label_t label	 = {78, 18, sc_reg_getAccumulator(), Black, White};
	accumulatorLabel = label;
	mc_label_render(accumulatorLabel);
}
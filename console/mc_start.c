#include "console.h"

void signal_handle(int signum)
{
	sc_cpu_reset();
	mc_memoryManipulator_init();
	mc_memoryManipulator_render();

	mc_instructionCounter_init();
	mc_accumulator_init();
	mc_flags_render();

	mc_selectedLabel_set(0);
}

void mc_start()
{
	int exitFlag = 0;
	signal(SIGUSR1, signal_handle);

	mc_memoryManipulator_move(Key_Down);
	mc_memoryManipulator_move(Key_Up);

	enum Keys key;
	while (!exitFlag)
	{
		if (rk_readKey(&key) == 0)
		{
			if (sc_reg_isFlagSetted(IGNORE_IMPULSE_FLAG))
			{
				if (key >= Key_Up && key <= Key_Right)
					mc_memoryManipulator_move(key);
				if (key == Key_I)
					raise(SIGUSR1);
				if (key == Key_F5)
					mc_selectedLabel_set(128);
				if (key == Key_F6)
					mc_selectedLabel_set(129);
				if (key == Key_Enter)
				{
					rk_terminal_save();
					rk_terminalMode_set(1, 100, 0, 1, 0);
					mt_cursorPosition_set(selecionLabel.x_position,
										  selecionLabel.y_position);
					int newValue;
					selecionLabel.background_color = Yellow;
					mc_label_render(selecionLabel);
					if (rk_readValue(&newValue, 100000))
					{
						Label_t updatedLabel;
						switch (selectedAddressIndex)
						{
						case 128:
							sc_reg_setAccumulator(newValue);
							updatedLabel = accumulatorLabel;
							break;
						case 129:
							sc_reg_setInstructionCounter(newValue);
							updatedLabel = instractionCounterLabel;
							break;
						deafult:
							sc_memoryController_set(selectedAddressIndex,
													newValue);
							updatedLabel =
								memoryManipulator[selectedAddressIndex];
							mc_label_render(
								memoryManipulator[selectedAddressIndex]);
							break;
						}
						updatedLabel.content = newValue;
						mc_label_render(updatedLabel);
					}
					rk_terminal_restore();
				}
				if (key == Key_L)
				{
				}
				if (key == Key_S)
				{
				}
			}
			if (key == Key_Esc)
				exitFlag = 1;
		}
	}
}
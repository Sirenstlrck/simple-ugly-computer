#include "../simple-computer/memory/memory.h"
#include "console.h"
#include "cpu/clock_generator.h"
#include "memory/cache_public.h"

void mc_renderCache()
{
	int x = 2;
	int y = 18;
	char buffer[256];
	mt_cursorPosition_set(x, y);
	CacheLine_t cacheLine;
	for (int i = 0; i < CACHE_SIZE; ++i)
	{
		sc_memoryCache_getLine(i, &cacheLine);
		sprintf(buffer, "%d: ", cacheLine.baseAddress / 10);
		write(STDOUT_FILENO, buffer, strlen(buffer));
		mt_cursorPosition_set(x += 4, y);
		for (int j = 0; j < CACHE_LINE_SIZE; ++j)
		{
			char *str = mc_wordToHex(cacheLine.data[j]);
			write(STDOUT_FILENO, str, strlen(str));
			mt_cursorPosition_set(x += 6, y);
		}
		mt_cursorPosition_set(x = 2, y++);
	}
}

void mc_updateRender()
{
	mc_memoryManipulator_init();
	mc_memoryManipulator_render();

	mc_accumulator_init();
	mc_instructionCounter_init();
	selectedAddressIndex = sc_reg_getInstructionCounter();

	mc_flags_render();
	mc_selectedLabel_set(selectedAddressIndex);
	mt_cursorPosition_set(71, 21);
	char buffer[256];
	sprintf(buffer, "%d", sc_clockGenerator_getTicksElapsed());
	write(STDOUT_FILENO, buffer, strlen(buffer));
	mc_renderCache();
}

void signal_handle(int signum)
{
	sc_intHandler_reset();
	mc_memoryManipulator_init();
	mc_memoryManipulator_render();

	mc_instructionCounter_init();
	mc_accumulator_init();
	mc_flags_render();

	mc_renderCache();

	mc_selectedLabel_set(0);
	mc_updateRender();
}

void mc_start()
{
	int exitFlag = 0;
	signal(SIGUSR1, signal_handle);

	sc_clockGenerator_init();
	sc_clockGenerator_setTickHook(mc_updateRender);
	mc_updateRender();

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
					int newValue;
					selecionLabel.background_color = Yellow;
					mc_label_render(selecionLabel);

					mt_cursorPosition_set(selecionLabel.x_position,
										  selecionLabel.y_position);

					int res = rk_readValue(&newValue, 100000);

					if (res == 0)
					{
						switch (selectedAddressIndex)
						{
						case 128:
							sc_reg_setAccumulator(newValue);
							mc_accumulator_init();
							selecionLabel		 = accumulatorLabel;
							selectedAddressIndex = 128;
							break;
						case 129:
							sc_reg_setInstructionCounter(newValue);
							mc_instructionCounter_init();
							selecionLabel		 = instractionCounterLabel;
							selectedAddressIndex = 129;
							break;
						}
						if (selectedAddressIndex >= 0 &&
							selectedAddressIndex < MEMORY_SIZE)
						{
							sc_memoryController_set(selectedAddressIndex,
													newValue);
							mc_memoryManipulator_init();
							mc_memoryManipulator_render();
							selecionLabel =
								memoryManipulator[selectedAddressIndex];
						}
					}
					selecionLabel.background_color = White;
					selecionLabel.foreground_color = Black;
					mc_label_render(selecionLabel);
					rk_terminal_restore();
				}
				if (key == Key_Backspace)
				{
					sc_memoryController_set(selectedAddressIndex, 0);
					mc_memoryManipulator_init();
					mc_memoryManipulator_render();
					mc_selectedLabel_set(selectedAddressIndex);
					mc_label_render(selecionLabel);
				}
				if (key == Key_L)
				{
					mt_cursorPosition_set(4, 31);
					write(STDOUT_FILENO, "Load file: ", 12);
					fflush(stdin);
					char path[100];
					int size;
					size = read(0, path, sizeof(path));

					path[size - 1] = '\0';
					sc_memory_load(path);

					mt_cursorPosition_set(4, 31);
					mt_deleteLine();

					mc_memoryManipulator_init();
					mc_memoryManipulator_render();
					mc_selectedLabel_set(0);
				}
				if (key == Key_S)
				{
					mt_cursorPosition_set(4, 31);

					write(STDOUT_FILENO, "Save file: ", 12);
					fflush(stdin);
					char path[100];
					int size;
					size = read(0, path, sizeof(path));

					path[size - 1] = '\0';
					sc_memory_save(path);

					mt_cursorPosition_set(4, 31);
					mt_deleteLine();

					mc_memoryManipulator_init();
					mc_memoryManipulator_render();
					mc_selectedLabel_set(selectedAddressIndex);
				}
				if (key == Key_T)
				{
					sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 0);
					sc_clockGenerator_tick();
					sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 1);
					mc_updateRender();
				}
			}
			if (key == Key_Esc)
				exitFlag = 1;
			if (key == Key_R)
			{
				if (sc_reg_isFlagSetted(IGNORE_IMPULSE_FLAG))
				{
					sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 0);
					sc_clockGenerator_run();
				}
				else
				{
					sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 1);
					sc_reg_reset();
				}
			}
		}
	}
}
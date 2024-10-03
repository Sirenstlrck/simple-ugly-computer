#include "read_key.h"

int rk_readKey(enum Keys *key)
{
	char buffer[10];
	memset(buffer, 0, sizeof(char) * 2);

	fflush(stdin);
	rk_terminal_save();

	int isImpulseIgnored;
	sc_regGet(IGNORE_IMPULSE_MASK, &isImpulseIgnored);
	if (isImpulseIgnored)
	{
		rk_terminalMode_set(1, 30, 1, 0, 1);
	}
	else
	{
		rk_terminalMode_set(1, 2, 0, 0, 1);
	}

	read(fileno(stdin), buffer, sizeof(buffer));
	if (buffer[0] == '\E')
	{
		switch (buffer[1])
		{
		case '\0':
			*key = Key_Esc;
			break;
		case '[':
			switch (buffer[2])
			{
			case 'A':
				*key = Key_Up;
				break;
			case 'B':
				*key = Key_Down;
				break;
			case 'C':
				*key = Key_Right;
				break;
			case 'D':
				*key = Key_Left;
				break;
			case '1':
				if (buffer[3] == '7' && buffer[4] == '~')
					*key = Key_F6;
				else if (buffer[3] == '5' && buffer[4] == '~')
					*key = Key_F5;
				break;
			default:
				*key = Key_Empty;
				break;
			}
			break;
		default:
			*key = Key_Empty;
			break;
		}
	}
	else if (buffer[0] == '\n' && buffer[1] == '\0')
	{
		*key = Key_Enter;
	}
	else
	{
		switch (buffer[0])
		{
		case 'l':
			*key = Key_L;
			break;
		case 's':
			*key = Key_S;
			break;
		case 'r':
			*key = Key_R;
			break;
		case 't':
			*key = Key_T;
			break;
		case 'i':
			*key = Key_I;
			break;
		default:
			*key = Key_Empty;
			break;
		}
	}
	rk_terminal_restore();
}
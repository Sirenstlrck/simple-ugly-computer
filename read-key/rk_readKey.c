#include "cpu/registers.h"
#include "read_key.h"
#include "terminal.h"

int rk_readValue(int *value, int timeout)
{
	fd_set readfds;
	struct timeval tv;
	int ready;
	char hex_value[10] = {'\0'};

	tv.tv_sec  = timeout;
	tv.tv_usec = 0;

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	ready = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

	if (ready < 0)
	{
		return -1;
	}
	else if (ready == 0)
	{
		return 0;
	}
	else
	{
		if (FD_ISSET(STDIN_FILENO, &readfds))
		{
			int counter = 0;
			while (counter < 5)
			{
				char ch;
				if (read(STDIN_FILENO, &ch, 1) == 1)
				{
					ch = tolower(ch);
					if (counter == 0)
					{
						if (ch != '-' && ch != '+')
						{
							return 0;
						}
					}
					else
					{
						if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
						{
							return 0;
						}
					}
					hex_value[counter++] = ch;
				}
			}
			hex_value[counter] = '\0';
			int sign		   = hex_value[0] == '-' ? 1 : 0;
			int command, operand;
			sscanf(hex_value + 1, "%02x", &command);
			sscanf(hex_value + 3, "%02x", &operand);
			//+1234
			if (sc_word_commandEncode(sign, command, operand, value) == -1)
			{
				return 0;
			}
			return 1;
		}
		return -1;
	}
}

int rk_readKey(enum Keys *key)
{
	char buffer[10];
	memset(buffer, 0, sizeof(char) * 2);

	fflush(stdin);
	rk_terminal_save();

	if (sc_reg_isFlagSetted(IGNORE_IMPULSE_FLAG))
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
	else if (buffer[0] == '\r' && buffer[1] == '\0')
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
	return 0;
}
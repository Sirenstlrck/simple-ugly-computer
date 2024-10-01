#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int main() 
{
    int input_char;

	char buffer [5][100];

    while ((input_char = getchar()) != EOF) 
	{
		if ((input_char >= 'A' && input_char <= 'F') || isdigit(input_char)) 
		{
			switch (input_char) 
			{
				case 'A':
					char str[100] = "     _\n    / \\\n   / _ \\\n  / ___ \\\n /_/   \\_\\\n";
					break;
				case 'B':
					char str[100] = "  ____\n | __ )\n |  _ \\\n | |_) |\n |____/\n";
					break;
			}
		} 
    }

	for(int i = 0; i < 5; ++i)
	{
		write(STDOUT_FILENO, buffer[i], strlen(buffer[i]));
	}
    return 0;
}
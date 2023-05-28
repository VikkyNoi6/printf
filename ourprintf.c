#include "main.h"
#include <string.h>

#define BUFF_SIZE 1024

void write_buffer(char buffer[], int *buff_ind, int *printed_chars);
void write_char(char ch, int *printed_chars);
void write_string(const char *str, int *printed_chars);
void process_conversion(char c, va_list args, int *printed_chars);

/**
*_printf - Custom printf function
*@format: Format string
*
*Return: Number of characters printed
*/
int _printf(const char *format, ...)
{
	int printed_chars = 0;
	va_list args;

	char buffer[BUFF_SIZE];
	int buff_ind = 0;

	if (format == NULL)
		return (-1);
	va_start(args, format);

	for (int i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
			{
				write_buffer(buffer, &buff_ind, &printed_chars);
			}
		}
		else
		{
			write_buffer(buffer, &buff_ind, &printed_chars);
			i++;
			process_conversion(format[i], args, &printed_chars);
		}
	}

	write_buffer(buffer, &buff_ind, &printed_chars);
	va_end(args);

	return (printed_chars);
}

/**
*write_buffer - Writes the buffer to stdout
*@buffer: Character buffer
*@buff_ind: Pointer to buffer index
*@printed_chars: Pointer to printed characters count
*/
void write_buffer(char buffer[], int *buff_ind, int *printed_chars)
{
	if (*buff_ind > 0)
	{
		write(1, buffer, *buff_ind);
		*printed_chars += *buff_ind;
		*buff_ind = 0;
	}
}

/**
*write_char - Writes a character to stdout
*@ch: Character to write
*@printed_chars: Pointer to printed characters count
*/
void write_char(char ch, int *printed_chars)
{
	write(1, &ch, 1);
	(*printed_chars)++;
}
/**
*write_string - Writes a string to stdout
*@str: String to write
*@printed_chars: Pointer to printed characters count
*/
void write_string(const char *str, int *printed_chars)
{
	int len = strlen(str);

	write(1, str, len);
	(*printed_chars) += len;
}

/**
*process_conversion - Processes the conversion specifier
*@c: Conversion specifier
*@args: Variable argument list
*@printed_chars: Pointer to printed characters count
*/
void process_conversion(char c, va_list args, int *printed_chars)
{
	switch (c)
	{
		case 'c':
			{
				char ch = va_arg(args, int);

				write_char(ch, printed_chars);

				break;
			}
		case 's':
			{
				char *str = va_arg(args, char *);

				write_string(str, printed_chars);
				break;
			}
		case '%':
			{
				write_char('%', printed_chars);
				break;
			}
		default:
			break;
	}
}

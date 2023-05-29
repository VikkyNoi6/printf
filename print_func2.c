#include "main.h"

#define BUFF_SIZE 1024

/************************* PRINT UNSIGNED NUMBER *************************/
/**
*print_unsigned - Prints unsigned number
*@buffer: Buffer array to print
*@types: Argument lists
*@flags:  Calculates the number of active flags
*@precision: Precision requirements
*@width: get width
*@size: Size determinant
*Return: The number of characters printed.
*/
int print_unsigned(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	long int convert_size_unsigned(unsigned long int num, int size);

	num = convert_size_unsigned(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = (num % 10) + '0';
		num /= 10;
	}

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
*print_octal - outputs an unsigned number in octal notation.
*@types: Argument lists
*@buffer: Buffer array to print
*@flags:  Calculates the number of active flags
*@width: get width
*@precision: Precision requirements
*@size: Size determinant
*Return: The number of characters printed.
*/
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int y = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsigned(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[y--] = '0';

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
*print_hexadecimal - Prints an unsigned number in hexadecimal notation
*@types: Argument lists
*@buffer: Buffer array to print
*@flags:  Calculates the number of active flags
*@width: get width
*@precision: Precision requirements
*@size: Size determinant
*Return: Number of characters printed
*/
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
*print_hexa_upper - outputs an unsigned number in hexadecimal notation.
*@types: Argument lists
*@buffer: Buffer array to print
*@flags:  Calculates the number of active flags
*@width: get width
*@precision: Precision requirements
*@size: Size determinant
*Return: Number of characters printed
*/
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
*print_hexa - outputs hexadecimal number in lower or upper
*@types: Argument lists
*@map_to: Array of values to which the number should be mapped
*@buffer: Buffer array to print
*@flags:  Calculates the number of active flags
*@flag_ch: Calculates the number of active flags
*@width: get width
*@precision: Precision requirements
*@size: Size determinant
*@size: Size determinant
*Return: Number of characters printed
*/
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsigned(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[y--] = flag_ch;
		buffer[y--] = '0';
	}

	y++;

	return (write_unsgnd(0, y, buffer, flags, width, precision, size));
}


#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @buffer: use print to Buffer array
 * @flags:  computes the active flags
 * @types:  arguments list
 * @width: Width
 * @size: specifier of size
 * @precision: Specification for precision
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @buffer: use print to Buffer array
 * @flags:  computes the active flags
 * @types:  arguments list
 * @width: Width
 * @size: specifier of size
 * @precision: Specification for precision
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, v;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (v = width - length; v > 0; v--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (v = width - length; v > 0; v--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @buffer: use print to Buffer array
 * @flags:  computes the active flags
 * @types:  arguments list
 * @width: Width
 * @size: specifier of size
 * @precision: Specification for precision
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @buffer: use print to Buffer array
 * @flags:  computes the active flags
 * @types:  arguments list
 * @width: Width
 * @size: specifier of size
 * @precision: Specification for precision
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int v = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	if (n == 0)
		buffer[v--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[v--] = (num % 10) + '0';
		num /= 10;
	}

	v++;

	return (write_number(is_negative, v, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @buffer: use print to Buffer array
 * @flags:  computes the active flags
 * @types:  arguments list
 * @width: Width
 * @size: specifier of size
 * @precision: Specification for precision
 * Return: Number of chars printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, v, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (v = 1; v < 32; v++)
	{
		m /= 2;
		a[v] = (n / m) % 2;
	}
	for (v = 0, sum = 0, count = 0; v < 32; v++)
	{
		sum += a[v];
		if (sum || v == 31)
		{
			char z = '0' + a[v];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

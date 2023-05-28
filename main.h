#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

/**
*struct print_format - Create for print formats.
*@type: Type of format.
*@f: Function that prints the format.
*/
typedef struct print_format
{
	char type;
	int (*f)(va_list);
}
print_format_t;

/**
*struct buffer - Struct for the buffer handling.
*@index: Present index in the buffer.
*@size: Sums size of the buffer.
*@buffer: Pointer to the buffer.
*/
typedef struct buffer
{
	int index;
	int size;
	char *buffer;
}
buffer_t;

/* Function prototypes for conversion specifiers */
int _printf(const char *format, ...);
int _write_char(char);
int print_uint(va_list args);
int print_hex(va_list args);
int print_bin(va_list args);
int print_char(va_list args);
int print_str(va_list args);
int print_percent(va_list args);
int print_int(va_list args);
int print_oct(va_list args);
int print_rev_str(va_list args);
int print_rot13(va_list args);
int print_str_non_printable(va_list args);
int print_ptr(va_list args);

/* Helper function prototypes */
int _strlen(char *str);
int _puts(char *str);
int _putchar(char c);
void _reverse_buffer(char *buffer, int size);

#endif

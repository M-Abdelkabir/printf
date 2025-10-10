#include "main.h"

/**
 * parse_length - parse length modifiers from format string
 * @format: format string
 * @i: pointer to current index in format string
 * @l: pointer to length modifiers struct
 * Return: updated index
 */
int parse_length(const char *format, int *i, length_t *l)
{
    int j = *i;

    if (format[j] == 'l')
    {
        l->l = 1;
        j++;
    }
    else if (format[j] == 'h')
    {
        l->h = 1;
        j++;
    }

    *i = j;
    return j;
}

/**
 * get_signed_length - get signed integer with length modifiers
 * @args: variable arguments list
 * @l: length modifiers
 * Return: signed number with appropriate type
 */
long int get_signed_length(va_list args, length_t l)
{
    if (l.l)
        return va_arg(args, long int);
    else if (l.h)
        return (short int)va_arg(args, int);
    else
        return va_arg(args, int);
}

/**
 * get_unsigned_length - get unsigned integer with length modifiers
 * @args: variable arguments list
 * @l: length modifiers
 * Return: unsigned number with appropriate type
 */
unsigned long int get_unsigned_length(va_list args, length_t l)
{
    if (l.l)
        return va_arg(args, unsigned long int);
    else if (l.h)
        return (unsigned short int)va_arg(args, unsigned int);
    else
        return va_arg(args, unsigned int);
}

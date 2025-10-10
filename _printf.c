#include "main.h"

/**
 * _printf - produces output according to a format with buffer
 * @format: character string containing directives
 * 
 * Return: number of characters printed (null byte not concider)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0, i = 0,width = 0;
    char buffer[BUFFER_SIZE];
    int buff_ind = 0;
    long int num;

    flags_t f;
    length_t l;

    if (format == NULL)
        return (-1);

    va_start(args, format);

    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            
            if (format[i] == '\0')
            {
                va_end(args);
                return (-1);
            }
	    f.plus = 0;f.space = 0;f.hash = 0;
	    l.l = 0;l.h = 0;

            i = parse_flags(format, &i, &f);
	    width = parse_width(format, &i, args);
            i = parse_length(format, &i, &l);
    
            switch (format[i])
            {
                case 'c':
                    add_to_buffer(buffer, &buff_ind, va_arg(args, int));
                    count++;
                    break;
                case 's':
                    count += _printString(va_arg(args, char *), buffer, &buff_ind, width);
                    break;
		case 'S':
		    count += _printCustomString(va_arg(args, char *), buffer, &buff_ind, width);
		    break;
                case 'd':
                case 'i':
		    num = get_signed_length(args, l);
                    count += _printInt(num, buffer, &buff_ind);
                    break;
                case 'b':
                    count += _printByte(va_arg(args, unsigned int), buffer, &buff_ind);
                    break;
                case 'u':
                case 'o':
                case 'x':
                case 'X':
		    num = get_unsigned_length(args, l);
                    count += _printOctHexDec(num, format[i], f, buffer, &buff_ind);
                    break;
		case 'p':
		    count += _printAddr(va_arg(args, void*), f, buffer, &buff_ind);
		    break;
                case '%':
                    add_to_buffer(buffer, &buff_ind, '%');
                    count++;
                    break;
                default:
                    add_to_buffer(buffer, &buff_ind, '%');
                    add_to_buffer(buffer, &buff_ind, format[i]);
                    count += 2;
                    break;
            }
        }
        else
        {
            add_to_buffer(buffer, &buff_ind, format[i]);
            count++;
        }
        
        i++;
        
        if (buff_ind >= BUFFER_SIZE - 1)
            flush_buffer(buffer, &buff_ind);
    }

    flush_buffer(buffer, &buff_ind);
    va_end(args);
    return (count);
}

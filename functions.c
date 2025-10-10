#include "main.h"

/**
 * _putchar - writes a character to stdout (without buffer)
 * @c: character to print
 * Return: 1 on success
 */
int _putchar(char c)
{
    return write(1, &c, 1);
}

/**
 * flush_buffer - Write buffer contents to stdout
 * @buffer: Character buffer
 * @buff_ind: Pointer to buffer index
 */
void flush_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
    {
        write(1, buffer, *buff_ind);
        *buff_ind = 0;
    }
}

/**
 * add_to_buffer - Add character to buffer
 * @buffer: Character buffer
 * @buff_ind: Pointer to buffer index
 * @c: Character to add
 */
void add_to_buffer(char buffer[], int *buff_ind, char c)
{
    if (*buff_ind < BUFFER_SIZE)
    {
        buffer[*buff_ind] = c;
        (*buff_ind)++;
    }
}
/**
 * _printString - prints a string with buffer
 * @str: string to print
 * @buffer: character buffer
 * @buff_ind: pointer to buffer index
 * Return: number of characters printed
 */
int _printString(char *str, char buffer[], int *buff_ind,int width)
{
    int padding_done, count = 0;
    int len = 0;
    char *temp = str;

    if (str == NULL)
        str = "(null)";
    
    temp = str;
    while (*temp)
    {
        len++;
        temp++;
    }

    padding_done = handle_padding(buffer, buff_ind, len, width, &count);
    while (*str)
    {
        add_to_buffer(buffer, buff_ind, *str);
        count++;
        str++;
        
        if (*buff_ind >= BUFFER_SIZE - 1)
            flush_buffer(buffer, buff_ind);
    }
    if (!padding_done)
        finish_padding(buffer, buff_ind, len, width, &count);

    return count;
}
/**
 * _printCustomString - prints string with non-printable chars as \xHEX
 * @str: string to print
 * @buffer: character buffer
 * @buff_ind: pointer to buffer index
 * Return: number of characters printed
 */
int _printCustomString(char *str, char buffer[], int *buff_ind, int width)
{
    int padding_done, count = 0;
    int len = 0;
    char *temp = str;
    char hex_digits[] = "0123456789ABCDEF";
    unsigned char c;

    if (str == NULL)
        str = "(null)";
    temp = str;
    while (*temp)
    {
	    len++;
	    temp++;
    }
    padding_done = handle_padding(buffer, buff_ind, len, width, &count);
    while (*str)
    {
        if ((*str > 0 && *str < 32) || *str >= 127)
        {
            add_to_buffer(buffer, buff_ind, '\\');
            add_to_buffer(buffer, buff_ind, 'x');
            count += 2;
            
            c = (unsigned char)*str;
            
            add_to_buffer(buffer, buff_ind, hex_digits[(c >> 4) & 0x0F]);
            add_to_buffer(buffer, buff_ind, hex_digits[c & 0x0F]);
            count += 2;
        }
        else
        {
            add_to_buffer(buffer, buff_ind, *str);
            count++;
        }
        str++;
        
        if (*buff_ind >= BUFFER_SIZE - 1)
            flush_buffer(buffer, buff_ind);
    }
    if(!padding_done)
	    finish_padding(buffer, buff_ind, len, width, &count);
    
    return count;
}
/**
 * _printInt - prints an integer with buffer
 * @nb: integer to print
 * @buffer: character buffer
 * @buff_ind: pointer to buffer index
 * Return: number of characters printed
 */
int _printInt(long int nb, char buffer[], int *buff_ind)
{
    int count = 0;
    unsigned int n;
    char digits[12];
    int i = 0;

    if (nb < 0)
    {
        n = (unsigned int)(-nb);
	add_to_buffer(buffer, buff_ind, '-');
    }else
        n = (unsigned int)nb;

    if (n == 0)
    {
        add_to_buffer(buffer, buff_ind, '0');
        return count + 1;
    }

    /* Extract digits */
    while (n > 0)
    {
        digits[i++] = (n % 10) + '0';
        n /= 10;
    }

    /* Add digits to buffer in reverse order */
    count += i;
    while (--i >= 0)
    {
        add_to_buffer(buffer, buff_ind, digits[i]);
        if (*buff_ind >= BUFFER_SIZE - 1)
            flush_buffer(buffer, buff_ind);
    }

    return count;
}

/**
 * _printByte - prints binary representation with buffer
 * @b: unsigned integer to print in binary
 * @buffer: character buffer
 * @buff_ind: pointer to buffer index
 * Return: number of characters printed
 */
int _printByte(unsigned int b, char buffer[], int *buff_ind)
{
    unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);
    int started = 0;
    int count = 0;

    if (b == 0)
    {
        add_to_buffer(buffer, buff_ind, '0');
        return 1;
    }

    /* skip the first 0 in left*/
    while (mask > 0)
    {
        if (b & mask)
        {
            add_to_buffer(buffer, buff_ind, '1');
            started = 1;
            count++;
        }
        else if (started)
        {
            add_to_buffer(buffer, buff_ind, '0');
            count++;
        }
        mask >>= 1;
        
        if (*buff_ind >= BUFFER_SIZE - 1)
            flush_buffer(buffer, buff_ind);
    }

    return count;
}

/**
 * _printOctHexDec - prints unsigned int in different bases with buffer
 * @number: number to print
 * @type: 'u' for decimal, 'o' for octal, 'x' for lowercase hex, 'X' for uppercase hex
 * @buffer: character buffer
 * @buff_ind: pointer to buffer index
 * Return: number of characters printed
 */
int _printOctHexDec(unsigned long int number, char type, flags_t f, char buffer[], int *buff_ind)
{
    char types[] = {'u', 'o', 'x', 'X'};
    unsigned int bases[] = {10, 8, 16, 16}, i = 0;
    char hexLower[] = "0123456789abcdef";
    char hexUpper[] = "0123456789ABCDEF";
    char output[32];
    int index = 0;
    int count = 0;

    while (types[i] != type && i < 4)
        i++;

    /* Handle # flag for non-decimal bases */
    if (type != 'u')
        count += handle_hash_flag(number, type, f, buffer, buff_ind);
    else
	count += handle_signed_flags(number, f, buffer, buff_ind);

    if (number == 0)
    {
        add_to_buffer(buffer, buff_ind, '0');
        return 1;
    }

    /* Extract digits in reverse order */
    while (number > 0)
    {
        unsigned int digit = number % bases[i];
        output[index++] = (type == 'X') ? hexUpper[digit] : hexLower[digit];
        number /= bases[i];
    }

    /* Add digits to buffer in correct order */
    count = index;
    while (--index >= 0)
    {
        add_to_buffer(buffer, buff_ind, output[index]);
        if (*buff_ind >= BUFFER_SIZE - 1)
            flush_buffer(buffer, buff_ind);
    }

    return count;
}
/**
 * _printAddr - print the address of any variable
 * @addr: the pointer that has the address
 * @buffer: character buffer
 * @buff_ind: pointer to buffer index
 * Return: number of characters printed
 */
int _printAddr(void *addr, flags_t f, char buffer[], int *buff_ind)
{
    int count = 0;
    unsigned long address_value;

    if (addr == NULL)
    {
        add_to_buffer(buffer, buff_ind, '(');
        add_to_buffer(buffer, buff_ind, 'n');
        add_to_buffer(buffer, buff_ind, 'i');
        add_to_buffer(buffer, buff_ind, 'l');
        add_to_buffer(buffer, buff_ind, ')');
        return 5;
    }

    add_to_buffer(buffer, buff_ind, '0');
    add_to_buffer(buffer, buff_ind, 'x');
    count = 2;

    address_value = (unsigned long)addr;

    count += _printOctHexDec(address_value, 'x', f,  buffer, buff_ind);

    return count;
}

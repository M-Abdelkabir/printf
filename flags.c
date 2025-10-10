#include "main.h"

/**
 * parse_flags - parse flag characters from format string
 * @format: format string
 * @i: pointer to current index in format string
 * @f: pointer to flags struct
 * Return: updated index
 */
int parse_flags(const char *format, int *i, flags_t *f)
{
    int j = *i;

    while (format[j] == '+' || format[j] == ' ' || format[j] == '#')
    {
        switch (format[j])
        {
            case '+': f->plus = 1; break;
            case ' ': f->space = 1; break;
            case '#': f->hash = 1; break;
        }
        j++;
    }

    *i = j;
    return j;
}
/**
 * handle_signed_flags - handle + and space flags for signed numbers
 * @num: the number to print
 * @f: flags struct
 * @buffer: character buffer
 * @buff_ind: pointer to buffer index
 * Return: number of chars added by flags
 */
int handle_signed_flags(int num, flags_t f, char buffer[], int *buff_ind)
{
    int count = 0;

    if (num >= 0)
    {
        if (f.space)
        {
            add_to_buffer(buffer, buff_ind, ' ');
            count++;
        }
        if (f.plus)
        {
            add_to_buffer(buffer, buff_ind, '+');
            count++;
        }
    }
    else
    {
        add_to_buffer(buffer, buff_ind, '-');
        count++;
    }

    return count;
}
/**
 * handle_hash_flag - handle # flag for octal and hex
 * @num: the number to print
 * @specifier: conversion specifier
 * @f: flags struct
 * @buffer: character buffer
 * @buff_ind: pointer to buffer index
 * Return: number of chars added by flag
 */
int handle_hash_flag(unsigned int num, char specifier, flags_t f, char buffer[], int *buff_ind)
{
    int count = 0;

    if (f.space)
	add_to_buffer(buffer, buff_ind, ' ');
    if (f.hash && num != 0)
    {
        switch (specifier)
        {
            case 'o':
                add_to_buffer(buffer, buff_ind, '0');
                count++;
                break;

            case 'x':
                add_to_buffer(buffer, buff_ind, '0');
                add_to_buffer(buffer, buff_ind, 'x');
                count += 2;
                break;

            case 'X':
                add_to_buffer(buffer, buff_ind, '0');
                add_to_buffer(buffer, buff_ind, 'X');
                count += 2;
                break;
        }
    }

    return count;
}

#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

/**
 * struct flags - contains flag settings
 * @plus: '+' flag
 * @space: ' ' flag
 * @hash: '#' flag
 */
typedef struct flags
{
    int plus;
    int space;
    int hash;
} flags_t;

/**
 * struct length_modifiers - contains length modifier settings
 * @l: long modifier
 * @h: short modifier
 */
typedef struct length_modifiers
{
    int l;
    int h;
} length_t;

int _printf(const char *format, ...);

int parse_width(const char *format, int *i, va_list args);
int parse_flags(const char *format, int *i, flags_t *f);
int parse_length(const char *format, int *i, length_t *l);
int handle_signed_flags(int num, flags_t f, char buffer[], int *buff_ind);
int handle_hash_flag(unsigned int num, char specifier, flags_t f, char buffer[], int *buff_ind);

int handle_padding(char buffer[], int *buff_ind, int content_len, int width, int *total_printed);
void finish_padding(char buffer[], int *buff_ind, int content_len, int width, int *total_printed);

long int get_signed_length(va_list args, length_t l);
unsigned long int get_unsigned_length(va_list args, length_t l);

void flush_buffer(char buffer[], int *buff_ind);
void add_to_buffer(char buffer[], int *buff_ind, char c);

int _putchar(char c);
int _printString(char *str, char buffer[], int *buff_ind, int width);
int _printCustomString(char *str, char buffer[], int *buff_ind, int width);
int _printInt(long int nb, char buffer[], int *buff_ind);
int _printByte(unsigned int b, char buffer[], int *buff_ind);
int _printOctHexDec(unsigned long int ohd, char type, flags_t f, char buffer[], int *buff_ind);
int _printAddr(void * addr, flags_t f, char buffer[], int *buff_ind);

#endif

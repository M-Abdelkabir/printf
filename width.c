#include "main.h"

/**
 * parse_width - iufvhfuihg
 * @format : jhgfuygr
 * @i : uhgiuerhg
 * @args : kjfgtrhgtiu
 * Return: kjnhgrehg
 */
int parse_width(const char *format, int *i, va_list args)
{
    int width = 0;
    int is_negative = 1;
    
    if (format[*i] == '*')
    {
        (*i)++;
        width = va_arg(args, int);
    }
    else
    { 
	if (format[*i] == '-')
	{
		is_negative = -1;
		(*i)++;
	}
        while (format[*i] >= '0' && format[*i] <= '9')
        {
            width = width * 10 + (format[*i] - '0');
            (*i)++;
        }
    }
    return width * is_negative;
}
/**
 * handle_padding - Gère le padding avant et après le contenu
 * @buffer: buffer de caractères
 * @buff_ind: pointeur vers l'index du buffer
 * @content_len: longueur du contenu à imprimer
 * @width: largeur de champ (négative pour alignement gauche)
 * @total_printed: pointeur vers le compteur total imprimé
 * 
 * Return: 1 si padding avant, 0 si padding après
 */
int handle_padding(char buffer[], int *buff_ind, int content_len, int width, int *total_printed)
{
    int left_align = 0;
    int actual_width;
    int padding, i;

    if (width < 0)
    {
        left_align = 1;
        actual_width = -width;
    }
    else
    {
        left_align = 0;
        actual_width = width;
    }

    padding = actual_width - content_len;
    if (padding < 0) 
        padding = 0;

    /* Right alignment - padding avant le contenu */
    if (!left_align && padding > 0)
    {
        for (i = 0; i < padding; i++)
        {
            add_to_buffer(buffer, buff_ind, ' ');
            (*total_printed)++;
            if (*buff_ind >= BUFFER_SIZE - 1)
                flush_buffer(buffer, buff_ind);
        }
        return 1; /* Padding fait avant */
    }

    return 0; /* Padding à faire après */
}

/**
 * finish_padding - Complète le padding après le contenu
 * @buffer: buffer de caractères
 * @buff_ind: pointeur vers l'index du buffer
 * @content_len: longueur du contenu imprimé
 * @width: largeur de champ (négative pour alignement gauche)
 * @total_printed: pointeur vers le compteur total imprimé
 */
void finish_padding(char buffer[], int *buff_ind, int content_len, int width, int *total_printed)
{
    int left_align = 0;
    int actual_width;
    int padding, i;

    if (width < 0)
    {
        left_align = 1;
        actual_width = -width;
    }
    else
    {
        left_align = 0;
        actual_width = width;
    }

    padding = actual_width - content_len;
    if (padding < 0) 
        padding = 0;

    /* Left alignment - padding après le contenu */
    if (left_align && padding > 0)
    {
        for (i = 0; i < padding; i++)
        {
            add_to_buffer(buffer, buff_ind, ' ');
            (*total_printed)++;
            if (*buff_ind >= BUFFER_SIZE - 1)
                flush_buffer(buffer, buff_ind);
        }
    }
}

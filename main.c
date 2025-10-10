#include "main.h"
#include <stdio.h>

/**
 * main - Entry point to test _printf function
 *
 * Return: Always 0
 */
int main(void)
{
    int len1, len2;

    union {
        void (*func)(void);
        void *ptr;
    } u;
    u.func = (void (*)(void))main;

    /* Test basic characters and strings */
    len1 = _printf("Character: %c\n", 'A');
    len2 = printf("Character: %c\n", 'A');
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    /* Test strings */
    len1 = _printf("String: %-15s.%20S\n", "Hello, World!","Hello \n abdo\t");
    len2 = printf("String: %-15s.%20s\n", "Hello, World!","Hello \n abdo\t");
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    /* Test NULL string - fixed */
    len1 = _printf("NULL string: %s\n", "");
    len2 = printf("NULL string: %s\n", "");
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    /* Test percent sign */
    len1 = _printf("Percent: %%\n");
    len2 = printf("Percent: %%\n");
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    /* Test mixed format */
    len1 = _printf("Char: %c, String: %s, Percent: %%\n", 'X', "test");
    len2 = printf("Char: %c, String: %s, Percent: %%\n", 'X', "test");
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    /* Test plain text without format specifiers */
    len1 = _printf("Just a simple string without format specifiers\n");
    len2 = printf("Just a simple string without format specifiers\n");
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    /* Test multiple characters */
    len1 = _printf("Chars: %c%c%c\n", '1', '2', '3');
    len2 = printf("Chars: %c%c%c\n", '1', '2', '3');
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);
    
    len1 = _printf("I pray for %b times in a day, alhamdo lilah\n", 124);
    len2 = printf("I pray for %d times in a day, alhamdo lilah\n", 123);
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    len1 = _printf("202 in deferent format : Octal = %o , hexa = %x, Hexa = %X, Dec = %u\n",202,202,202,202);
    len2 = printf("202 in deferent format : Octal = %*o , hexa = %x, Hexa = %X, Dec = %u\n",15,202,202,202,202);

    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    len1 = _printf("Address of main is : %p\n", (void *)u.ptr);
    len2 = printf("Address of main is : %p\n", (void *)u.ptr);
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    len1 = _printf("202 in deferent format : Octal = %#+ o , hexa = %#x, Hexa = % X, Dec = %+ u\n",202,202,202,202);
    len2 = printf("202 in deferent format : Octal = %#o , hexa = %#x, Hexa = %X, Dec = %u\n",202,202,202,202);
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

     len1 = _printf("202 in deferent format : Octal = %ho , hexa = %hx, Hexa = %lX, Dec = %hu\n",202222,202222,20222222222222,202222);
    len2 = printf("202 in deferent format : Octal = %ho , hexa = %hx, Hexa = %lX, Dec = %hu\n",202222,202222,20222222222222,202222);
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);

    len1 = _printf("Address of main is : %p\n", (void *)&len1);
    len2 = printf("Address of main is : %p\n", (void *)&len2);
    printf("Length: _printf[%d] vs printf[%d]\n\n", len1, len2);


    return (0);
}

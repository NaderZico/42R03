#include <stdarg.h>
#include <unistd.h>

void print_str(char *str, int *len)
{
    if(!str)
        str = "(null)";
    while(*str)
    {
        write(1, str, 1);
        (*len)++;
        str++;
    }
}

void print_digit(int d, int *len)
{
    if(d == -2147483648)
    {
        write(1, "-2147483648", 11);
        (*len)+= 11;
        return;
    }
    if(d < 0)
    {
        write(1, "-", 1);
        d = -d;
        (*len)++;
    }
    if(d > 9)
        print_digit(d / 10, len);
    write(1, &"0123456789"[d % 10], 1);
    (*len)++;
}

void print_hex(unsigned int h, int *len)
{
    if(h > 15)
        print_hex(h / 16, len);
    write(1, &"0123456789abcdef"[h % 16], 1);
    (*len)++;
}

int ft_printf(const char *format, ...)
{
    va_list list;
    int len = 0;

    va_start(list, format);

    while(*format)
    {
        if(*format == '%')
        {
            format++;
            while(*format == ' ' || *format == '\t')
                format++;
            if(*format == 's')
                print_str(va_arg(list, char *), &len);
            else if(*format == 'd')
                print_digit(va_arg(list, int), &len);
            else if(*format == 'x')
                print_hex(va_arg(list, unsigned int), &len);
            else if(*format == '\0')
                return len;        
        }
        else
        {
        write(1, format, 1);
        len++;
        }
        format++;
    }
    return len;
}

// #include <stdio.h>
// int main(void)
// {
//     int len = 0;
//     len = ft_printf("Hexadecimal for %            d %d %s %x %d", -2147483648, -42, "hi", 0, 42);
//     ft_printf("\n%d", len);
//     printf("\n---------------------------\n");
//     len = printf("Hexadecimal for %           d %d %s %x %d", -2147483648, -42, "hi", 0, 42);
//     printf("\n%d\n", len);
// }
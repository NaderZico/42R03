#include "get_next_line.h"

char *get_next_line(int fd)
{
    char *line;
    int i = 0;
    char c;

    if(fd < 0 || BUFFER_SIZE > INT_MAX || BUFFER_SIZE <= 0)
        return NULL;
    line = malloc(INT_MAX - 10000);
    if(!line)
        return NULL;
    while(read(fd, &c, 1) > 0)
    {
        line[i++] = c;
        if(c == '\n')
            break;
    }
    line[i] = '\0';
    
    if(i == 0)
    {
        free(line);
        return NULL;
    }
    return line;
}

// #include <fcntl.h>
// #include <stdio.h>

// int main(void)
// {
//     int   fd;
//     char *line;

//     fd = open("m.txt", O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return (1);
//     }

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }

//     close(fd);
//     return (0);
// }


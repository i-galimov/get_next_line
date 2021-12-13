#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main (void)
{
    // int i = 0;
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("%s", line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    /* while (i < 100)
    {
        line = get_next_line(fd);
        printf("%s\n", line);
        free(line);
        i++;
    } */
    close(fd);
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
int main ()
{
    int i = 0;
    int fd;
    char *line;
    
    fd = open("file.txt", O_RDONLY);
    while (i < 10)
    {
        line = get_next_line(fd);
        printf("%s", line);
        free(line);
        i++;
    }
    close(fd);
    return 0;
}
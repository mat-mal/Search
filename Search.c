#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int CountFiles(DIR *directory);

int main(void)
{
    char path[256];
    
    DIR *directory = NULL;
    struct dirent *entry;
    struct stat stbuf;
    directory = opendir("./We");

    int counter = CountFiles(directory);
    char buffor[counter][256];
    int i = 0;
    while((entry = readdir(directory)) != NULL)
    {
        sprintf(path, "./We/%s", entry->d_name);
        stat(path, &stbuf);
        if(S_ISDIR(stbuf.st_mode))
        {
            strncpy(buffor[i], entry->d_name, 256);
            printf("Buffor: %s\n", buffor[i]);
            printf("Entry:  %s\n", entry->d_name);
        }
        i++;
    }
    
    //printf("%s\n", buffor[1]);
    char search[256];
    scanf(" %s", search);
    printf("Searching: %s\n", search);

    for(int i = 0; i < counter; i++)
    {
        if(strstr(buffor[i], search) != NULL)
        {
            printf("Result: %s\n", buffor[i]);
        }
        else if(i == counter-1)
        {
            printf("Sorry couldn't find anything\n");
        }
    }

    
    closedir(directory);

    return 0;
}

int CountFiles(DIR *directory)
{
    int counter = 0;
    struct dirent *entry;
    while((entry = readdir(directory)) != NULL)
    {
        counter++;
    }
    printf("%d\n", counter);
    rewinddir(directory);
    return counter;
}
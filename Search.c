#include <stdio.h>
#include <dirent.h>

int CountFiles(DIR *directory);

int main(void)
{
    DIR *directory = NULL;
    struct dirent *entry;
    directory = opendir(".");

    int counter = CountFiles(directory);
    char buffor[counter][256];
    int i = 0;
    while((entry = readdir(directory)) != NULL)
    {
        strncpy(buffor[i], entry->d_name, 256);
        printf("%s\n", buffor[i]);
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
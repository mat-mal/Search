<<<<<<< Updated upstream
#include <stdio.h>
#include <dirent.h>

int CountFiles(DIR *directory);
=======
#include "Search.h"


static int counter = 0;
static int found = 0;
>>>>>>> Stashed changes

int main(int argc, char *argv[])
{
<<<<<<< Updated upstream
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
=======
    char opt;

    string path = "/";
    while((opt = getopt(argc, argv, "d:h")) != -1)
    {
        switch (opt)
        {
            case 'd':
                if(strlen(optarg) > 1 || isalpha(optarg[0]) == 0) 
                {
                    printf("!ERROR! WRONG DRIVE LETTER!\n");
                    printf("Enter correct drive letter!\n");
                    exit(1);
                }
                path[0] = toupper(optarg[0]);
                strcat(path, ":/");
                break;
            case 'h':
            default:
                PrintManPage();
                return 0;
        }
    }
    printf("Path: %s\n", path);
    string* results = calloc(1000, sizeof(string));
    Search(path, WhatToFind(), results);
    PrintResults(results);
>>>>>>> Stashed changes

    return 0;
}

<<<<<<< Updated upstream
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
=======

void Search(string path, string search, string* results)
{
    DIR *directory = NULL;
    directory = opendir(path);
    if(directory == NULL)
    {
        printf("!ERROR! CAN'T FIND PATH!\n");
        printf("Enter correct drive letter!\n");
        exit(1);        
    }
    struct dirent *entry;
    while((entry = readdir(directory)) != NULL)
    {
        string newpath;
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        strcpy(entrypath, path);
        strcat(entrypath, entry->d_name);
        strcat(entrypath, "/");
        stat(entrypath, &stbuf);
        if(S_ISDIR(stbuf.st_mode)) 
        {
            snprintf(newpath, sizeof(newpath), "%s%s/", path, entry->d_name);

            PrintSearching(newpath);

            Search(newpath, search, results);
        }
        else
        {
            lenght = strlen(entry->d_name);
            for(int i = 0; i < lenght; i++)
            {
                entry->d_name[i] = tolower(entry->d_name[i]);
            }
            if(strstr(entry->d_name, search) != NULL)
            {
                int pathlen = strlen(entrypath);
                entrypath[pathlen - 1] = 0;
                strcpy(results[found], entrypath);
                found++;
            }
        }
        counter++;
        if(found >= 1000)
        {
            printf("\nToo many items found, restrict your search input\n");
            exit(0);
        }
    }
    closedir(directory);
}

char* WhatToFind(void)
{
    while(1)
    {
        printf("Search: ");
        fgets(search, 260, stdin);
        lenght = strlen(search);
        if(lenght < 3 && search[0] == 'q')
        {
            exit(0);
        }
        else if(lenght < 4)              //why 4? becouse fgets
        {
            printf("Type more than 2 characers to search\n");
            continue;
        }
        else
        {
            break;
        }
    }
    search[lenght - 1] = 0;
    for(int i = 0; i < lenght; i++)
    {
        search[i] = tolower(search[i]);
    }
    printf("Searching for: %s\n", search);

    return search;
}

void PrintResults(string* results)
{
    for(int i = 0; i < found; i++)
    {
        printf("\nResult: %s", results[i]); 
    }
    printf("\n");

    printf("Items checked: %d\n", counter);
    printf("Items found: %d\n", found);
}

void PrintSearching(string newpath)
{
    if(strlen(newpath) > 100)
    {
        int endhalf = 50;
        int firsthalf = 43;
        int i;
        string path100;
        string pathend;
        char* tmp;
        string partpath[260];

        strcpy(path100, newpath);

        if(path100[0] == '/')
        {
            i = 1;
            strcpy(partpath[0], "");
        }
        else
        {
            i = 0;
        }
    
        tmp = strtok(path100, "/");
        while(tmp != NULL)
        {
            sprintf(partpath[i], "%s", tmp);
            tmp = strtok(NULL, "/");
            //printf("\n\npart%d: %s\n", i, partpath[i]);
            i++;
        }

        strcpy(pathend, partpath[i-1]);
        string tmpend;
        if(strlen(pathend) > 50 && strlen(pathend) < 94) 
        {
            endhalf = strlen(pathend);
            firsthalf = 93 - endhalf;
        }
        if(strlen(pathend) >= 94) 
        {
            endhalf = 94;
            firsthalf = 0;
        }
        for(int j = i-1; j > 0; j--)
        {
            if(strlen(pathend) + strlen(partpath[j-1]) > endhalf) break;
            strcpy(tmpend, partpath[j-1]);
            strcat(tmpend, "/");
            strcat(tmpend, pathend);
            strcpy(pathend, tmpend);
        }

        if(strlen(pathend) + strlen(partpath[0]) > 93)
        {
            strcpy(path100, "/...");
        }
        else
        {
            strcpy(path100, partpath[0]);
        }


        for(int j = 1; j < i-1; j++)
        {
            strcat(path100, "/");
            if(strlen(path100) + strlen(partpath[j]) > firsthalf) break;
            strcat(path100, partpath[j]);
        }

        if(strlen(path100) + strlen(pathend) < 95)
        {
            strcat(path100, ".../");
            strcat(pathend,"/");
            strcat(path100, pathend);
        }
        else
        {
            strncat(path100, pathend, 91);
            strcat(path100, "...");
        }

        //if(strlen(newpath) > 100)
        //{
        //    printf("\n%s\n", path100);
        //    printf("%s\n", pathend);
        //}
        printf("Searching in: %-*s", 100, path100);

    }
    else
    {
        printf("Searching in: %-*s", 100, newpath);      
    }
    //printf("Searching in: %s", newpath);                      //for testing
    printf("\r");
}

void PrintManPage(void)
{
    printf("Usage: Search.exe [options]\n");
    printf("\n              !WARNING! \n");
    printf("This program may cause stack overflow\n\n");
	printf("Options:\n");
	printf("  -h                 Display this information\n");
	printf("  -d <drive letter>  Choose drive to be searched\n");
>>>>>>> Stashed changes
}
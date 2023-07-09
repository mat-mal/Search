#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

typedef char string[256];

int CountFiles(string path);
string* GetFolderElements(int counter, string path);
bool Search(int counter, string path, string* newpath, string search, bool found);
string** GetFolders(string* newpath, int counter, int numfolders);
int CountFolders(int counter, string* newpath);
void GoUp(string path);

int main(void)
{
    string path =  "./";
    //char fulladdress[256];
    bool found = false;
    //DIR *directory = NULL;
    //struct dirent *entry;

    string search = "txt";
    //scanf(" %s", search); // to ma zostać!!!!!!!!
    printf("Searching: %s\n", search);
    int k = 0;
    int maindirectoryfile = CountFiles(path);
    string* inmaindirectory = GetFolderElements(maindirectoryfile, path);    
    int maindirectoryfoldersamount = CountFolders(maindirectoryfile, inmaindirectory);
    string** maindirectoryfolders = GetFolders(inmaindirectory, maindirectoryfile, maindirectoryfoldersamount);
    found = Search(maindirectoryfile, path, inmaindirectory, search, found);


    while(k < maindirectoryfoldersamount)
    {
        strcpy(path, *maindirectoryfolders[k]);
        strcat(path, "/");
        int counter = CountFiles(path);
        string* newpath = GetFolderElements(counter, path);
        int numfolders = CountFolders(counter, newpath);
        found = Search(counter, path, newpath, search, found);


        //need some loop
        while(numfolders != 0)
        {
            int counter = CountFiles(path);
            string* newpath = GetFolderElements(counter, path);
        
            for(int i = 0; i < counter; i++)
            {
                printf("%s\n", newpath[i]);
            }

            int numfolders = CountFolders(counter, newpath);
            string** folders = GetFolders(newpath, counter, numfolders);

            found = Search(counter, path, newpath, search, found);

            if(found == false)
            {
                printf("Sorry couldn't find anything\n");
            }

            if(numfolders == 0)
            {
                GoUp(path);
                break;   
            }
            else
            {
                strcpy(path, *folders[0]);
                strcat(path, "/");
                printf("Entering folder: %s\n", path);
            }
        
        


        free(folders);
        free(newpath);
        }

        printf("\nk: %d\n\n", k);
        k++;
        
    }

    free(maindirectoryfolders);
    free(inmaindirectory);

    //while(entry != NULL)
    //{
        /*directory = opendir(path);

        int counter = CountFiles(directory);
        char buffor[counter][256];
        int i = 0;




        while((entry = readdir(directory)) != NULL)
        {
            strncpy(buffor[i], entry->d_name, 256);
            if(strstr(buffor[i], search) != NULL)
            {
                printf("Result: %s\n", buffor[i]);
                found = true;
            }
            sprintf(fulladdress, "%s/%s", path, buffor[i]);
            stat(fulladdress, &stbuf);
            if(S_ISDIR(stbuf.st_mode)) 
            {

            }


            i++;
        }*/


    

    //}
        //sprintf(path, "%s", entry->d_name);
        //stat(path, &stbuf);
        //if(S_ISDIR(stbuf.st_mode))    
    //printf("%s\n", buffor[i]);


    /*for(int i = 0; i < counter; i++)
    {
        if(strstr(buffor[i], search) != NULL)
        {
            printf("Result: %s\n", buffor[i]);
        }
        else if(i == counter-1)
        {
            printf("Sorry couldn't find anything\n");
        }
    }*/

    


    return 0;
}

int CountFiles(string path)
{
    DIR *directory = NULL;
    directory = opendir(path);
    int counter = 0;
    struct dirent *entry;
    while((entry = readdir(directory)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        counter++;
    }
    printf("%d\n", counter);
    closedir(directory);
    return counter;
}

string* GetFolderElements(int counter, string path)
{
    DIR *directory = NULL;
    directory = opendir(path);
    struct dirent *entry;
    //char buffor[counter][256];
    string* newpath = calloc(counter, 256);

    for(int i = 0; i < counter; i++)
    {
        strcpy(newpath[i], path);
    }

    int j = 0;
    while((entry = readdir(directory)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        
        strcat(newpath[j], entry->d_name);
        j++;
    }

    closedir(directory);

    return newpath;
}

bool Search(int counter, string path, string* newpath, string search, bool found)
{
    for(int i = 0; i < counter; i++)
    {
        if(strstr(newpath[i], search) != NULL)
        {
            printf("Result: %s\n", newpath[i]);
            found = true;

        }
    }

    return found;
}

int CountFolders(int counter, string* newpath)
{
    struct stat stbuf;
    int numfolders = 0;
    for(int i = 0; i < counter; i++)
    {
        stat(newpath[i], &stbuf);
        if(S_ISDIR(stbuf.st_mode)) 
        {   
            printf("Folders: %s\n", newpath[i]);
            numfolders++;
        }
    }

    return numfolders++;
}

string** GetFolders(string* newpath, int counter, int numfolders)
{
    struct stat stbuf;
    int j = 0;
    string** folders =  calloc(numfolders, 256);
    for(int i = 0; i < counter; i++)
    {
        stat(newpath[i], &stbuf);
        if(S_ISDIR(stbuf.st_mode)) 
        {   
            folders[j] = &newpath[i];
            j++;
        }
    }
    
    return folders;
}

void GoUp(string path)
{
    string previousfolder;
    strcpy(previousfolder, path);
    int previouslen = strlen(previousfolder);
    previousfolder[previouslen - 1] = 0;
    char* tmp = strrchr(previousfolder, '/');
    int tmplen = strlen(tmp);
    previousfolder[previouslen - tmplen] = 0;

    printf("Folder up: %s", previousfolder);
}
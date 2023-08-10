#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

typedef char string[260];
struct stat stbuf;
string entrypath;
int lenght;
string search;

void Search(string path, string search, string* results);
void PrintResults(string* results);
char* WhatToFind(void);
void PrintManPage(void);
char Selectdrive(string drive);
void PrintSearching(string newpath);
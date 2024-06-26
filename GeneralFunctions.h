#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


# define MAX_STR_LEN 255
# define SEP_CHAR '_'


///MACROS///

#define CHECK_PRINT_RETURN_0(ptr,str) {if(!ptr){ printf(#str"\n"); return 0;}}

#define CLOSE_FILE_RETURN_0(fp) {fclose(fp); return 0;} 

#define CLOSE_FILE_RETURN_1(fp) {fclose(fp); return 1;}

char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size);
char*	myGetsFile(char* buffer, int size, FILE* fp);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength);
int		getIntPositive(const char* prompt);

void	generalArrayFunction(void* arr, int size, int arrTypeSize, void(*func)(void* element));


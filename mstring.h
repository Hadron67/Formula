#ifndef MSTRING_H
#define MSTRING_H
#include<string.h>
typedef char* Mstring;
Mstring substr(const char *,int ,int );
void sort(int *a,int );
int strfin(const char*,const char *);
Mstring *split(char *input, char *token[]);
int strfine(const char* input,const char* token);

// notice that the elements of the array can't be read-only in the following function.
void stringarray_free(Mstring _this[]);
Mstring strreplicate(char* s);
Mstring* stringarray_filt(Mstring input[],const char* token[]);
int stringarray_contains(Mstring input[],char* s);
#endif

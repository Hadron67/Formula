#ifndef MSTRING_H
#define MSTRING_H
#include<string.h>
typedef char* Mstring;
Mstring substr(const char *,int ,int );
void sort(int *a,int );
int strfin(const char*,const char *);
Mstring *split(char *input, char *token[]);
int strfine(const char* input,const char* token);
void mstring_replace(char* input,const char* tokens[],const char* replacement[],char* output);
// notice that the elements of the array can't be read-only in the following function.
void stringarray_free(Mstring _this[]);
Mstring strreplicate(const char* s);
Mstring* stringarray_filt(Mstring input[],const char* token[]);
int stringarray_contains(Mstring input[],const char* s);
Mstring* stringarray_replace(Mstring input[],const char* token[],const char* replacement[]);
#endif

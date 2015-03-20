#include <stdio.h>
#include <stdlib.h>
#include "formula_typedef.h"
#include "mstring.h"
#include <string.h>

int main(int agv, char *ags[])
{
	char *s = "y=A*sin(omega*t)";
	char* d[] = {"+","-","*","/","(",")","=",NULL};
	//d[5]="(";
	Mstring* a=split(s, d);
	for(int i=0;a[i]!=NULL;i++) printf("%s,",a[i]);
	stringarray_free(a);
	// printf("%d",strfin(s,"7"));
	printf("\n");
	Mstring t=substr("4*8+2 mod 8*4",6,9);
	printf("%s\n",t);
}


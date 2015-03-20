#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mstring.h"

Mstring* split(char *input, char *token[])
{
	int len=strlen(input);
	int enzyme[len];
	char input_temp[len];
	strcpy(input_temp,input);
	int esize = 0;
	int finished = 0;
	while (!finished)
	{
		finished=1;
		  for (int i = 0; token[i] != NULL; i++)
		{
			int p1 = strfin(input_temp, token[i]);
			int p2=strfine(input_temp,token[i]);
			if (p1 >= 0)
			{
				finished=0;
				enzyme[esize++] = p1;
				enzyme[esize++]=p2;
				for(int i=p1;i<p2;i++) input_temp[i]='\1';
				//input_temp[p]='\1';
				//printf("%d :  %s\n", p1, token[i]);
			}
		}
	}
	sort(enzyme, esize);
	Mstring* output=(Mstring*)malloc(sizeof(Mstring)*(esize+2));
	
	output[0]=substr(input,0,enzyme[0]);
	for(int i=0;i<esize-1;i++){
		output[i+1]=substr(input,enzyme[i],enzyme[i+1]);
	}
	output[esize]=substr(input,enzyme[esize-1],len);
	output[esize+1]=NULL;
	return output;
}

Mstring substr(const char *input, int start, int end)
{
	if(end<=start) return strreplicate("");
	if (end > strlen(input))
		end = strlen(input);
	if (start < 0)
		start = 0;
	char *output = (char *)malloc(sizeof(char) * (end - start + 1));
	for (int i = start; i < end; i++)
	{
		output[i - start] = input[i];
	}
	output[end - start] = '\0';
	return output;
}

int strfin(const char *input, const char *token)
{
	int l1 = strlen(input);
	int l2 = strlen(token);
	for (int i = 0; i <= l1 - l2; i++)
	{
		int j;
		for (j = 0; j < l2; j++)
		{
			if (input[i + j] != token[j])
				break;
		}
		if (j >= l2)
			return i;
	}
	return -1;
}
int strfine(const char* input,const char* token){
	int l1=strlen(input);
	int l2=strlen(token);
	for(int i=0;i<=l1-l2;i++){
		int j;
		for(j=l2-1;j>=0;j--){
			if(input[i+j]!=token[j]) break;
		}
		if(j<0) return i+l2;
	}
	return -1;
}
Mstring strreplicate(char* s){
	int l=strlen(s);
	Mstring output=(Mstring)malloc(sizeof(char)*(l+1));
	for(int i=0;i<l;i++){
		output[i]=s[i];
	}
	output[l]='\0';
	return output;
}
void stringarray_free(Mstring _this[]){
	for(int i=0;_this[i]!=NULL;i++) free(_this[i]);
}
void sort(int *a, int size)
{
	int finished = 0;
	while (!finished)
	{
		finished = 1;
		for (int i = 0; i < size - 1; i++)
		{
			if (a[i] > a[i + 1])
			{
				finished = 0;
				int temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
			}
		}
	}
}



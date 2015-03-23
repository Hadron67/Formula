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
	if(esize==0){
		output[0]=strreplicate(input);
		output[1]=NULL;
		return output;
	}
	else{
		output[0]=substr(input,0,enzyme[0]);
	}
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
Mstring strreplicate(const char* s){
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
int stringarray_contains(Mstring input[],const char* s){
	for(int i=0;input[i]!=NULL;i++){
		if(!strcmp(input[i],s)) return 1;
	}
	return 0;
}
Mstring* stringarray_filt(Mstring input[],const char* token[]){
	int length=0;
	int tokencount;
	int i,j;
	for(tokencount=0;token[tokencount]!=NULL;tokencount++);
	
	for(i=0;input[i]!=NULL;i++){
		if(!stringarray_contains(token,input[i])){
			length++;
		}
	}
	length++;
	Mstring* _new=(char**)malloc(sizeof(char*)*length);
	_new[length-1]=NULL;
	length=0;
	for(i=0;input[i]!=NULL;i++){
		if(!stringarray_contains(token,input[i])){
			_new[length++]=strreplicate(input[i]);
		}
	}
	return _new;
}
Mstring* stringarray_replace(Mstring input[],const char* token[],const char* replacement[]){
	int tokencount;
	int length;
	int j;
	for(tokencount=0;token[tokencount]!=NULL;tokencount++);
	for(length=0;input[length]!=NULL;length++);
	Mstring* output=(Mstring*)malloc(sizeof(Mstring)*length);
	for(int i=0;i<length;i++){
		for(j=0;j<tokencount-1;j++){
			if(!strcmp(input[i],token[j])){
				output[i]=strreplicate(replacement[j]);
				break;
			}
		}
		if(j==tokencount){
			output[i]=strreplicate(input[i]);
		}
	}
	return output;
}
Mstring mstring_replace(char* input,const char* tokens[],const char* replacement[]){
	char temp[1000];
	char* t=temp;
	int tokencount;
	for(tokencount=0;tokens[tokencount]!=NULL;tokencount++);
	int j;
	int input_length=strlen(input);
	for(int i=0;i<input_length;i++){
		for(j=0;j<tokencount;j++){
			if(input[i]==tokens[j][0]){
				int k;
				for(k=0;k<strlen(tokens[j])&&(i+k<input_length);k++){
					if(tokens[j][k]!=input[i+k]) break;
				}
				if(k==strlen(tokens[j])){
					for(int l=0;l<strlen(replacement[j]);l++){
						*(t++)=replacement[j][l];
					}
					i+=k-1;
					break;
				}
			}
		}
		if(j==tokencount){
			*(t++)=input[i];
		}
	}
	*(t++)='\0';
	Mstring output=strreplicate(temp);
	return output;
}

#include <stdio.h>
#include <stdlib.h>
#include "formula_typedef.h"
#include "mstring.h"
#include <string.h>
#include "formula_core.h"
#include "formula_float.h"
static FormulaOper oper_test[]={
	{",",0,1,NULL,NULL,NULL},
	{"+",1,1,NULL,NULL,NULL},
	{"-",1,1,NULL,NULL,NULL},
	{"*",2,2,NULL,NULL,NULL},
	{"/",2,2,NULL,NULL,NULL},
	{"%",2,2,NULL,NULL,NULL},
	{"=",1,3,NULL,NULL,NULL},
	{NULL,0,0,NULL,NULL,NULL}
};
static FormulaFunc func_test[]={
	{"sin",1,NULL},
	{"B",1,NULL},
	{NULL,0,NULL}
};
int main(int agv, char *ags[])
{
	char *s = "5*(2-4)";
	FormulaDict* dict=formuladict_new(NULL,NULL,NULL);
	
	formuladict_addoperators(dict,oper_float);
	formuladict_addfunctions(dict,func_test);
	//d[5]="(";
	
	Mstring* a=formula_reserve(ags[1],dict);
	FormulaObject* test=formula_calculate(a,dict);
	stringarray_free(a);
	// printf("%d",strfin(s,"7"));
	printf("%f",*((double*)test->variable));
	formulaobject_free(test);
	printf("\n");

}


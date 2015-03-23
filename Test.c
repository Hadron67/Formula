#include <stdio.h>
#include <stdlib.h>
#include "formula_typedef.h"
#include "mstring.h"
#include <string.h>
#include "formula_core.h"
#include "formula_float.h"
int main(int agv, char *ags[])
{
	char *s = "5*(2-4)";
	FormulaDict* dict=formuladict_new(NULL,NULL,NULL);
	
	formuladict_addoperators(dict,oper_float);
	formuladict_addfunctions(dict,func_float);
	//d[5]="(";
	
	Mstring* a=formula_reserve(ags[1],dict);
	FormulaObject* test=formula_calculate(a,dict);
	stringarray_free(a);
	printf("%f",*((double*)test->variable));
	formulaobject_free(test);
	printf("\n");

}


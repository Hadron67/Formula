#ifndef FORMULA_CORE_H
#define FORMULA_CORE_H
#define isoperator(a,b) (formuladict_getoperator(a,b)==NULL)
#define isfunction(a,b) (formuladict_getfunction(a,b)==NULL)
#define isvariable(a,b) (formuladict_getobject(a,b)==NULL)
#include <stdlib.h>
#include <stdio.h>
#include "formula_typedef.h"
#include "mstring.h"
typedef struct {
	FormulaObject** objs; //pointer array
	FormulaFunc** funcs;   //pointer array	
	FormulaOper** opers;   //pointer array
	int objcount;
	int funccount;
	int opercount;
}FormulaDict;
typedef struct {
	
}FormulaCalculator;
Mstring* formula_precedence(char* formula,FormulaDict* dict);
// transform to reserved polish expression.
Mstring* formula_reserve(char* formula,FormulaDict* dict);
FormulaDict* formuladict_new(FormulaObject** objs,FormulaFunc** funcs,FormulaOper** opers);
void formuladict_addoperators(FormulaDict* dict,FormulaOper* operators);
void formuladict_addfunctions(FormulaDict* dict,FormulaFunc* funcs);
FormulaFunc* formuladict_getfunction(FormulaDict* dict,char* name);
FormulaOper* formuladict_getoperator(FormulaDict* dict,char* name);
FormulaObject* formuladict_getobject(FormulaDict* dict,char* name);
#endif

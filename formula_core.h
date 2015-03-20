#ifndef FORMULA_CORE_H
#define FORMULA_CORE_H
#include "formula_typedef.h"
#include "mstring.h"
typedef struct {
	char* equation;
	
}Formula;
typedef struct {
	FormulaObject** objs; //pointer array
	Algebra** algs;       //pointer array
	
}FormulaDict;
#endif

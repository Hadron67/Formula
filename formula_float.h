#ifndef FORMULA_FLOAT_H
#define FORMULA_FLOAT_H
#include<stdlib.h>
static FormulaVariable* float_init();
static FormulaVariable* float_delete(FormulaVariable* _this);
static FormulaVariable* float_plus(FormulaVariable* a,FormulaVariable* b);
static FormulaTypedef type_float={
	"float",
	sizeof(float),
	float_init,
	float_delete
};
static FormulaOper oper_float[]={
	{"+",1,1,&type_float,&type_float,float_plus},
	{NULL,0,0,NULL,NULL,NULL}
};
#endif

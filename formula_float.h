#ifndef FORMULA_FLOAT_H
#define FORMULA_FLOAT_H
#include<stdlib.h>
#include "formula_typedef.h"
FormulaObject* float_init(FormulaObject* _this);
void float_delete(FormulaObject* _this);
FormulaObject* float_plus(FormulaObject** handle);
FormulaObject* float_minus(FormulaObject** handle);
FormulaObject* float_multiply(FormulaObject** handle);
FormulaObject* float_divide(FormulaObject** handle);

FormulaObject* float_sin(FormulaObject** handle);
FormulaObject* float_cos(FormulaObject** handle);
extern FormulaTypedef type_float;
extern FormulaOper oper_float[];
extern FormulaFunc func_float[];

FormulaObject* formula_float(double a);
double Forfloat_get(FormulaObject* a);
#endif

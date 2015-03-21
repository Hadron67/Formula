#include "formula_float.h"
static FormulaVariable* float_init(){
	float* out=(float*)malloc(sizeof(float));
	return out;
}
static FormulaVariable* float_delete(FormulaVariable* _this);
static FormulaVariable* float_plus(FormulaVariable* a,FormulaVariable* b);

#include "formula_float.h"
#include<stdlib.h>

FormulaTypedef type_float={
	"float",
	sizeof(double),
	float_init,
	float_delete
};

FormulaOper oper_float[]={
	{"+",1,1,"float","float",float_plus},
	{"-",1,1,"float","float",float_minus},
	{"*",2,1,"float","float",float_multiply},
	{"/",2,1,"float","float",float_divide},
	{NULL,0,0,NULL,NULL,NULL}
};
FormulaObject* formula_float(double a){
	double* b=(double*)malloc(sizeof(double));
	*b=a;
	FormulaObject* output=formulaobject_new("",&type_float,b);
}
FormulaObject* float_init(FormulaObject* _this){
	return _this;
}
void float_delete(FormulaObject* _this){
	free(_this->variable);
}
FormulaObject* float_plus(FormulaObject** handle){
	double a1=*((double*)handle[0]->variable);
	double a2=*((double*)handle[-1]->variable);
	return formula_float(a1+a2);
}
FormulaObject* float_minus(FormulaObject** handle){
	double a1=*((double*)handle[0]->variable);
	double a2=*((double*)handle[-1]->variable);
	return formula_float(a1-a2);
}
FormulaObject* float_multiply(FormulaObject** handle){
	double a1=*((double*)handle[0]->variable);
	double a2=*((double*)handle[-1]->variable);
	return formula_float(a1*a2);
}
FormulaObject* float_divide(FormulaObject** handle){
	double a1=*((double*)handle[0]->variable);
	double a2=*((double*)handle[-1]->variable);
	return formula_float(a1/a2);
}

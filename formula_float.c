#include "formula_float.h"
#include<stdlib.h>
#include <math.h>
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
FormulaFunc func_float[]={
	{"sin",1,float_sin},
	{"cos",1,float_cos},
	{NULL,0,NULL}
};
FormulaObject* formula_float(double a){
	double* b=(double*)malloc(sizeof(double));
	*b=a;
	FormulaObject* output=formulaobject_new("",&type_float,b);
}
double Forfloat_get(FormulaObject* a){
	if(!strcmp(a->_typedef->_typename,"float")){
		return *((double*)a->variable);
	}
}
FormulaObject* float_init(FormulaObject* _this){
	return _this;
}
void float_delete(FormulaObject* _this){
	free(_this->variable);
}
FormulaObject* float_plus(FormulaObject** handle){
	double a1=Forfloat_get(handle[0]);
	double a2=Forfloat_get(handle[-1]);
	return formula_float(a1+a2);
}
FormulaObject* float_minus(FormulaObject** handle){
	double a1=Forfloat_get(handle[0]);
	double a2=Forfloat_get(handle[-1]);
	return formula_float(a1-a2);
}
FormulaObject* float_multiply(FormulaObject** handle){
	double a1=Forfloat_get(handle[0]);
	double a2=Forfloat_get(handle[-1]);
	return formula_float(a1*a2);
}
FormulaObject* float_divide(FormulaObject** handle){
	double a1=Forfloat_get(handle[0]);
	double a2=Forfloat_get(handle[-1]);
	return formula_float(a1/a2);
}
FormulaObject* float_sin(FormulaObject** handle){
	double a1=Forfloat_get(handle[0]);
	return formula_float(sin(a1));
}
FormulaObject* float_cos(FormulaObject** handle){
	double a1=Forfloat_get(handle[0]);
	return formula_float(cos(a1));
}

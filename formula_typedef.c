#include "formula_typedef.h"
#include<string.h>
#include<stdlib.h>
FormulaObject* formulaobject_array_get_object(char* name,FormulaObject* objects[]){
	for(int i=0;objects[i]!=NULL;i++){
		if(!strcmp(name,objects[i]->variablename)) {
			return objects[i];
		}
	}
	return NULL;
}
FormulaOperator formulaalgebra_get_operator(char* name,Algebra* alg){
	for(int i=0;alg->operators[i].name=NULL;i++){
		if(!strcmp(name,alg->operators[i].name)){
			return alg->operators[i].oper;
		}
	}
	return NULL;
}
FormulaFunction formulaalgebra_get_function(char* name,Algebra* alg){
	for(int i=0;alg->functions[i].name=NULL;i++){
		if(!strcmp(name,alg->functions[i].name)){
			return alg->functions[i].func;
		}
	}
	return NULL;
}
FormulaObject* formulaobject_new(char* name,FormulaTypedef* _typedef,FormulaVariable* variable){
	FormulaObject* _this=(FormulaObject*)malloc(sizeof(FormulaObject));
	_this->variablename=name;
	_this->_typedef=_typedef;
	_this->variable=variable;
	return _this;
}

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

FormulaObject* formulaobject_new(char* name,FormulaTypedef* _typedef,FormulaVariable* variable){
	FormulaObject* _this=(FormulaObject*)malloc(sizeof(FormulaObject));
	_this->variablename=name;
	_this->_typedef=_typedef;
	_this->variable=variable;
	return _this;
}

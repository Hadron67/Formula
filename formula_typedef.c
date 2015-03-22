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
	if(name!=NULL) _this->variablename=strreplicate(name);
	_this->_typedef=_typedef;
	if(variable==NULL){
		_this->variable=(FormulaVariable*)malloc(_typedef->size);
		_typedef->constructor(_this);
	}
	else{
		_this->variable=variable;
	}
	return _this;
}
void formulaobject_free(FormulaObject* obj){
	obj->_typedef->destructor(obj->variable);
	free(obj);
}

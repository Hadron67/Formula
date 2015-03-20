#ifndef FORMULA_TYPEDEF_H
#define FORMULA_TYPEDEF_H
#include <string.h>
struct _FormulaTypedef;
typedef void FormulaVariable;
typedef FormulaVariable* (*FormulaFunction)(FormulaVariable* a);
typedef FormulaVariable* (*FormulaOperator)(FormulaVariable* a,FormulaVariable* b);
typedef FormulaVariable* (*FormulaAlloc)();
typedef FormulaVariable* (*FormulaDelete)(FormulaVariable* _this);
typedef FormulaVariable* (*FormulaCast)(FormulaVariable* from);
//type cast function
typedef struct {
	struct _FormulaTypedef* type_from;
	struct _FormulaTypedef* type_to;
	FormulaCast formulacaster;
}FormulaCastFunc;
//information about a type
typedef struct _FormulaTypedef{
	char* _typename;
	FormulaAlloc allocor;
	FormulaDelete destructor;
}FormulaTypedef;
//define a function
typedef struct {
	char* name;
	FormulaTypedef* type_arg;
	FormulaFunction func;
}FormulaFunc;
//define an operator
typedef struct {
	char* name;
	int priority;
	int albel;
	FormulaTypedef* type_arg1;
	FormulaTypedef* type_arg2;
	FormulaOperator oper;
}FormulaOper;

//define algebra rule system
typedef struct {
	FormulaFunc* functions; //array
	FormulaOper* operators; //array
}Algebra;
//FormulaObject is used in the formula interpretion.
typedef struct {
	char* variablename;
	FormulaTypedef* _typedef;
	FormulaVariable* variable;
}FormulaObject;

FormulaObject* formulaobject_array_get_object(char* name,FormulaObject* objects[]);
FormulaOperator formulaalgebra_get_operator(char* name,Algebra* alg);
FormulaFunction formulaalgebra_get_function(char* name,Algebra* alg);
FormulaObject* formulaobject_new(char* name,FormulaTypedef* _typedef,FormulaVariable* variable);
#endif

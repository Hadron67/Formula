#ifndef FORMULA_TYPEDEF_H
#define FORMULA_TYPEDEF_H
#include <string.h>
struct _FormulaTypedef;
typedef void FormulaVariable;
typedef FormulaVariable* (*FormulaFunction)(FormulaVariable* a[]);
typedef FormulaVariable* (*FormulaOperator)(FormulaVariable* a,FormulaVariable* b);
typedef FormulaVariable* (*FormulaInit)(FormulaVariable* _this);
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
	int size;
	FormulaInit constructor;
	FormulaDelete destructor;
}FormulaTypedef;
//define a function
typedef struct {
	char* name;
	int argscount;
	FormulaTypedef** type_arg; //pointer array
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


//FormulaObject is used in the formula interpretion.
typedef struct {
	char* variablename;
	FormulaTypedef* _typedef;
	FormulaVariable* variable;
}FormulaObject;

FormulaObject* formulaobject_array_get_object(char* name,FormulaObject* objects[]);
FormulaObject* formulaobject_new(char* name,FormulaTypedef* _typedef,FormulaVariable* variable);
#endif

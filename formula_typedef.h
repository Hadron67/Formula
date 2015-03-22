#ifndef FORMULA_TYPEDEF_H
#define FORMULA_TYPEDEF_H
#include <string.h>
typedef struct _FormulaTypedef FormulaTypedef;
typedef struct _FormulaObject FormulaObject;
typedef struct _FormulaOper FormulaOper;
typedef struct _FormulaFunc FormulaFunc;
typedef void FormulaVariable;

typedef FormulaObject* (*FormulaFunction)(FormulaObject* a);
typedef FormulaObject* (*FormulaOperator)(FormulaObject* a,FormulaObject* b);
typedef FormulaObject* (*FormulaInit)(FormulaObject* _this);
typedef FormulaObject* (*FormulaDelete)(FormulaObject* _this);
typedef FormulaObject* (*FormulaCast)(FormulaObject* from);
//type cast function
typedef struct {
	FormulaTypedef* type_from;
	FormulaTypedef* type_to;
	FormulaCast formulacaster;
}FormulaCastFunc;
//information about a type
struct _FormulaTypedef{
	char* _typename;
	int size;
	FormulaInit constructor;
	FormulaDelete destructor;
};
//define a function
struct _FormulaFunc{
	char* name;
	int argscount;
	FormulaFunction func;
};
//define an operator
struct _FormulaOper{
	char* name;
	int priority;
	int albel;
	FormulaOperator oper;
};


//FormulaObject is used in the formula interpretion.
struct _FormulaObject{
	char* variablename;
	FormulaTypedef* _typedef;
	FormulaVariable* variable;
};

FormulaObject* formulaobject_array_get_object(char* name,FormulaObject* objects[]);
FormulaObject* formulaobject_new(char* name,FormulaTypedef* _typedef,FormulaVariable* variable);
#endif

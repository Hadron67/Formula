#include "formula_core.h"
#include "formula_typedef.h"
#define isnum(a) ((a)>='0'&&(a<='9'))
// basic type
#include "formula_float.h"
//
int priority(FormulaDict* dict,char* name){
	if(!strcmp(name,"(")) return -1;
	FormulaOper* oper=formuladict_getoperator(dict,name);
	FormulaFunc* func=formuladict_getfunction(dict,name);
	if(oper==NULL&&func==NULL) return 0;
	else if(func!=NULL) return 10000;
	else return oper->priority;
}
int isnumber(char* name){
	for(int i=0;i<strlen(name);i++){
		if((name[i]>'9'||name[i]<'0')&&name[i]!='.') return 0;
	}
	return 1;
}
void addzero(char* input,char* output){
	char* t=output;
	int len=strlen(input);
	for(int i=0;i<len;i++){
		if(i==0&&i<len-1){
			if(input[i]=='-'){
				*(t++)='0';
			}
		}
		else {
			if(input[i]=='-'&&!isnum(input[i-1])){
				*(t++)='0';
			}
		}
		*(t++)=input[i];
	}
	*(t++)='\0';
}
//
Mstring* formula_precedence(char* formula,FormulaDict* dict){
	const char* tokens_replace[]={",",NULL};
	const char* replacement[]={")(",NULL};
	int len=strlen(formula);
	char temp[len*2];
	addzero(formula,temp);
	char* formula1[len*2];
	mstring_replace(temp,tokens_replace,replacement,formula1);
	int operatorcount=dict->opercount;
	Mstring* operators=(char**)malloc(sizeof(char*)*(operatorcount+4));
	operators[0]=strreplicate("(");
	operators[1]=strreplicate(")");
	operators[2]=strreplicate(",");
	for(int i=3;i<operatorcount+3;i++){
		operators[i]=strreplicate(dict->opers[i-3]->name);
	}
	operators[operatorcount+3]=NULL;
	Mstring* splited_formulas=split(formula1,operators);
	static const char* tokens[]={"",NULL};
	Mstring* output=stringarray_filt(splited_formulas,tokens);
	stringarray_free(operators);
	stringarray_free(splited_formulas);
	return output;
}
Mstring* formula_reserve(char* formula,FormulaDict* dict){
	Mstring* divided=formula_precedence(formula,dict);
	int len;
	for(len=0;divided[len]!=NULL;len++);
	Mstring* output=(Mstring*)malloc(sizeof(Mstring)*(len+1));
	int t=0;
	Mstring s_stack[len+1];
	int stack_top=0;
	for(int i=0;i<len;i++){
		if(!strcmp(divided[i],"(")){
			s_stack[stack_top++]=divided[i];
		}
		else if(!strcmp(divided[i],")")){
			while(strcmp(s_stack[stack_top-1],"(")!=0){
				output[t++]=strreplicate(s_stack[--stack_top]);
			}
			--stack_top;
		}
		else if(isnumber(divided[i])||isvariable(dict,divided[i])){
			output[t++]=strreplicate(divided[i]);
		}
		else{
			FormulaOper* oper=formuladict_getoperator(dict,divided[i]);
			if(oper!=NULL){
				if(stack_top==0){
					s_stack[stack_top++]=divided[i];
				}
				else{
					if(priority(dict,divided[i])>priority(dict,s_stack[stack_top-1])){
						s_stack[stack_top++]=divided[i];
					}
					else{
						while(priority(dict,divided[i])<=priority(dict,s_stack[stack_top-1])){
							output[t++]=strreplicate(s_stack[--stack_top]);
						}
						s_stack[stack_top++]=divided[i];
					}
				}
				continue;
			}
			FormulaFunc* func=formuladict_getfunction(dict,divided[i]);
			if(func!=NULL){
				s_stack[stack_top++]=divided[i];
			}
			else{
				printf("error: unknown symbol: %s \n",divided[i]);
			}
		}
	}
	while(stack_top-->0){
		output[t++]=strreplicate(s_stack[stack_top]);
	}
	output[t++]=NULL;
	static const char* tokens[]={"",NULL};
	Mstring* out=stringarray_filt(output,tokens);
	stringarray_free(output);
	//free(s_stack);
	stringarray_free(divided);
	return out;
}
FormulaObject* formula_calculate(Mstring* reservedpolish,FormulaDict* dict){
	//TODO:calculate a formula.
	int length;
	for(length=0;reservedpolish[length]!=NULL;length++);
	FormulaObject* result_stack[length+1];
	result_stack[0]=NULL;
	FormulaObject** handle=result_stack+1;
	
	for(int i=0;i<length;i++){
		FormulaOper* oper;
		FormulaFunc* func;
		if(isnumber(reservedpolish[i])){
			double* temp=(double*)malloc(sizeof(double));
			*temp=strtod(reservedpolish[i],NULL);
			*(handle++)=formulaobject_new("",&type_float,temp);
			continue;
		}
		if(handle-result_stack>=3){
			if(NULL!=(oper=formuladict_findoperator(dict,handle[-1]->_typedef->_typename,handle[-2]->_typedef->_typename,reservedpolish[i]))){
				FormulaObject* temp=oper->oper(handle-1);
				formulaobject_free(*(--handle));
				formulaobject_free(*(--handle));
				*(handle++)=temp;
				continue;
			}
		}
		if(NULL!=(func=formuladict_getfunction(dict,reservedpolish[i]))){
			FormulaObject* temp=func->func(handle-1);
			for(int j=0;j<func->argscount;j++){
				formulaobject_free(*(--handle));
			}
			*(handle++)=temp;
			continue;
		}
	}
	return *(--handle);
}
FormulaDict* formuladict_new(){
	FormulaDict* dict=(FormulaDict*)malloc(sizeof(FormulaDict));
	dict->objs=NULL;
	dict->funcs=NULL;
	dict->opers=NULL;
	dict->objcount=0;
	dict->funccount=0;
	dict->opercount=0;
	return dict;
}
void formuladict_addoperators(FormulaDict* dict,FormulaOper* operators){
	int opercount=0;
	for(opercount=0;operators[opercount].name!=NULL;opercount++);
	dict->opercount+=opercount;
	if(dict->opers!=NULL){
		dict->opers=(FormulaOper**)realloc(dict->opers,sizeof(FormulaOper**)*dict->opercount);
	}
	else{
		dict->opers=(FormulaOper**)malloc(sizeof(FormulaOper**)*opercount);
	}
	for(int i=0;i<opercount;i++){
		dict->opers[i]=&operators[i];
	}
}
void formuladict_addfunctions(FormulaDict* dict,FormulaFunc* funcs){
	int funccount;
	for(funccount=0;funcs[funccount].name!=NULL;funccount++);
	dict->funccount+=funccount;
	if(dict->funcs!=NULL){
		dict->funcs=(FormulaFunc**)realloc(dict->funcs,sizeof(void*)*dict->opercount);
	}
	else{
		dict->funcs=(FormulaFunc**)malloc(sizeof(void*)*funccount);
	}
	for(int i=0;i<funccount;i++){
		dict->funcs[i]=&funcs[i];
	}
}
FormulaFunc* formuladict_getfunction(FormulaDict* dict,char* name){
	if(dict->funcs==NULL) return NULL;
	for(int i=0;i<dict->funccount;i++){
		if(!strcmp(name,dict->funcs[i]->name)){
			return dict->funcs[i];
		}
	}
	return NULL;
}
FormulaOper* formuladict_getoperator(FormulaDict* dict,char* name){
	if(dict->opers==NULL) return NULL;
	for(int i=0;i<dict->opercount;i++){
		if(!strcmp(name,dict->opers[i]->name)){
			return dict->opers[i];
		}
	}
	return NULL;
}
FormulaOper* formuladict_findoperator(FormulaDict* dict,char* type1,char* type2,char* name){
	if(dict->opers==NULL) return NULL;
	for(int i=0;i<dict->opercount;i++){
		if(dict->opers[i]->albel){
			if(!strcmp(dict->opers[i]->type_arg1,type1)&&!strcmp(dict->opers[i]->type_arg2,type2)||!strcmp(dict->opers[i]->type_arg1,type2)&&!strcmp(dict->opers[i]->type_arg2,type1)){
				if(!strcmp(name,dict->opers[i]->name)) return dict->opers[i];
			}
		}
		else{
			if(!strcmp(dict->opers[i]->type_arg1,type1)&&!strcmp(dict->opers[i]->type_arg1,type1)){
				return dict->opers[i];
			}
		}
	}
	return NULL;
}
FormulaObject* formuladict_getobject(FormulaDict* dict,char* name){
	if(dict->objs==NULL) return NULL;
	for(int i=0;i<dict->objcount;i++){
		if(!strcmp(name,dict->objs[i]->variablename)){
			return dict->objs[i];
		}
	}
	return NULL;
}

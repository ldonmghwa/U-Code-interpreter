#include <iostream>
#include "struct.h"
using namespace std;

char* label_Pop(LinkedLblStk **lblist, char *label){
	if ((*lblist)->top == NULL){
		return NULL;
	}
	Label *delete_stk = (*lblist)->top;
	int i;
	for (i = 0; i<sizeof((*lblist)->top->Label); i++){
		label[i] = (*lblist)->top->Label[i];
	}
	if ((*lblist)->top->llink != NULL){
		(*lblist)->top = (*lblist)->top->llink;
		(*lblist)->top->rlink = NULL;
		delete delete_stk;
	}
	else{
		(*lblist)->top->rlink = NULL;
	}
	return label;
}
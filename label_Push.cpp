#include <iostream>
#include "struct.h"
using namespace std;

void label_Push(LinkedLblStk **lblist, char *label){
	Label *new_lbl = NULL;
	new_lbl = new Label[1];
	strcpy_s(new_lbl->Label, label);
	if ((*lblist)->top == NULL){
		new_lbl->llink = NULL;
		new_lbl->rlink = NULL;
	}
	else{
		new_lbl->llink = (*lblist)->top;
		(*lblist)->top->rlink = new_lbl;
	}
	(*lblist)->top = new_lbl;
}
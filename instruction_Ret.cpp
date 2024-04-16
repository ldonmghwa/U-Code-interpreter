#include <iostream>
#include "struct.h"
using namespace std;

Linklst* instruction_Ret(Linklst **list, char* ins, char* func_label){
	Linklst *prec = NULL, *escort;
	escort = *list;
	while (escort != NULL){
		if (strcmp(escort->data, ins) == 0 && strcmp(escort->operand1, func_label) == 0){
			return escort;
		}
		prec = escort;
		escort = escort->rlink;
	}
	escort = prec;
	while (escort != NULL){
		if (strcmp(escort->data, ins) == 0 && strcmp(escort->operand1, func_label) == 0){
			return escort;
		}
		prec = escort;
		escort = escort->llink;
	}
}
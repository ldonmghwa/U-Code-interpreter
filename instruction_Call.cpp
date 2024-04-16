#include <iostream>
#include "struct.h"

Linklst * instruction_Call(Linklst **list, char *label){
	Linklst *prec = NULL, *escort;
	escort = *list;
	while (escort != NULL){
		if (strcmp(label, escort->data) == 0){
			return escort;
		}
		prec = escort;
		escort = escort->rlink;
	}
	escort = prec;
	while (escort != NULL){
		if (strcmp(label, escort->data) == 0){
			return escort;
		}
		prec = escort;
		escort = escort->llink;
	}
	return *list;
}
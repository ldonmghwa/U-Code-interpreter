#include <iostream>
#include "struct.h"
Linklst *instruction_Tjp(Linklst **list, char* label, int tf_check){
	Linklst *prec = NULL, *escort;
	if (tf_check == 1){
		escort = *list;
		while (escort != NULL){
			if (strcmp(escort->data, label) == 0) return escort;
			prec = escort;
			escort = escort->rlink;
		}
		escort = prec;
		while (escort != NULL){
			if (strcmp(escort->data, label) == 0) return escort;
			prec = escort;
			escort = escort->llink;
		}
	}
	else if (tf_check == 0) return *list;
}
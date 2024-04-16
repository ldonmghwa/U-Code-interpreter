#include <iostream>
#include "struct.h"
void instruction_Str(Mainmem **mlist, int data, int block, int offset, char *label){
	Mainmem *prec = NULL, *escort;
	escort = *mlist;
	if (block == 1){
		while (escort != NULL){
			if (escort->block == block && escort->offset == offset){
				escort->data = data;
				return;
			}
			prec = escort;
			escort = escort->llink;
		}
		escort = prec;
		while (escort != NULL){
			if (escort->block == block && escort->offset == offset){
				escort->data = data;
				return;
			}
			prec = escort;
			escort = escort->rlink;
		}
	}
	else if (block == 2){
		while (escort != NULL){
			if (strcmp(escort->Label, label) == 0 && escort->block == block&&escort->offset == offset){
				escort->data = data;
				return;
			}
			prec = escort;
			escort = escort->llink;
		}
		escort = prec;
		while (escort != NULL){
			if (strcmp(escort->Label, label) == 0 && escort->block == block&&escort->offset == offset){
				escort->data = data;
				return;
			}
			prec = escort;
			escort = escort->rlink;
		}
	}
}
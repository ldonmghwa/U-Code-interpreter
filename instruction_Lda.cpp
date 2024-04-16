#include <iostream>
#include "struct.h"

int instruction_Lda(Mainmem **mlist, int block, int offset, char *label){
	Mainmem *prec = NULL, *escort;
	escort = *mlist;
	if (block == 1){
		while (escort != NULL){
			if (escort->block == block&&escort->offset == offset){
				return escort->m_addr;
			}
			prec = escort;
			escort = escort->rlink;
		}
		escort = prec;
		while (escort != NULL){
			if (escort->block == block&&escort->offset == offset){
				return escort->m_addr;
			}
			prec = escort;
			escort = escort->llink;
		}
	}
	else if (block == 2){
		while (escort != NULL){
			if (strcmp(label, escort->Label) == 0 && escort->block == block&&escort->offset == offset){
				return escort->m_addr;
			}
			prec = escort;
			escort = escort->rlink;
		}
		escort = prec;
		while (escort != NULL){
			if (strcmp(label, escort->Label) == 0 && escort->block == block&&escort->offset == offset){
				return escort->m_addr;
			}
			prec = escort;
			escort = escort->llink;
		}
	}
}
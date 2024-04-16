#include <iostream>
#include "struct.h"

int instruction_Sym(Mainmem **mlist, int block, int offset, int addr, char *label){
	Mainmem *prec = NULL, *escort;
	Mainmem *new_mem = NULL;
	escort = *mlist;
	while (!(escort->block == -1 && escort->offset == -1)){
		if (strcmp(escort->Label, label) == 0 && escort->block == block&&escort->offset == offset){
			return 0;
		}
		prec = escort;
		escort = escort->rlink;
	}
	escort->block = block;
	escort->offset = offset;
	escort->m_addr = addr;
	return 1;
};
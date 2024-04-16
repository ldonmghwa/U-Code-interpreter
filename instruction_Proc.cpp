#include <iostream>
#include "struct.h"
using namespace std;

void instruction_Proc(Mainmem **mlist, char *label){
	Mainmem *prec = NULL, *escort = *mlist;
	Mainmem *new_mem;
	while (escort != NULL){
		prec = escort;
		escort = escort->rlink;
	}
	new_mem = new Mainmem[1];
	new_mem->block = -1;
	new_mem->offset = -1;
	strcpy_s(new_mem->Label, label);
	if (*mlist == NULL){
		new_mem->rlink = NULL;
		new_mem->llink = NULL;
		*mlist = new_mem;
	}
	else {
		new_mem->rlink = NULL;
		new_mem->llink = prec;
		prec->rlink = new_mem;
	}
}
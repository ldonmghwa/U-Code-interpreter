#include <iostream>
#include "struct.h"
using namespace std;

Mainmem *move_Memory(Mainmem **mlist, char *label){
	Mainmem *prec = NULL, *escort;
	escort = *mlist;
	while (escort != NULL){
		if (strcmp(escort->Label, label) == 0){
			return escort;
		}
		prec = escort;
		escort = escort->rlink;
	}
	return *mlist;
}
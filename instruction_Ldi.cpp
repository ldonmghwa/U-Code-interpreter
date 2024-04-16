#include <iostream>
#include "struct.h"
using namespace std;

int instruction_Ldi(Mainmem **mlist, int m_addr){
	Mainmem *prec = NULL, *escort;
	escort = *mlist;
	while (escort != NULL){
		if (escort->m_addr == m_addr){
			return escort->data;
		}
		prec = escort;
		escort = escort->rlink;
	}
	escort = prec;
	while (escort != NULL){
		if (escort->m_addr == m_addr){
			return escort->data;
		}
		prec = escort;
		escort = escort->llink;
	}

	return escort->data;
}
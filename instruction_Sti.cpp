#include <iostream>
#include "struct.h"
using namespace std;
void instruction_Sti(Mainmem **mlist, int data, int m_addr){
	Mainmem *prec = NULL, *escort;
	escort = *mlist;
	while (escort != NULL){
		if (escort->m_addr == m_addr){
			escort->data = data;
			return;
		}
		prec = escort;
		escort = escort->rlink;
	}
	escort = prec;
	while (escort != NULL){
		if (escort->m_addr == m_addr){
			escort->data = data;
			return;
		}
		prec = escort;
		escort = escort->llink;
	}
}
#include <iostream>
#include <fstream>
#include "struct.h"
using namespace std;

void print_Memory(Mainmem **mlist, ofstream* fout, int check){
	Mainmem *prec = NULL, *escort = *mlist;
	
	*fout << " - 메모리 상태: ";
	if (check == 1) cout << " - 메모리 상태: ";
	try{
		while (escort != NULL){
			prec = escort;
			escort = escort->llink;
		}
		escort = prec;
		while (escort != NULL){
			*fout << escort->data << " ";
			if (check == 1)cout << escort->data << " ";
			escort = escort->rlink;
		}
	}
	catch (char *msg){
		if (check == 1) cout << msg;
	}
	*fout << "\n";
	if (check == 1) cout << "\n";
}
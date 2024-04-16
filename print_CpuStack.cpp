#include <iostream>
#include <fstream>
#include "struct.h"
using namespace std;

void print_CpuStack(LinkedCpuStk **clist, ofstream* fout, int check){
	CpuStk *prec = NULL, *escort = (*clist)->top;
	*fout << " - CPU Stack 상태: ";
	if (check == 1)cout << " - CPU Stack 상태: ";
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
		if (check == 1)cout << msg;
	}
	*fout << "\n";
	if (check == 1)cout << "\n";
}
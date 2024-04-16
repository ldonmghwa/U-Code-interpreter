#include <iostream>
#include "struct.h"
using namespace std;
int cpustk_Pop(LinkedCpuStk **clist){
	if ((*clist) == NULL){
		return 0;
	}
	CpuStk *delete_stk = (*clist)->top;
	int data = (*clist)->top->data;
	if ((*clist)->top->llink != NULL){
		(*clist)->top = (*clist)->top->llink;
		(*clist)->top->rlink = NULL;
	}
	else{
		(*clist)->top->rlink = NULL;
		(*clist)->top = NULL;
	}
	delete delete_stk;
	delete_stk = NULL;
	return data;
}
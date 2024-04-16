#include <iostream>
#include "struct.h"

void cpustk_Push(LinkedCpuStk **clist, int data){
	CpuStk *new_cpu = NULL;
	new_cpu = new CpuStk[1];
	new_cpu->data = data;
	if ((*clist)->top == NULL){
		new_cpu->llink = NULL;
		new_cpu->rlink = NULL;
		(*clist)->top = new_cpu;
	}
	else{
		new_cpu->rlink = NULL;
		new_cpu->llink = (*clist)->top;
		(*clist)->top->rlink = new_cpu;
		(*clist)->top = new_cpu;
	}
}
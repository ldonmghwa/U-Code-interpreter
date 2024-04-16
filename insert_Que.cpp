#include <iostream>
#include "struct.h"
using namespace std;

void insert_Que(Qlst **qlist, int data){
	Queuelst *new_q = new Queuelst[1];
	new_q->data = data;
	new_q->link = NULL;
	if ((*qlist)->front == NULL){
		(*qlist)->front = new_q;
		(*qlist)->rear = new_q;
	}
	else{
		(*qlist)->rear->link = new_q;
		(*qlist)->rear = new_q;
	}
}
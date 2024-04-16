#include <iostream>
#include "struct.h"
using namespace std;

int delete_Que(Qlst **qlist){
	if ((*qlist)->front != NULL){
		Queuelst *del_q = (*qlist)->front;
		int data;
		data = del_q->data;
		(*qlist)->front = (*qlist)->front->link;
		if ((*qlist)->front == NULL){
			(*qlist)->rear = NULL;
		}
		delete del_q;
		return data;
	}
}
#include <iostream>
#include <string.h>
#include "struct.h"
using namespace std;

void Insert_Linkedlist(Linklst **root, char *word, int opperand_check, int word_len){
	Linklst *prec = NULL, *escort;
	Linklst *new_link;
	escort = *root;
	while (escort != NULL){
		prec = escort;
		escort = escort->rlink;
	}
	if (opperand_check == 0){
		new_link = new Linklst[1];
		strcpy_s(new_link->data, word);
		strcpy_s(new_link->operand1, "");
		strcpy_s(new_link->operand2, ""); 
		strcpy_s(new_link->operand3, "");
		new_link->llink = prec;
		if (prec == NULL){
			new_link->rlink = NULL;
			new_link->llink = NULL;
			*root = new_link;
		}
		else{
			new_link->rlink = prec->rlink;
			prec->rlink = new_link;
		}
	}
	else{
		if (prec->operand1[0] == NULL){
			strcpy(prec->operand1, word);
		}
		else if (prec->operand1[0] != NULL && prec->operand2[0] == NULL)
		{
			strcpy(prec->operand2, word);
		}
		else{
			strcpy(prec->operand3, word);
		}
	}
}
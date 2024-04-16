#include <iostream>
#include "struct.h"
using namespace std;
void instruction_Proc(Mainmem **, char *);

void reset_Opcode(Linklst **list, Mainmem **mlist){
	Linklst *root = NULL;
	root = *list;
	char func_label[20];
	while (root != NULL){
		if (strcmp(root->data, "bgn") == 0){
			root->opcode = 1;
			strcpy_s(func_label, "global");
			for (int i = 0; i < atoi(root->operand1); i++)
				instruction_Proc(mlist, func_label);
		}
		else if (strcmp(root->data, "sym") == 0) root->opcode = 2;
		else if (strcmp(root->data, "nop") == 0)root->opcode = 3;
		else if (strcmp(root->data, "end") == 0)root->opcode = 4;
		else if (strcmp(root->data, "proc") == 0)
		{
			root->opcode = 5;
			for (int i = 0; i < atoi(root->operand1); i++){
				instruction_Proc(mlist, func_label);
			}
		}
		else if (strcmp(root->data, "ret") == 0)root->opcode = 6;
		else if (strcmp(root->data, "ldp") == 0)root->opcode = 7;
		else if (strcmp(root->data, "push") == 0)root->opcode = 8;
		else if (strcmp(root->data, "call") == 0)root->opcode = 9;
		else if (strcmp(root->data, "lod") == 0)root->opcode = 10;
		else if (strcmp(root->data, "lda") == 0)root->opcode = 11;
		else if (strcmp(root->data, "ldc") == 0)root->opcode = 12;
		else if (strcmp(root->data, "str") == 0)root->opcode = 13;
		else if (strcmp(root->data, "ldi") == 0)root->opcode = 14;
		else if (strcmp(root->data, "sti") == 0)root->opcode = 15;
		else if (strcmp(root->data, "not") == 0)root->opcode = 16;
		else if (strcmp(root->data, "neg") == 0)root->opcode = 17;
		else if (strcmp(root->data, "inc") == 0)root->opcode = 18;
		else if (strcmp(root->data, "dec") == 0)root->opcode = 19;
		else if (strcmp(root->data, "dup") == 0)root->opcode = 20;
		else if (strcmp(root->data, "add") == 0)root->opcode = 21;
		else if (strcmp(root->data, "sub") == 0)root->opcode = 22;
		else if (strcmp(root->data, "mult") == 0)root->opcode = 23;
		else if (strcmp(root->data, "div") == 0)root->opcode = 24;
		else if (strcmp(root->data, "mod") == 0)root->opcode = 25;
		else if (strcmp(root->data, "gt") == 0)root->opcode = 26;
		else if (strcmp(root->data, "lt") == 0)root->opcode = 27;
		else if (strcmp(root->data, "ge") == 0)root->opcode = 28;
		else if (strcmp(root->data, "le") == 0)root->opcode = 29;
		else if (strcmp(root->data, "eq") == 0)root->opcode = 30;
		else if (strcmp(root->data, "ne") == 0)root->opcode = 31;
		else if (strcmp(root->data, "and") == 0)root->opcode = 32;
		else if (strcmp(root->data, "or") == 0)root->opcode = 33;
		else if (strcmp(root->data, "swp") == 0)root->opcode = 34;
		else if (strcmp(root->data, "ujp") == 0)root->opcode = 35;
		else if (strcmp(root->data, "tjp") == 0)root->opcode = 36;
		else if (strcmp(root->data, "fjp") == 0)root->opcode = 37;
		else{//label
			root->opcode = 0;
			if (strcmp(root->rlink->data, "proc") == 0)
				strcpy_s(func_label, root->data);
		}
		root = root->rlink;
	}
}
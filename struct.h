typedef struct CpuStack{
	int data;
	struct CpuStack *rlink, *llink;
}CpuStk;
typedef struct{
	CpuStk *top;
}LinkedCpuStk;
typedef struct MainMemory{
	char Label[20];
	int data;
	int m_addr;
	int block;
	int offset;
	struct MainMemory *rlink, *llink;
}Mainmem;
typedef struct LabelStack{
	char Label[20];
	struct LabelStack *rlink, *llink;
}Label;
typedef struct{
	Label *top;
}LinkedLblStk;
typedef struct Queue_list{
	int data;
	struct Queue_list *link;
}Queuelst;
typedef struct{
	Queuelst *front, *rear;
}Qlst;
typedef struct Linkedlist{
	char data[20];
	int opcode;
	char operand1[10];
	char operand2[10];
	char operand3[10];
	struct Linkedlist *rlink, *llink;
}Linklst;

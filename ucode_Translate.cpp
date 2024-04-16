#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include "struct.h"
using namespace std;

void reset_Opcode(Linklst **, Mainmem **);
void label_Push(LinkedLblStk **, char *);
Mainmem *move_Memory(Mainmem **, char *);
int instruction_Sym(Mainmem **, int, int, int, char *);
void insert_Que(Qlst **, int);
int delete_Que(Qlst **);
char* label_Pop(LinkedLblStk **, char *);
Linklst* instruction_Ret(Linklst **, char*, char*);
void cpustk_Push(LinkedCpuStk **, int);
int cpustk_Pop(LinkedCpuStk **);
void instruction_Sti(Mainmem **, int, int);
Linklst * instruction_Call(Linklst **, char *);
int instruction_Lod(Mainmem **, int, int, char *);
int instruction_Lda(Mainmem **, int, int, char *);
void instruction_Str(Mainmem **, int, int, int, char *);
int instruction_Ldi(Mainmem **, int);
int instruction_Arith(int, int, int);
int instruction_glenao(int, int, int);
Linklst *instruction_Fjp(Linklst **, char*, int);
Linklst *instruction_Tjp(Linklst **, char*, int);
void print_Memory(Mainmem **, ofstream*, int);
void print_CpuStack(LinkedCpuStk **, ofstream*, int);
void ucode_Translate(Linklst **list, Mainmem **mlist, LinkedCpuStk **clist, LinkedLblStk **lblist, Qlst **qlist, char *file_name){
	if ((*qlist)->front != NULL){
		delete *qlist;
		*qlist = NULL;
		(*qlist) = new Qlst[1];
		(*qlist)->front = NULL;
		(*qlist)->rear = NULL;
	}
	if (*clist != NULL){
		delete *clist;
		*clist = NULL;
		(*clist) = new LinkedCpuStk[1];
		(*clist)->top = NULL;
	}
	if (*lblist != NULL){
		delete *lblist;
		*lblist = NULL;
		(*lblist) = new LinkedLblStk[1];
		(*lblist)->top = NULL;
	}
	while ((*list)->llink != NULL){
		*list = (*list)->llink;
	}
	if (*mlist != NULL){
		delete *mlist;
		*mlist = NULL;
		reset_Opcode(list, mlist);
	}
	Linklst *root = *list;
	Mainmem *mroot = *mlist;
	char _file_name[20];
	strcpy_s(_file_name, file_name);
	strcat(_file_name, ".lst.txt");
	char func_label[20] = "", label[20], return_label[20];
	int addr = 0, data, tf_check = -1, stk_top, stk_top_under, insert_read, step_number = 1;
	int bgn_num = 0, nop_num = 0, sym_num = 0, end_num = 0,
		proc_num = 0, ret_num = 0, ldp_num = 0, push_num = 0,
		call_num = 0, read_num = 0, write_num = 0, lf_num = 0,
		lod_num = 0, lda_num = 0, ldc_num = 0, str_num = 0,
		ldi_num = 0, sti_num = 0, not_num = 0, neg_num = 0,
		inc_num = 0, dec_num = 0, dup_num = 0,
		add_num = 0, sub_num = 0, mult_num = 0,
		div_num = 0, mod_num = 0, gt_num = 0,
		lt_num = 0, ge_num = 0, le_num = 0,
		eq_num = 0, ne_num = 0, and_num = 0,
		or_num = 0, swp_num = 0, ujp_num = 0,
		tjp_num = 0, fjp_num = 0, label_num = 0;
	ofstream fout(_file_name, ios_base::out);
	clock_t start_clock = clock();
	while (root != NULL){
		if (root->opcode != 0) fout << step_number++ << ". 단계 명령어: " << root->data << endl;
		else fout << step_number++ << ". 레이블: " << root->data << endl;
		if (root->opcode == 1){//bgn
			bgn_num++;
			label_Push(lblist, "global");
			strcpy_s(func_label, "global");
			mroot = move_Memory(mlist, "global");
			fout << " - 전역 변수 갯수: " << root->operand1 << endl;
		}
		else if (root->opcode == 2){//sym
			int offset = atoi(root->operand2), i, size = atoi(root->operand3);
			sym_num++;
			fout << " - 함수: " << func_label << endl;
			if (size == 1){
				if (instruction_Sym(&mroot, atoi(root->operand1), offset, addr, func_label) == 0){
					addr--;
				}
				fout << " - 주소: " << addr << endl;
				addr++;
			}
			else{
				fout << " - 주소: " << addr << "~";
				for (i = 0; i < size; i++){
					if (instruction_Sym(&mroot, atoi(root->operand1), offset, addr, func_label) == 0){
						i = i + 1;
						addr++;
						offset++;
					}
					offset++;
					addr++;
				}
				fout << addr - 1 << "까지 설정이 됨" << endl;
			}
			fout << " - 블럭: " << root->operand1 << endl;
			fout << " - 오프셋: " << root->operand2 << endl;
			fout << " - 사이즈: " << root->operand3 << endl;
		}
		else if (root->opcode == 3){//nop
			nop_num++;
			print_Memory(mlist, &fout, 0);
			print_CpuStack(clist, &fout, 0);
			fout << "--------------------------------------------\n";
			root = root->rlink;
			continue;
		}
		else if (root->opcode == 4){//end
			end_num++;
			fout << ">> 프로그램을 종료합니다. \n";
			cout << "\n>>프로그램을 종료합니다.\n>>아무키나 누르세요.\n";
			_getch();
			break;
		}
		else if (root->opcode == 5){//proc
			proc_num++;
			fout << " - 지역 변수 갯수: " << root->operand1 << endl;
			root = root->rlink;
			int i;
			if ((*qlist)->front != NULL){
				for (i = 0; (*qlist)->front != NULL; i++){
					mroot->data = delete_Que(qlist);
					mroot = mroot->rlink;
				}
				for (int j = 0; j < i; j++){
					mroot = mroot->llink;
				}
			}
			print_Memory(mlist, &fout, 0);
			print_CpuStack(clist, &fout, 0);
			fout << "--------------------------------------------\n";
			continue;
		}
		else if (root->opcode == 6){//ret
			ret_num++;
			strcpy_s(return_label, label_Pop(lblist, return_label));
			if (strcmp(return_label, "main") == 0){
				strcpy_s(func_label, "global");
			}
			else{
				strcpy_s(func_label, (*lblist)->top->Label);
			}
			root = instruction_Ret(list, "call", return_label);
			fout << " - return될 Label: " << func_label << endl;
		}
		else if (root->opcode == 7){//ldp
			ldp_num++;
			fout << " - 함수 호출 준비" << endl;
			root = root->rlink;
			print_Memory(mlist, &fout, 0);
			print_CpuStack(clist, &fout, 0);
			fout << "--------------------------------------------\n";
			continue;
		}
		else if (root->opcode == 8){//push
			push_num++;
			data = cpustk_Pop(clist);
			fout << " - push될 data: " << data << endl;
			insert_Que(qlist, data);
		}
		else if (root->opcode == 9){//call
			call_num++;
			if (strcmp(root->operand1, "write") == 0){
				write_num++;
				int pop_data = delete_Que(qlist);
				fout << " - write 함수 호출" << endl;
				fout << " - 출력: " << pop_data << " " << endl;
				cout << pop_data << " ";
			}
			else if (strcmp(root->operand1, "read") == 0){
				read_num++;
				cout << " - read 함수 호출\n";
				cout << " - 값입력: ";
				cin >> insert_read;
				fout << " - read 함수 호출" << endl;
				fout << " - 값 입력: " << insert_read;
				instruction_Sti(mlist, insert_read, delete_Que(qlist));
			}
			else if (strcmp(root->operand1, "lf") == 0){
				lf_num++;
				fout << " - lf 함수 호출" << endl;
				fout << " - 개행 출력 " << endl;
				cout << " - lf 함수 호출" << endl;
				cout << endl;
			}
			else{
				mroot = move_Memory(mlist, root->operand1);
				label_Push(lblist, root->operand1);
				strcpy_s(func_label, root->operand1);
				fout << " - 건너 뛸 함수: " << func_label << endl;
				root = instruction_Call(list, func_label);
			}
		}
		else if (root->opcode == 10){//lod
			lod_num++;
			data = instruction_Lod(mlist, atoi(root->operand1), atoi(root->operand2), func_label);
			cpustk_Push(clist, data);
			fout << " - 함수: " << func_label << endl;
			fout << " - 블록: " << root->operand1 << endl;
			fout << " - 오프셋: " << root->operand2 << endl;
			fout << " - 가져온 값: " << data << endl;
		}
		else if (root->opcode == 11){//lda
			lda_num++;
			data = instruction_Lda(mlist, atoi(root->operand1), atoi(root->operand2), func_label);
			cpustk_Push(clist, data);
			fout << " - 함수: " << func_label << endl;
			fout << " - 가져온 주소 값: " << data << endl;
			fout << " - 블록: " << root->operand1 << endl;
			fout << " - 오프셋: " << root->operand2 << endl;
		}
		else if (root->opcode == 12){//ldc
			ldc_num++;
			cpustk_Push(clist, atoi(root->operand1));
			fout << " - 상수: " << root->operand1 << endl;
		}
		else if (root->opcode == 13){//str
			str_num++;
			data = cpustk_Pop(clist);
			instruction_Str(mlist, data, atoi(root->operand1), atoi(root->operand2), func_label);
			fout << " - 함수: " << func_label << endl;
			fout << " - 블록: " << root->operand1 << endl;
			fout << " - 오프셋: " << root->operand2 << endl;
			fout << " - 저장될 값: " << data << endl;
		}
		else if (root->opcode == 14){//ldi
			ldi_num++;
			data = cpustk_Pop(clist);
			cpustk_Push(clist, instruction_Ldi(mlist, data));
			fout << " - 주소: " << data << endl;
		}
		else if (root->opcode == 15){//sti
			sti_num++;
			stk_top = cpustk_Pop(clist);
			stk_top_under = cpustk_Pop(clist);
			instruction_Sti(mlist, stk_top, stk_top_under);
			fout << " - 메모리에 넣을 값:  " << stk_top << endl;
			fout << " - 메모리 주소: " << stk_top_under << endl;
		}
		else if (root->opcode == 16){//not
			not_num++;
			stk_top = cpustk_Pop(clist);
			fout << " - 바뀌기 전 값:  " << stk_top << endl;
			cpustk_Push(clist, !stk_top);
			fout << " - 진리 값: " << !stk_top << endl;
		}
		else if (root->opcode == 17){//neg
			neg_num++;
			stk_top = cpustk_Pop(clist);
			fout << " - 바뀌기 전 값:  " << stk_top << endl;
			cpustk_Push(clist, 0 - stk_top);
			fout << " - 부호가 적용된 값: " << -stk_top << endl;
		}
		else if (root->opcode == 18){//inc
			inc_num++;
			stk_top = cpustk_Pop(clist);
			fout << " - 바뀌기 전 값:  " << stk_top << endl;
			stk_top++;
			cpustk_Push(clist, stk_top);
			fout << " - 증가된 값: " << stk_top << endl;
		}
		else if (root->opcode == 19){//dec
			dec_num++;
			stk_top = cpustk_Pop(clist);
			fout << " - 바뀌기 전 값:  " << stk_top << endl;
			stk_top--;
			cpustk_Push(clist, stk_top);
			fout << " - 감소된 값: " << stk_top << endl;
		}
		else if (root->opcode == 20){//dup
			dup_num++;
			fout << " - 복사할 값: " << (*clist)->top->data << endl;
			cpustk_Push(clist, (*clist)->top->data);
		}
		else if (root->opcode >= 21 && root->opcode <= 25){//add, sub, mult, div, mod
			if (root->opcode == 21) add_num++;
			else if (root->opcode == 22)sub_num++;
			else if (root->opcode == 23)mult_num++;
			else if (root->opcode == 24)div_num++;
			else if (root->opcode == 25)mod_num++;
			stk_top = cpustk_Pop(clist);
			stk_top_under = cpustk_Pop(clist);
			fout << " - 계산되기 전의 두 값: " << stk_top_under << " " << stk_top << endl;
			int asmdm = instruction_Arith(root->opcode, stk_top, stk_top_under);
			cpustk_Push(clist, asmdm);
			fout << " - 계산 이후 의 값: " << asmdm << endl;
		}
		else if (root->opcode >= 26 && root->opcode <= 33){//gt,lt,ge,le,eq,ne, and, or
			if (root->opcode == 26) gt_num++;
			else if (root->opcode == 27) lt_num++;
			else if (root->opcode == 28) ge_num++;
			else if (root->opcode == 29) le_num++;
			else if (root->opcode == 30) eq_num++;
			else if (root->opcode == 31) ne_num++;
			else if (root->opcode == 32) and_num++;
			else if (root->opcode == 33) or_num++;
			stk_top = cpustk_Pop(clist);
			stk_top_under = cpustk_Pop(clist);
			fout << " - 산술되기 전의 두 값: " << stk_top_under << " " << stk_top << endl;
			int glenao = instruction_glenao(root->opcode, stk_top, stk_top_under);
			cpustk_Push(clist, glenao);
			fout << " - 산술된 이 후의 값: " << glenao << endl;
		}
		else if (root->opcode == 34){//swp
			swp_num++;
			stk_top = cpustk_Pop(clist);
			stk_top_under = cpustk_Pop(clist);
			fout << " - 바뀌기 전의 두 값: " << stk_top_under << " " << stk_top << endl;
			cpustk_Push(clist, stk_top);
			cpustk_Push(clist, stk_top_under);
		}
		else if (root->opcode == 35){//ujp
			ujp_num++;
			fout << " - 건너 뛸 Label: " << root->operand1 << endl;
			root = instruction_Fjp(&root, root->operand1, 0);
		}
		else if (root->opcode == 36){//tjp
			tjp_num++;
			fout << " - 건너 뛸 Label: " << root->operand1 << endl;
			tf_check = cpustk_Pop(clist);
			if (tf_check == 1){
				fout << " - " << root->operand1 << "로 이동\n";
			}
			else{
				fout << " - 이동 안함" << endl;
			}
			root = instruction_Tjp(&root, root->operand1, tf_check);
		}
		else if (root->opcode == 37){//fjp
			fjp_num++;
			fout << " - 건너 뛸 Label: " << root->operand1 << endl;
			tf_check = cpustk_Pop(clist);
			if (tf_check == 0){
				fout << " - " << root->operand1 << "로 이동\n";
			}
			else{
				fout << " - 이동 안함" << endl;
			}
			root = instruction_Fjp(&root, root->operand1, tf_check);
		}
		else{
			label_num++;
			strcpy_s(label, root->data);
		}
		print_Memory(mlist, &fout, 0);
		print_CpuStack(clist, &fout, 0);
		fout << "--------------------------------------------\n";
		root = root->rlink;
		if (start_clock - clock() > 60000){
			return;
		}
	}
	system("cls");
	char str[255], _data[100], block[100], offset[100], m_addr[100], _label[100], cfile_name[20];
	strcpy(cfile_name, file_name);
	strcat(cfile_name, ".uco.txt");
	ifstream fin(cfile_name, ios_base::in);
	fout << "1.메모리 스택 | 2. 메모리 블럭 | 3. 메모리 오프셋 | 4. 메모리 주소 | 5. 메모리 레이블\n";
	fout << "-------------------------------------------------------------------------------------\n";
	printf("1.메모리 스택 | 2. 메모리 블럭 | 3. 메모리 오프셋 | 4. 메모리 주소 | 5. 메모리 레이블\n");
	printf("-------------------------------------------------------------------------------------\n");
	Mainmem *prec = NULL, *escort;
	escort = *mlist;
	while (escort != NULL){
		prec = escort;
		escort = escort->llink;
	}
	escort = prec;
	while (escort != NULL){
		sprintf(_data, "%17d |  ", escort->data);
		fout << _data;
		printf("%13d |  ", escort->data);
		sprintf(block, "%17d |    ", escort->block);
		fout << block;
		printf("%13d |    ", escort->block);
		sprintf(offset, "%17d |  ", escort->offset);
		fout << offset;
		printf("%13d |  ", escort->offset);
		sprintf(m_addr, "%17d |  ", escort->offset);
		fout << m_addr;
		printf("%13d |    ", escort->m_addr);
		sprintf(_label, "%17s\n", escort->Label);
		fout << _label;
		printf("%13s\n", escort->Label);
		escort = escort->rlink;
	}
	printf("-------------------------------------------------------------------------------------\n");
	print_CpuStack(clist,&fout, 0);
	fout << "-------------------------------------------------------------------------------------\n";
	_getch();
	fout << "----uco 파일----\n";
	while (fin.getline(str, 255)){
		fout << str << endl;
	}
	fout << "----각 명령어 별 사용횟수----\n";
	fout << "1. bgn: " << bgn_num << ", OPcode: 1" << endl;
	fout << "2. sym: " << sym_num << ", OPcode: 2" << endl;
	fout << "3. nop: " << nop_num << ", OPcode: 3" << endl;
	fout << "4. end: " << end_num << ", OPcode: 4" << endl;
	fout << "5. proc: " << proc_num << ", OPcode: 5" << endl;
	fout << "6. ret: " << ret_num << ", OPcode: 6" << endl;
	fout << "7. ldp: " << ldp_num << ", OPcode: 7" << endl;
	fout << "8. push: " << push_num << ", OPcode: 8" << endl;
	fout << "9. call: " << call_num << ", OPcode: 9" << endl;
	fout << " - write: " << write_num << endl;
	fout << " - read: " << read_num << endl;
	fout << " - lf: " << lf_num << endl;
	fout << "10. lod: " << lod_num << ", OPcode: 10" << endl;
	fout << "11. lda: " << lda_num << ", OPcode: 11" << endl;
	fout << "12. ldc: " << ldc_num << ", OPcode: 12" << endl;
	fout << "13. str: " << str_num << ", OPcode: 13" << endl;
	fout << "14. ldi: " << ldi_num << ", OPcode: 14" << endl;
	fout << "15. sti: " << sti_num << ", OPcode: 15" << endl;
	fout << "16. not: " << not_num << ", OPcode: 16" << endl;
	fout << "17. neg: " << neg_num << ", OPcode: 17" << endl;
	fout << "18. inc: " << inc_num << ", OPcode: 18" << endl;
	fout << "19. dec: " << dec_num << ", OPcode: 19" << endl;
	fout << "20. dup: " << dup_num << ", OPcode: 20" << endl;
	fout << "21. add: " << add_num << ", OPcode: 21" << endl;
	fout << "22. sub: " << sub_num << ", OPcode: 22" << endl;
	fout << "23. mult: " << mult_num << ", OPcode: 23" << endl;
	fout << "24. div: " << div_num << ", OPcode: 24" << endl;
	fout << "25. mod: " << mod_num << ", OPcode: 25" << endl;
	fout << "26. gt: " << gt_num << ", OPcode: 26" << endl;
	fout << "27. lt: " << lt_num << ", OPcode: 27" << endl;
	fout << "28. ge: " << ge_num << ", OPcode: 28" << endl;
	fout << "29. le: " << le_num << ", OPcode: 29" << endl;
	fout << "30. eq: " << eq_num << ", OPcode: 30" << endl;
	fout << "31. ne: " << ne_num << ", OPcode: 31" << endl;
	fout << "32. and: " << and_num << ", OPcode: 32" << endl;
	fout << "33. or: " << or_num << ", OPcode: 33" << endl;
	fout << "34. swp: " << swp_num << ", OPcode: 34" << endl;
	fout << "35. ujp: " << ujp_num << ", OPcode: 35" << endl;
	fout << "36. tjp: " << tjp_num << ", OPcode: 36" << endl;
	fout << "37. fjp: " << fjp_num << ", OPcode: 37" << endl;
	fout << "38. label: " << label_num << endl;
	fout << "39. total: " << step_number-1 << endl;
	fin.close();
	fout.close();
}

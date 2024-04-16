#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "struct.h"
#include <ctime>
using namespace std;

void UcoFile_Ansys(Linklst **, char *);
void reset_Opcode(Linklst **, Mainmem **);
void ucode_Translate(Linklst **, Mainmem **, LinkedCpuStk **, LinkedLblStk **, Qlst **, char*);
void step_ucode_Translate(Linklst **, Mainmem **, LinkedCpuStk **, LinkedLblStk **, Qlst **, char*);

void main(){
	Linklst *list = NULL;
	Mainmem *mlist = NULL;
	LinkedCpuStk *clist = NULL;
	LinkedLblStk *lblist = NULL;
	Qlst *qlist = NULL;
	qlist = new Qlst[1];
	qlist->front = NULL;
	qlist->rear = NULL;
	char file_name[20] = { NULL }, _file_name[20];
	int input = -1, step_check, file_check = 0, c;
	
	while (1){
		clist = new LinkedCpuStk[1];
		clist->top = NULL;
		lblist = new LinkedLblStk[1];
		lblist->top = NULL;
		system("cls");
		cout << "U code Interpreter";
		cout << " 1. �ڵ� �м�";
		cout << " 2. �ڵ� �ؼ�";
		cout << " 0. ���α׷� ����\n";
		cout << " >> �Է�: ";
		cin >> input;
		if (input == 1){
			system("cls");
			cout << ">> .uco.txt�� �Է� ���ص� ��" << endl;
			cout << ">> ���� �̸� �Է�: ";
			cin >> file_name;
			strcpy_s(_file_name, file_name);
			strcat_s(file_name, ".uco.txt");
			UcoFile_Ansys(&list, file_name);
			file_check++;
			_getch();
		}
		else if (input == 2){
			system("cls");
			while ((c =getchar()) != '\n'&&c!=EOF);
			if (file_check != 0){
				reset_Opcode(&list, &mlist);
				while (1){
					system("cls");
					cout << ">> �ܰ躰 ���� �Ͻðڽ��ϱ�?(yes = 1, no = 0) ";
					cin >> step_check;
					if (step_check == 1){
						step_ucode_Translate(&list, &mlist, &clist, &lblist, &qlist, _file_name);
						break;
					}
					else if (step_check == 0){
						ucode_Translate(&list, &mlist, &clist, &lblist, &qlist, _file_name);
						break;
					}
					else{
						cout << ">> 1, 0�� �Է��� �ֽʽÿ�.\n";
						_getch();
					}
				}
				if (qlist->front != NULL){
					delete qlist;
					qlist = NULL;
				}
				if (mlist != NULL) {
					delete mlist;
					mlist = NULL;
				}
				if (clist != NULL){
					delete clist;
					clist = NULL;
				}
				if (lblist != NULL){
					delete lblist;
					lblist = NULL;
				}
			}
			else{
				cout << ">> �ڵ� �м��� ���� �Ͻʽÿ�. " << endl;
				_getch();
			}
		}
		else if (input == 0){
			cout << ">> ���α׷��� �����մϴ�.\n";
			_getch();
			break;
		}
		else{
			while ((c = getchar()) != '\n'&&c != EOF);
			cout << ">> 1 �Ǵ� 2 �Ǵ� 0�� �Է��� �ּ���.";
			_getch();
		}
	}
	
	if (mlist != NULL)delete mlist;
	if (clist->top != NULL)delete clist;
	if (lblist != NULL)delete lblist;
	if (list != NULL)delete list;
	if (qlist->front != NULL) delete qlist;
}
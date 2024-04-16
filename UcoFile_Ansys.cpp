#include <iostream>
#include "struct.h"
#include <fstream>
using namespace std;
void Insert_Linkedlist(Linklst **, char *, int, int);
void GotoXY(int , int );
void UcoFile_Ansys(Linklst **list, char *file_name){
	char instr_alpha[10] = { NULL };
	char insert_word[100] = { NULL };
	int operand_check = 0;
	int comment_check = 0;
	fstream file(file_name, ios_base::in | ios_base::out);
	if (file.fail()){
		GotoXY(11, 1);
		cout << ">>" << file_name << "라는 파일이 존재하지 않습니다.\n";
	}
	else{
		for (int i = 0; !file.eof(); i++){
			file.read((char*)&instr_alpha[i], sizeof(char));
			if (instr_alpha[i] == ' ' || instr_alpha[i] == '\t')
			{	
				if (i == 0){i = -1;continue;}
				if (comment_check != 0){ i = -1; continue; }
				Insert_Linkedlist(list, insert_word, operand_check, strlen(insert_word));
				if (instr_alpha[i] == ' ') operand_check++;
				for (int j = 0; j < i; j++){
					instr_alpha[j] = NULL;
					insert_word[j] = NULL;
				}
				i = -1;
			}
			else if (instr_alpha[i] == '\n'){
				if (strcmp(insert_word, "") == 0){ i = -1; comment_check = 0; operand_check = 0; continue; }
				if (comment_check != 0){ comment_check = 0; i = -1; operand_check = 0; continue; }
				Insert_Linkedlist(list, insert_word, operand_check, strlen(insert_word));
				for (int j = 0; j < i; j++){
					instr_alpha[j] = NULL;
					insert_word[j] = NULL;
				}
				operand_check = 0;
				i = -1;
			}
			else if (instr_alpha[i] == '%'){
				comment_check++;
			}
			else{
				if (comment_check != 0){ i = -1; continue; }
				insert_word[i] = instr_alpha[i];
			}
		}
		file.close();
		cout << ">> 텍스트 파일 분석이 완료 되었습니다.\n";
	}
}
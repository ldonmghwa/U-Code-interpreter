#include <iostream>

int instruction_glenao(int opcode, int stk_top, int stk_top_under){
	if (opcode == 26){//gt
		if (stk_top_under > stk_top) return 1;
		else return 0;
	}
	else if (opcode == 27){//le
		if (stk_top_under < stk_top) return 1;
		else return 0;
	}
	else if (opcode == 28){//ge
		if (stk_top_under >= stk_top) return 1;
		else return 0;
	}
	else if (opcode == 29){//le
		if (stk_top_under <= stk_top) return 1;
		else return 0;
	}
	else if (opcode == 30){//eq
		if (stk_top_under == stk_top) return 1;
		else return 0;
	}
	else if (opcode == 31){//ne
		if (stk_top_under != stk_top) return 1;
		else return 0;
	}
	else if (opcode == 32){//and
		if (stk_top_under && stk_top) return 1;
		else return 0;
	}
	else if (opcode == 33){//or
		if (stk_top_under || stk_top) return 1;
		else return 0;
	}
}
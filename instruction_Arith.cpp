#include <iostream>
using namespace std;
int instruction_Arith(int opcode, int stk_top, int stk_top_under){
	if (opcode == 21){//add
		stk_top_under = stk_top_under + stk_top;
		return stk_top_under;
	}
	else if (opcode == 22){//sub
		stk_top_under = stk_top_under - stk_top;
		return stk_top_under;
	}
	else if (opcode == 23){//mult
		stk_top_under = stk_top_under*stk_top;
		return stk_top_under;
	}
	else if (opcode == 24){//div
		stk_top_under = stk_top_under / stk_top;
		return stk_top_under;
	}
	else if (opcode == 25){//mod
		stk_top_under = stk_top_under%stk_top;
		return stk_top_under;
	}
}
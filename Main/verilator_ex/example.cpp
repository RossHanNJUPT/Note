#include "Vtop.h"
#include <verilated.h>
#include "verilated_vcd_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char** argv)
{
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);
	Vtop* top = new Vtop{
		contextp
	};
	Verilated::traceEverOn(true);
	VerilatedVcdC* tfp = new VerilatedVcdC;
	top->trace(tfp, 99);
	tfp->open("wave.vcd");
	while(!contextp->gotFinish()) {
		int a = rand() & 1;
		int b = rand() & 1;
		top->a = a;
		top->b = b;
		top->eval();
		printf("a = %d, b = %d, f = %d\n", a, b ,top->f);
		assert(top->f == (a ^ b));
		contextp->timeInc(1);
		tfp->dump(contextp->time());
	}
	top->final();
	tfp->close();
	delete top;

	return 0;
}

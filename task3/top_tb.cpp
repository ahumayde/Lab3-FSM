#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "vbuddy.cpp"   
#define MAX_SIM_CYC 100000

int main(int argc, char **argv, char **env) {
  int simcyc;     
  int tick;       
  int lights = 0; 

  Verilated::commandArgs(argc, argv);

  Vtop * top = new Vtop;

  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);

  tfp->open ("top.vcd");
  if (vbdOpen()!=1) return(-1);

  vbdHeader("Lab 3 Task 3");
  vbdSetMode(1);       

  top->clk = 1;
  top->rst = 0;
  top->en = 0;
  top->N = vbdValue();

  for (simcyc=0; simcyc<MAX_SIM_CYC; simcyc++) {

    for (tick=0; tick<2; tick++) {
      tfp->dump (2*simcyc+tick);
      top->clk = !top->clk;
      top->eval ();
    }

    top->rst = (simcyc < 2);  
    top->en = (simcyc > 2);
    top->N = vbdValue();

    vbdBar(top->dout);
    vbdCycle(simcyc);

    if (Verilated::gotFinish())  exit(0);
  }
  vbdClose();  
  tfp->close(); 
  exit(0);
}

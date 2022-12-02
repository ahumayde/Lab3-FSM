#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"
#include "vbuddy.cpp"     
#define MAX_SIM_CYC 10000

int main(int argc, char **argv, char **env) {
  int simcyc;  
  int tick;       
  int x = 0;

  Verilated::commandArgs(argc, argv);

  Vtop * top = new Vtop;

  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);
  tfp->open ("top.vcd");

  if (vbdOpen()!=1) return(-1);
  vbdHeader("L3T2: Delay");
  vbdSetMode(1);      

  top->clk     = 1;
  top->rst     = 0;
  top->trigger = 0;
  top->N       = 27;



  for (simcyc=0; simcyc<MAX_SIM_CYC; simcyc++) {

    for (tick=0; tick<2; tick++) {
      tfp->dump (2*simcyc+tick);
      top->clk = !top->clk;
      top->eval ();
    }
  
    top->rst = (simcyc < 2);  
    top->trigger = vbdFlag();
    top->N = vbdValue();

    if(top->dout + x == 255){
      vbdInitWatch();
    } 

    if(top->trigger && top->dout == 0){  
        int time = vbdElapsed();

        vbdHex(3,time >> 8 & 0xF);
        vbdHex(2,time >> 4 & 0xF);
        vbdHex(1,time & 0xF);
    }

    vbdBar(top->dout);
    vbdCycle(simcyc);

    x = top->dout;

    if (Verilated::gotFinish())  exit(0);
  }
  vbdClose();  
  tfp->close(); 
  exit(0);
}

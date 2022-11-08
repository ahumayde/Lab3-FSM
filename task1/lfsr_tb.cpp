#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vlfsr.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env){
    int cycle;
    int tick;

    Verilated::commandArgs(argc,argv);

    Vlfsr* top = new Vlfsr;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);

    tfp->open("lfsr.vcd");
    if(vbdOpen()!=1) return(-1);


    vbdHeader("L3T1: LFSR");
    vbdSetMode(1);

    top->clk = 1;
    top->rst = 0;
    top->en  = 0;

    for (cycle = 0; cycle < 10000; cycle++){

        for (tick = 0; tick < 2; tick++){
            tfp->dump(2 * cycle + tick);
            top->clk = !top->clk;
            top->eval();
        }

        top->en = vbdFlag();

        vbdHex(2, int(top->dout) >> 4 & 0xF);
        vbdHex(1, int(top->dout) & 0xF);        
        vbdBar(top->dout & 0xFF);
        vbdCycle(cycle);

        if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) exit(0);
    }
    vbdClose();
    tfp->close();
    printf("Exiting\n");
    exit(0);

}

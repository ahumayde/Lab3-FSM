#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"
#include "Vf1_fsm.h"

int main(int argc, char **argv, char **env){
    int cycle; 
    int tick; 

    Verilated::commandArgs(argc, argv);

    Vf1_fsm* top = new Vf1_fsm;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp,99);

    tfp->open("f1_fsm.vcd");
    if(vbdOpen()!=1) return(-1);


    vbdHeader("Lab 3 Task 2");
    vbdSetMode(1);

    top->clk = 1;
    top->rst = 0;
    top->en  = 1;

    for (cycle = 0; cycle < 10000; cycle++){

        for (tick = 0; tick < 2; tick++){
            tfp->dump(2 * cycle + tick);
            top->clk = !top->clk;
            top->eval();
        }

        top->en = vbdFlag();
        top->rst = (cycle < 2);

        vbdBar(top->dout & 0xFF);
        vbdCycle(cycle);

        if (Verilated::gotFinish() || vbdGetkey() == 'q' ) exit(0);
    }
    vbdClose();
    tfp->close();
    printf("Exiting\n");
    exit(0);


}
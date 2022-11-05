#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"
#define ROM_SZ 256
#define ADDRESS_WIDTH 8

int main(int argc, char **argv, char **env) {
    int cycle;
    int clk;

    Verilated::commandArgs(argc, argv);

    Vsinegen* top = new Vsinegen;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("sinegen.vcd");

    if (vbdOpen()!=1) return -1;
    vbdHeader("ALLAHU AKBAR");
    
    top->clk  = 1;
    top->rst  = 0;
    top->en   = 1;
    top->incr = 1;

    for (cycle = 0; cycle < 1000000; cycle++){
    
        for(clk = 0; clk < 2; clk++){
            tfp->dump( 2 * cycle + clk );
            top->clk = !top->clk;
            top->eval();
        }

        top->incr = vbdValue();

        vbdPlot(int(top->dout),0,255);
        vbdCycle(cycle);

        if( (Verilated::gotFinish()) || (vbdGetkey()=='q')) exit(0);
    } 
    vbdClose();
    tfp->close();
    exit(0);
}
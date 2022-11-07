#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vsigdelay.h"
#include "vbuddy.cpp"
#define MAX_SIM_CYC 10000
#define ADDRESS_WIDTH 9
#define RAM_SZ pow(2,ADDRESS_WIDTH)

int main(int argc, char **argv, char **env) {
  int cycle;     
  int tick;      

  Verilated::commandArgs(argc, argv);

  Vsigdelay* top = new Vsigdelay;

  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);

  tfp->open ("sigdelay.vcd");
  if (vbdOpen()!=1) return(-1);

  vbdHeader("L2T3:Delay");
  vbdInitMicIn(RAM_SZ);
  
  top->clk = 1;
  top->rst = 0;
  top->en = 1;
  top->off = 1;

  for (cycle = 0; cycle<MAX_SIM_CYC; cycle++) {

    for (tick=0; tick<2; tick++) {
      tfp->dump (2*cycle+tick);
      top->clk = !top->clk;
      top->eval();
    }

    top->signal = vbdMicValue();
    top->off = vbdValue();//abs()

    vbdPlot(int(top->signal)+80, 0, 255);
    vbdPlot(int(top->dout)-60, 0, 255);

    vbdCycle(cycle);

    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) exit(0);
  }
  vbdClose();   
  tfp->close(); 
  printf("Exiting\n");
  exit(0);
}

#include "F28x_Project.h"
void PWM();
void GPIO();
void main(void)
{

    EALLOW;
    PWM();
    GPIO();
    EDIS;

}

void PWM(void)
{

CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=0;
ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=0;
CpuSysRegs.PCLKCR2.bit.EPWM1=1;
CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=1; // for synchronizing clocking signals

EPwm1Regs.TBPRD=2000; // Set timer period
EPwm1Regs.TBCTL.bit.CTRMODE=2;
EPwm1Regs.TBCTL.bit.CLKDIV=1;
EPwm1Regs.TBCTL.bit.HSPCLKDIV=1;
EPwm1Regs.CMPA.bit.CMPA=30;
EPwm1Regs.TBCTL.bit.SYNCOSEL=00;// Disable sync-out
EPwm1Regs.TBCTL.bit.FREE_SOFT=1;// Ignore emulation suspend

EPwm1Regs.TBCTR=0x0000;// Clear counter
EPwm1Regs.TBPHS.bit.TBPHS=0;// Set timer phase
EPwm1Regs.TBCTL.bit.PHSEN = 0;// Disable phase loading
EPwm1Regs.ETSEL.bit.SOCAEN=1;// Enable ADC SOCA event
EPwm1Regs.ETPS.bit.INTPRD=0;// Set SOCA on PRD event
EPwm1Regs.ETPS.bit.INTPSSEL=1;// Generate SOCA on first event
EPwm1Regs.TBCTL.bit.PRDLD=1;
EPwm1Regs.TBCTL.bit.CTRMODE=2;// Enable the timer in count up mode
EPwm1Regs.AQCTL.bit.SHDWAQAMODE=0;
EPwm1Regs.CMPCTL.bit.SHDWAMODE=1;

EPwm1Regs.AQCTLA.bit.CAU=01;
EPwm1Regs.AQCTLA.bit.PRD=10;
EPwm1Regs.AQCTLA.bit.CAD=01;

EPwm1Regs.AQCTLB.bit.CAU=01;
EPwm1Regs.AQCTLB.bit.PRD=10;
EPwm1Regs.AQCTLB.bit.CAD=01;


EPwm1Regs.DBCTL.bit.OUT_MODE=0x11; // enable Dead-band module
EPwm1Regs.DBCTL.bit.POLSEL=2;// Active High complementary
EPwm1Regs.DBFED.bit.DBFED=160;// FED = 20 TBCLKS
EPwm1Regs.DBRED.bit.DBRED=80;// RED 20 TBCLKs

CpuSysRegs.PCLKCR0.bit.TBCLKSYNC=1;// TBCLK to ePWM modules enabled
}

void GPIO(void)
{

    GpioCtrlRegs.GPAGMUX1.bit.GPIO0=0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0=1;
    GpioCtrlRegs.GPAPUD.bit.GPIO0=1;

    GpioCtrlRegs.GPAGMUX1.bit.GPIO1=0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1=1;
    GpioCtrlRegs.GPAPUD.bit.GPIO1=1;

}

/*
 * main.c
 *
 *  Created on: 2019. 5. 9.
 *      Author: JJang
 */


#include "def.h"

void main(void)
{
	// Disable Global Interrupt
	DINT;

	InitSysCtrl();

	// ���ͷ�Ʈ �ʱ�ȭ
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	// MMR ��ȣ ���� ����
	EALLOW;

	// LED GPIO �ʱ�ȭ
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;		// GREEN
	GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;		// RED
	GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;

	PieVectTable.TINT0 = &cpu_timer0_isr;

	// MMR ��ȣ ���� ����
	EDIS;

	// CPU0 Ÿ�̸� �ʱ�ȭ
	InitCpuTimers();
	cal_Timer_Prd();
	ConfigCpuTimer(&CpuTimer0, Cpu_Clk, Cpu_Prd);

	// CPU Timer0 ����
	StartCpuTimer0();

	// CPU Timer0 ���ͷ�Ʈ Ȱ��ȭ
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	IER |= M_INT1; 								// CPU0 Timer ���ͷ�Ʈ(INT1.7)  Ȱ��ȭ

	EINT;   									// Enable Global interrupt INTM
	ERTM;   									// Enable Global realtime interrupt DBGM

	GpioDataRegs.GPADAT.bit.GPIO14 = 1;			// GREEN
	GpioDataRegs.GPADAT.bit.GPIO15 = 0;			// RED

	for(;;)
	{
		if(Cpu_cnt >= 10000)	// 1��
		{
			GpioDataRegs.GPATOGGLE.bit.GPIO14 = 1;
			Cpu_cnt = 1;
		}
	}
}

/*
 * main.c
 *
 *  Created on: 2019. 5. 9.
 *      Author: JJang
 */


#include "def.h"

void main(void)
{
	int fft_cnt = 0;
	int fft_factor = 1;
	int i;

	// Disable Global Interrupt
	DINT;

	InitSysCtrl();

	// 인터럽트 초기화
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	// MMR 보호 영역 해제
	EALLOW;

	// LED GPIO 초기화
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;		// GREEN
	GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;		// RED
	GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;

	ConfigSciPin();

	PieVectTable.TINT0 = &cpu_timer0_isr;

	// MMR 보호 영역 설정
	EDIS;

	// CPU0 타이머 초기화
	InitCpuTimers();
	cal_Timer_Prd();
	ConfigCpuTimer(&CpuTimer0, Cpu_Clk, Cpu_Prd);

	// CPU Timer0 시작
	StartCpuTimer0();

	// CPU Timer0 인터럽트 활성화
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	IER |= M_INT1; 								// CPU0 Timer 인터럽트(INT1.7)  활성화

	EINT;   									// Enable Global interrupt INTM
	ERTM;   									// Enable Global realtime interrupt DBGM

	GpioDataRegs.GPADAT.bit.GPIO14 = 1;			// GREEN
	GpioDataRegs.GPADAT.bit.GPIO15 = 0;			// RED

	// SCI 초기화
	InitSCI();

	FFT_init();

	for(;;)
	{
		if(Cpu_cnt >= 100000)	// 1초
		{
			if(fft_cnt < 0 || fft_cnt > 160)
				fft_factor *= -1;

			fft_cnt += fft_factor;

			GpioDataRegs.GPATOGGLE.bit.GPIO14 = 1;
			Cpu_cnt = 0;
			FFTtest(fft_cnt);

			for(i=0;i<10;i++)
			{
				if(freq_point[i])
					SendToPc("%d freq : %d,\t",i,freq_point[i]);
				else
				{
					SendToPc("\n");
					break;
				}
			}
		}
	}
}

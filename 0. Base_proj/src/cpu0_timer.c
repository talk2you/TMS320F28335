/*
 * cpu0_timer.c
 *
 *  Created on: 2019. 5. 9.
 *      Author: JJang
 */

#include "cpu0_timer.h"
#include "stdlib.h"


Uint16 Cpu_Clk = 150;
Uint32 Cpu_cnt = 0;
Uint32 Cpu_Prd = 0;


/* ------------------------------------------------
 * # Timer 주기 설정 #
 * ------------------------------------------------
 * CPU0 Timer 설정법
 * ex) "10m"라고 입력하면 10ms 주기로 타이머 인터럽트 발생
 * 	   "100u"라고 입력하면 100us 주기로 타이머 인터럽트 발생
------------------------------------------------ */

char Timer_Prd[10] = {"100u"};


void cal_Timer_Prd(void)
{
	int i = 0;
	char temp_num[10] = {0,};
	char temp_symbol = 0;

	while(Timer_Prd[i] != '\0' )
	{
		if(Timer_Prd[i] > 'a')
		{
			temp_symbol = Timer_Prd[i];
		}
		else
			temp_num[i] = Timer_Prd[i];
		i++;
	}

	Cpu_Prd = atoi(temp_num);

	switch(temp_symbol)
	{
	case 'u' :
		Cpu_Prd *= 1;
		break;
	case 'm' :
		Cpu_Prd *= 1000;
		break;
	default :
		Cpu_Prd *= 1000000;
	}
}

interrupt void cpu_timer0_isr(void)
{
	Cpu_cnt++;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;	// Acknowledge interrupt to PIE
}


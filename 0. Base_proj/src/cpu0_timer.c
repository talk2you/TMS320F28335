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
 * # Timer �ֱ� ���� #
 * ------------------------------------------------
 * CPU0 Timer ������
 * ex) "10m"��� �Է��ϸ� 10ms �ֱ�� Ÿ�̸� ���ͷ�Ʈ �߻�
 * 	   "100u"��� �Է��ϸ� 100us �ֱ�� Ÿ�̸� ���ͷ�Ʈ �߻�
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


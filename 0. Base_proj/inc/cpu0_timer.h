/*
 * cpu0_timer.h
 *
 *  Created on: 2019. 5. 9.
 *      Author: JJang
 */

#ifndef INC_CPU0_TIMER_H_
#define INC_CPU0_TIMER_H_

#include "def.h"

void cal_Timer_Prd(void);
interrupt void cpu_timer0_isr(void);

extern Uint16 Cpu_Clk;
extern Uint32 Cpu_Prd;
extern Uint32 Cpu_cnt;

#endif /* INC_CPU0_TIMER_H_ */

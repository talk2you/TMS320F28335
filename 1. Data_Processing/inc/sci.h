/*
 * sci.h
 *
 *  Created on: 2019. 06. 17.
 *      Author: JJang
 */

#ifndef SRC_SCI_H_
#define SRC_SCI_H_

#include "def.h"

void ConfigSciPin(void);
void InitSCI(void);
interrupt void scibRxIsr(void);

extern Uint16 SCI_RxFlag;


#endif /* SRC_SCI_H_ */

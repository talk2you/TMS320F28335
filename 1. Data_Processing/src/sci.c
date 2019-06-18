/*
 * sci.c
 *
 *  Created on: 2019. 06. 17.
 *      Author: JJang
 */

/* --------------------------------------
 *  SCI A : PC 와 통신
 *  SCI B : Control Board 와 통신
 *
 *  GPIO35,36 : USB
 *  GPIO22,23 : Control Board
 --------------------------------------*/

/* ------------------------------------------------
 * # SCI 통신 초기화 #
 * ------------------------------------------------
 * @ ConfigSciPin 	: SCI Pin 설정
 * @ InitSCI		: SCI Register 설정
 * @ scibRxIsr		: SCI 수신 인터럽트
------------------------------------------------ */

#include "sci.h"
#include "com.h"

Uint16 SCI_TXintCount;
Uint16 SCI_RXintCount;
Uint16 SCI_RxFlag;

void ConfigSciPin(void)
{
	/* SCI-A Pin */
	GpioCtrlRegs.GPBPUD.bit.GPIO36 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)
	GpioCtrlRegs.GPBQSEL1.bit.GPIO36 = 3;  // Asynch input GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 1;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1;   // Configure GPIO29 for SCITXDA operation

	/* SCI-B Pin */
	GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;    // Enable pull-up for GPIO28 (SCIRXDB)
	GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;	   // Enable pull-up for GPIO29 (SCITXDB)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;   // Configure GPIO29 for SCITXDA operation
}

void InitSCI(void)
{
	/* SCI-A Init */
	SciaRegs.SCICTL1.bit.SWRESET = 0;		// SCI 소프트웨어 리셋

	SciaRegs.SCICCR.bit.SCICHAR = 7;		// SCI 송수신 Charcter-length 설정 : 8bit
	SciaRegs.SCICCR.bit.LOOPBKENA = 0;		// SCI 루프백 테스트 모드 Enable
	SciaRegs.SCICTL1.bit.RXENA = 0;			// SCI 수신기능 Enable
	SciaRegs.SCICTL1.bit.TXENA = 1;			// SCI 송신기능 Enable
	SciaRegs.SCICTL2.bit.RXBKINTENA = 0;	// SCI 수신 인터럽트 Enable
	SciaRegs.SCIHBAUD = 0x00;      			// SCI Baudrate 설정
	SciaRegs.SCILBAUD = 0x12;				// LSPCLK = 37.5MHz, 37500000 / (18+1) * 8 = 246710 (250000) bps

	SciaRegs.SCIPRI.bit.FREE = 1;			// SCI 에뮬레이션 프리 모드

	SciaRegs.SCICTL1.bit.SWRESET = 1;		// SCI 소프트웨어 리셋 해제

	/* SCI-B Init */
	ScibRegs.SCICTL1.bit.SWRESET = 0;		// SCI 소프트웨어 리셋

	ScibRegs.SCICCR.bit.SCICHAR = 7;		// SCI 송수신 Charcter-length 설정 : 8bit
	ScibRegs.SCICCR.bit.LOOPBKENA = 0;		// SCI 루프백 테스트 모드 Enable
	ScibRegs.SCICTL1.bit.RXENA = 1;			// SCI 수신기능 Enable
	ScibRegs.SCICTL1.bit.TXENA = 1;			// SCI 송신기능 Enable
	ScibRegs.SCIHBAUD = 0x00;      			// SCI Baudrate 설정
	ScibRegs.SCILBAUD = 0x12;				// LSPCLK = 37.5MHz, 37500000 / (18+1) * 8 = 246710 (250000) bps
	ScibRegs.SCIPRI.bit.FREE = 1;			// SCI 에뮬레이션 프리 모드

	ScibRegs.SCICTL2.bit.RXBKINTENA = 1;

	ScibRegs.SCICTL1.bit.SWRESET = 1;		// SCI 소프트웨어 리셋 해제
}

interrupt void scibRxIsr(void)
{
	Enque(&que,ScibRegs.SCIRXBUF.bit.RXDT);
	EINT;

	SCI_RxFlag = 1;
	SCI_RXintCount++;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;			// Acknowledge interrupt to PIE
}

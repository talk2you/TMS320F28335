/*
 * com.c
 *
 *  Created on: 2018. 12. 17.
 *      Author: JJang
 */

/* ------------------------------------------------
 * # Ring Queue �Լ�
 * ------------------------------------------------
 * @ InitQueue		: Queue �ʱ�ȭ
 * @ IsFull			: Queue ������ ���� Ȯ��
 * @ IsEmpty		: Queue ����ִ� ���� Ȯ��
 * @ Enque			: Queue ������ �Է�
 * @ Deque			: Queue ������ ���
------------------------------------------------ */

/* ------------------------------------------------
 * # Serial �Լ�
 * ------------------------------------------------
 * @ SendToPc 		: PC�� Serial ������ ���
------------------------------------------------ */

#include "com.h"
#include "sci.h"

Uint16 MCU_Receive = 0;
volatile Uint16 adc1 = 0, adc2 = 0, adcstat = 0;
char buf[10];

Queue que;

va_list ap;

/*^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+

										Ring Queue

^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^*/

void InitQueue(Queue *queue)
{
    queue->front = queue->rear = 0; 			// Ring Queue Initialization
}
int IsFull(Queue *queue)
{
    return NEXT(queue->rear) == queue->front;	//���� rear�� front�� ������ �� �� ����
}
int IsEmpty(Queue *queue)
{
    return queue->front == queue->rear;    		//front�� rear�� ������ �� ����
}
void Enque(Queue *queue, int data)
{
    if (IsFull(queue))
    {
        //printf("Que is full!\n");
        return;
    }
    queue->buf[queue->rear] = data;				//rear �ε����� ������ ����
    queue->rear = NEXT(queue->rear); 			//rear�� ���� ��ġ�� ����
}
int Deque(Queue *queue)
{
	int re;
    if (IsEmpty(queue))
        return -1;
    re = queue->buf[queue->front];				//front �ε����� ������ ���� re�� ����
    queue->front = NEXT(queue->front);			//front�� ���� ��ġ�� ����
    return re;
}

/*^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+

									Communication with PC

^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^`'*._,+^*/


void SendToPc(char* format, ...)
{
	char buf[30];
	char i = 0;

	va_start(ap, format);
	cst_vsprintf(buf,format,ap);
	va_end(ap);

	while(buf[i] != '\0')
	{
		while(!(SciaRegs.SCICTL2.bit.TXRDY));
		SciaRegs.SCITXBUF = buf[i++] & 0x00FF;
	}
}

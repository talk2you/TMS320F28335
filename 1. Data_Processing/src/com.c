/*
 * com.c
 *
 *  Created on: 2018. 12. 17.
 *      Author: JJang
 */

/* ------------------------------------------------
 * # Ring Queue 함수
 * ------------------------------------------------
 * @ InitQueue		: Queue 초기화
 * @ IsFull			: Queue 가득찬 상태 확인
 * @ IsEmpty		: Queue 비어있는 상태 확인
 * @ Enque			: Queue 데이터 입력
 * @ Deque			: Queue 데이터 출력
------------------------------------------------ */

/* ------------------------------------------------
 * # Serial 함수
 * ------------------------------------------------
 * @ SendToPc 		: PC로 Serial 데이터 출력
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
    return NEXT(queue->rear) == queue->front;	//다음 rear가 front와 같으면 꽉 찬 상태
}
int IsEmpty(Queue *queue)
{
    return queue->front == queue->rear;    		//front와 rear가 같으면 빈 상태
}
void Enque(Queue *queue, int data)
{
    if (IsFull(queue))
    {
        //printf("Que is full!\n");
        return;
    }
    queue->buf[queue->rear] = data;				//rear 인덱스에 데이터 보관
    queue->rear = NEXT(queue->rear); 			//rear를 다음 위치로 설정
}
int Deque(Queue *queue)
{
	int re;
    if (IsEmpty(queue))
        return -1;
    re = queue->buf[queue->front];				//front 인덱스에 보관한 값을 re에 설정
    queue->front = NEXT(queue->front);			//front를 다음 위치로 설정
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

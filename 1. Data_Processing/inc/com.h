/*
 * com.h
 *
 *  Created on: 2018. 12. 17.
 *      Author: JJang
 */

#ifndef INC_COM_H_
#define INC_COM_H_

#include "def.h"

#if 0
void InitSciQue(void);
void EnQue_Ctrl(int data);
int DeQue_Ctrl(void);
#endif

#define QUEUE_SIZE 20
#define NEXT(index)   ((index+1)%QUEUE_SIZE)

typedef struct Queue //Queue 구조체 정의
{
	int buf[QUEUE_SIZE]; //저장소
	int front; //꺼낼 인덱스(가장 오래전에 보관한 데이터가 있는 인덱스)
	int rear; //보관할 인덱스
} Queue;

extern char buf[10];
extern volatile Uint16 adc1, adc2, adcstat;
extern Queue que;

void InitQueue(Queue *queue); //큐 초기화
int IsFull(Queue *queue); //큐가 꽉 찼는지 확인
int IsEmpty(Queue *queue); //큐가 비었는지 확인
void Enque(Queue *queue, int data); //큐에 보관
int Deque(Queue *queue); //큐에서 꺼냄

void SendToPc(char* format, ...);
void SendToMcu(Uint16 mode, Uint16 data);
void RecvFromMcu(void);
void ProcessMcuData(void);

void RecvFromAdc(Uint16 data);

void TestCom(void);
void Err_Com(void);

#endif /* INC_COM_H_ */

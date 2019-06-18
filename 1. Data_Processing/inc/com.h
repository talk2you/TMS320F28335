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

typedef struct Queue //Queue ����ü ����
{
	int buf[QUEUE_SIZE]; //�����
	int front; //���� �ε���(���� �������� ������ �����Ͱ� �ִ� �ε���)
	int rear; //������ �ε���
} Queue;

extern char buf[10];
extern volatile Uint16 adc1, adc2, adcstat;
extern Queue que;

void InitQueue(Queue *queue); //ť �ʱ�ȭ
int IsFull(Queue *queue); //ť�� �� á���� Ȯ��
int IsEmpty(Queue *queue); //ť�� ������� Ȯ��
void Enque(Queue *queue, int data); //ť�� ����
int Deque(Queue *queue); //ť���� ����

void SendToPc(char* format, ...);
void SendToMcu(Uint16 mode, Uint16 data);
void RecvFromMcu(void);
void ProcessMcuData(void);

void RecvFromAdc(Uint16 data);

void TestCom(void);
void Err_Com(void);

#endif /* INC_COM_H_ */

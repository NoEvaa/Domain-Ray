#ifndef _YZMAIN_H_
#define _YZMAIN_H_

#include "yzmain.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<pthread.h>
#ifndef N
#define N 6
#endif
struct Map{
    int mine;//����λ��ͼ��<0F|1T> 
    int show;//չʾ����ͼ��<0δչ��|1չ��|2���>
    int nums;//��Χ����ͼ�� 
};

void gtxy(int x,int y);
void timer_event(int t);
int mouseput();
void *timer(void *arg);//��ʱ��
void p_status();
void clean(); 
void HideCursor();
void SetSize(short x,short y);
void go_on(int c,int x,int y,int ax,int ay);
#endif

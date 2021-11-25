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
    int mine;//地雷位置图版<0F|1T> 
    int show;//展示版面图板<0未展开|1展开|2标记>
    int nums;//周围雷数图版 
};

void gtxy(int x,int y);
void timer_event(int t);
int mouseput();
void *timer(void *arg);//计时器
void p_status();
void clean(); 
void HideCursor();
void SetSize(short x,short y);
void go_on(int c,int x,int y,int ax,int ay);
#endif

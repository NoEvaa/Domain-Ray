#ifndef _YZETMB_H_
#define _YZETMB_H_

#include "yzetmb.h"
#include "yzmain.h"

void entertainment2();//ÓéÀÖ2 
int play2();//ÓéÀÖ2ÓÎÏ·½ø³Ì 
void play2_frame();
void play2_set_mine(struct Map (*p)[N],int count,int Nc);
void play2_get_mine(struct Map (*p)[N],int Nc);
int play2_get_mine_nums(struct Map (*p)[N],int x,int y,int Nc);
void pr_mine_nums(struct Map (*p)[N],int Nc);
void play2_right(struct Map (*p)[N],int x,int y);
void p_lm();
int check2(struct Map (*p)[N],int Nc);

#endif

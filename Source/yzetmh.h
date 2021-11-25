#ifndef _YZETMH_H_
#define _YZETMH_H_

#include "yzetmh.h"
#include "yzmain.h"
#include "yzgame.h"

void entertainment8();//ÓéÀÖ8
int play8();//ÓéÀÖ8ÓÎÏ·½ø³Ì
void play8_frame();
void play8_set_mine(struct Map (*p)[9],int count,int Nc);
void play8_get_mine(struct Map (*p)[9]);
int play8_get_mine_nums(struct Map (*p)[9],int x,int y);
int play8_judge_board(struct Map (*p)[9],int x,int y,int Nc);
void play8_open_zero_board(struct Map (*p)[9],int x,int y,int Nc);
void play8_show_board(struct Map (*p)[9],int i,int j);
int play8_left_key(struct Map (*p)[9],int x,int y,int Nc);
void play8_fir_pro(struct Map (*p)[9],int x,int y,int Nc);
int play8_judge_sat(struct Map (*p)[9],int i,int j,int x,int y);
void play8_change_loc(struct Map (*p)[9],int x,int y,int ax,int ay,int Nc);
void p8_d_mine(struct Map (*p)[9]);
void play8_right_key(struct Map (*p)[9],int x,int y);

#endif

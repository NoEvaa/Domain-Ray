#ifndef _YZETMG_H_
#define _YZETMG_H_

#include "yzetmg.h"
#include "yzmain.h"
#include "yzgame.h"

void entertainment7();//ÓéÀÖ7
int play7();//ÓéÀÖ3ÓÎÏ·½ø³Ì
int play7_event(struct Map (*p)[19],int lr,int Nc,int *revp);
void play7_set_mine(struct Map (*p)[19],int count,int Nc,int lr);
void empty_mine(struct Map (*p)[19],int Nc,int lr);
void play7_get_mine(struct Map (*p)[19]);
int play7_get_mine_nums(struct Map (*p)[19],int x,int y);
int play7_judge_board(struct Map (*p)[19],int x,int y,int Nc,int lr);
void play7_open_zero_board(struct Map (*p)[19],int x,int y,int Nc,int lr);
void play7_show_board(struct Map (*p)[19],int i,int j);
void play7_frame();
void p_play7_map(int lr,int Nc);
int play7_left_key(struct Map (*p)[19],int x,int y,int Nc,int lr);
void play7_fir_pro(struct Map (*p)[19],int x,int y,int Nc,int lr);
int play7_judge_sat(struct Map (*p)[19],int i,int j,int x,int y,int Nc);
void play7_change_loc(struct Map (*p)[19],int x,int y,int ax,int ay,int Nc,int lr);
void p7_m();
void p7_r(int r);
void p7_l(int l);
void p7_d_mine(struct Map (*p)[19]);

#endif

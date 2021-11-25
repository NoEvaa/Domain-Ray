#ifndef _YZETMA_H_
#define _YZETMA_H_

#include "yzetma.h"
#include "yzmain.h"
#include "yzgame.h"

void entertainment1();//ÓéÀÖ1 
void et_event(int ec); 
int play1(int ec);//ÓéÀÖ1ÓÎÏ·½ø³Ì 
void play1_p_resu(int resu,int x,int y);
int play1_victory(int ec);
void play1_frame();
int left_key1(struct Map (*p)[N][N][N],int x,int y,int Nc,int *rx,int *ry,int *rz,int *rt,int *cli);
int left_key1_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc,int *rx,int *ry,int *rz,int *rt);
void play1_set_mine(struct Map (*p)[N][N][N],int count,int Nc);
void set_out_key(struct Map (*p)[N][N][N],int *x,int *y,int *z,int *t,int Nc);
void search(struct Map (*p)[N][N][N],int x,int y,int Nc,int rx,int ry,int rz,int rt);
void search_event(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc,int rx,int ry,int rz,int rt);
void search_judge(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc,int rx,int ry,int rz,int rt);
void p_cb_xy(int x,int y,int color);
void p_kout_xy(int x,int y,int i);

#endif

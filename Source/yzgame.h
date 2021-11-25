#ifndef _YZGAME_H_
#define _YZGAME_H_

#include "yzgame.h"
#include "yzprogress.h"
#include "yzmain.h"

void set_mine(struct Map (*p)[N][N][N],int count,int Nc);//置雷 
void get_mine(struct Map (*p)[N][N][N],int Nc);//读雷
int get_mine_nums(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//获取雷数
int judge_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//面板判定 
void open_zero_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);
void open_t_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);
void show_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//面板展开 

void p_s_xy(int x,int y);//打印方块 
void p_m_xy(int x,int y);// 打印标记 
void p_n_xy(int x,int y,int nums);//打印雷数 
void p_newmap(int lx,int ly,int Nc);//打印地图 
void p_m_nums(struct Map (*p)[N][N][N],int Nc,int me);//打印m1 m2
int count_mine(struct Map (*p)[N][N][N],int t,int Nc); 
void p_b_nums(struct Map (*p)[N][N][N],int Nc,int me);//打印b1 b2
int count_blank(struct Map (*p)[N][N][N],int t,int Nc);
void p_level(int le);//打印难度
void p_resu(int resu,int x,int y);//打印道具 
void p_d_mine(struct Map (*p)[N][N][N],int Nc);//失败后打印雷标 

int victory(int le);//胜利事件 
int defeat(int x,int y);//失败事件 
int game(int Nc,int M,int merge,int firstpro,int timelim,int signres,int reviveprop,int level);//扫雷主函数 
int left_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int fl,int me);//左键 
int left_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc,int fl);
void right_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int me);//右键 
void right_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc);
void fir_pro(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//首次保护 
int judge_sat(struct Map (*p)[N][N][N],int i,int j,int k,int x,int y,int z,int t,int Nc);
void change_loc(struct Map (*p)[N][N][N],int x,int y,int z,int t,int ax,int ay,int az,int Nc);
void frame();
#endif

#ifndef _YZGAME_H_
#define _YZGAME_H_

#include "yzgame.h"
#include "yzprogress.h"
#include "yzmain.h"

void set_mine(struct Map (*p)[N][N][N],int count,int Nc);//���� 
void get_mine(struct Map (*p)[N][N][N],int Nc);//����
int get_mine_nums(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//��ȡ����
int judge_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//����ж� 
void open_zero_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);
void open_t_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);
void show_board(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//���չ�� 

void p_s_xy(int x,int y);//��ӡ���� 
void p_m_xy(int x,int y);// ��ӡ��� 
void p_n_xy(int x,int y,int nums);//��ӡ���� 
void p_newmap(int lx,int ly,int Nc);//��ӡ��ͼ 
void p_m_nums(struct Map (*p)[N][N][N],int Nc,int me);//��ӡm1 m2
int count_mine(struct Map (*p)[N][N][N],int t,int Nc); 
void p_b_nums(struct Map (*p)[N][N][N],int Nc,int me);//��ӡb1 b2
int count_blank(struct Map (*p)[N][N][N],int t,int Nc);
void p_level(int le);//��ӡ�Ѷ�
void p_resu(int resu,int x,int y);//��ӡ���� 
void p_d_mine(struct Map (*p)[N][N][N],int Nc);//ʧ�ܺ��ӡ�ױ� 

int victory(int le);//ʤ���¼� 
int defeat(int x,int y);//ʧ���¼� 
int game(int Nc,int M,int merge,int firstpro,int timelim,int signres,int reviveprop,int level);//ɨ�������� 
int left_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int fl,int me);//��� 
int left_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc,int fl);
void right_key(struct Map (*p)[N][N][N],int lx,int ly,int x,int y,int Nc,int me);//�Ҽ� 
void right_key_event(struct Map (*p)[N][N][N],int i,int j,int k,int t,int Nc);
void fir_pro(struct Map (*p)[N][N][N],int x,int y,int z,int t,int Nc);//�״α��� 
int judge_sat(struct Map (*p)[N][N][N],int i,int j,int k,int x,int y,int z,int t,int Nc);
void change_loc(struct Map (*p)[N][N][N],int x,int y,int z,int t,int ax,int ay,int az,int Nc);
void frame();
#endif

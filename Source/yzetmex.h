#ifndef _YZETMEX_H_
#define _YZETMEX_H_

#include "yzetmex.h"
#include "yzmain.h"
#include "yzetmexb.h"
#include "yzetmexc.h"

void extra();//番外 
int extra_choice();
void entertainment_c1();//番外1 
int e_c1_play();//番外1游戏进程 
void randomwalk(int bp[9][9]);
int check_rw_stop(int bp[9][9],int x,int y);
int check_rw_walk(int bp[9][9],int x,int y);
void e_c1_p_map(int bp[9][9]);
void e_c1_frame();
void e_c1_p_d(int nm);
int count_nm(int bp[9][9]);
int e_c1_left_event(int bp[9][9],int x,int y,int rx,int ry);

#endif

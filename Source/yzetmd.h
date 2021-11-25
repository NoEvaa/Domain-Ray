#ifndef _YZETMD_H_
#define _YZETMD_H_

#include "yzetmd.h"
#include "yzmain.h"

void entertainment4();//”È¿÷4
void e_4();
void e4_rule();
void e4_r1();
void e4_r2();
void e4_r3();
void e4_r4(); 
void p_choice_lv(int l);
void p_choice_od(int o);
int play4(int lv,int ord);//”È¿÷4”Œœ∑Ω¯≥Ã
int play4_event(int (*p)[5],int x,int y,int op,int Nc);
void play4_max_judge(int (*p)[5],int Nc);
void play4_kaboom(int (*p)[5],int i,int j,int Nc,int v);
void p4_wmap(int (*p)[5],int Nc);
void p4_n_wb(int x,int y,int n);
void p_situ(int cb,int bl,int wh);
void p_lev(int lv);
void calcu_situ(int (*p)[5],int Nc);
void play4_frame();
int d_end(int v,int r);
int AI_Simple(int (*p)[5],int Nc);
int AI_Normal(int (*p)[5],int Nc); 
int AI_get_situ(int (*p)[5],int b[25],int Nc);
int AI_ALIce(int (*p)[5],int Nc);
int AI_Noah(int (*p)[5],int Nc);
void AI_event(int (*p)[5],int v);
void AI_Noah_laststep_pred(int (*p)[5],int Nc);
void AI_MinefieldCyberBrain_Kernel(int (*p)[5],int pn,unsigned long long *wi,unsigned long long *lo,unsigned long long *dr);
int SuperAI_BHR_MFCB_NOAHsARK(int (*p)[5],int Nc);

#endif
